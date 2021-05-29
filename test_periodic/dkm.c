/* includes */

#include "vxWorks.h"
#include "taskLib.h"	// task
#include "semLib.h"		// semaphore
#include "sysLib.h"		// periodic act
#include "subsys/timer/vxbTimerLib.h" // timer
#include "dummyTask.h"

TASK_ID WorkerId;
int JobLength = 5;

/*
 * ISR code must be as short as possible.
 * It should have the only resume function.
 * not semTake, yes semGive
 */
void AuxClkISR(void) {
	static int count = 0;
	logMsg("Tick: %d\n", ++count, 0, 0, 0, 0, 0);
	taskResume(WorkerId);
}

void Worker(void) {
	int JobId = 0; // not need static
	FOREVER {
		taskSuspend(0);
		logMsg("job %d started\n", JobId, 0, 0, 0, 0, 0);
		// get_busy(JobLength * OPSMSEC); // try me!
		logMsg("job %d finished\n", JobId, 0, 0, 0, 0, 0);
		JobId++;
	}
}

/*
 * Customarily, we consider the aux clock frequency to be our base frequency
 * (for example, 20ms), while periodic tasks are activated at frequencies 
 * that are multiples of such base frequency.
 */
void start(void) {
	/* safe: armed auxiliary clock with same rate of system clock */
	sysAuxClkRateSet(sysClkRateGet());

	/* task spawn */
	WorkerId = taskSpawn("Worker", 100, 0, 4000, (FUNCPTR) Worker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	/* active auxiliary clock */
	sysAuxClkEnable();

	/* get timer info */
	int MinFreq, MaxFreq;
	logMsg("Auxiliary clock enabled. Obtaining timer handler information...\n", 0, 0, 0, 0, 0, 0);
	timerHandle_t th = sysAuxClkHandleGet();
	vxbTimerFeaturesGet(th, (UINT32 *) &MinFreq, (UINT32 *) &MaxFreq, NULL);
	logMsg("Timer frequency between %d and %d (%d). Connecting...\n", MinFreq, MaxFreq, sysAuxClkRateGet(), 0, 0, 0);

	/* connect to ISR */
	sysAuxClkConnect((FUNCPTR) AuxClkISR, (_Vx_usr_arg_t) 0);

	/* delay calling task from executing duration = 10 seconds */
	taskDelay(10 * sysClkRateGet());
	sysAuxClkDisable();
}
