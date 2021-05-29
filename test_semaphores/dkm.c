/* includes */

#include "vxWorks.h"
#include "taskLib.h"
#include "semLib.h"
#include "mutual.h"
#include <stdio.h>
#include <string.h>

SEM_ID countingSemId;
TASK_ID myTaskId;
int count;
int taskCount;


void semTakeRoutine(void) {
	FOREVER {
		printf("Task %s is attempting to get the binary semaphore [%d] \n", taskName(0), count+1);
		semTake(countingSemId, WAIT_FOREVER);
		printf("Task %s got the binary semaphore [%d]\n", taskName(0), ++count);
		fflush(stdout);
	}
}

void semGiveRoutine(int iterations) {
	int count;
	for(count=1; count<=iterations; count++) {
		printf("Task %s is attempting to release the binary semaphore\n", taskName(0));
		fflush(stdout);
		semGive(countingSemId); 
		/* at this point the task is preempted if the task that was blocked has higher prio */
	}
}

void mySemGiveTaskSpawn(char * s, int iterations) {
	taskCount++;
	myTaskId = taskSpawn(s, 101, 0, 4000, (FUNCPTR) semGiveRoutine, iterations, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	/* note that lower numbers correspond to higher priorities */
}

void mySemTakeTaskSpawn(char * s) {
	taskCount++;
	myTaskId = taskSpawn(s, 100, 0, 4000, (FUNCPTR) semTakeRoutine, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	/* note that lower numbers correspond to higher priorities */
}

void init(void) {
	countingSemId = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
	printf("Task %s created a binary semaphore with id %d\n", taskName(0), countingSemId);
	
	count = 0;
	taskCount = 0;
}

/* Kernel Shell:
 * sp init: assigns the semaphore creation to task
 * sp (mySemTakeTaskSpawn, "tsh1"): routine spawns with name "tsk1" 
 * 	this task will be in PENDED state because semB is empty.
 * sp(mySemGiveTaskSpawn, "tsk2",1): routine spawns with name "tsk2"
 * 
 * semTake => -1
 * semGive => +1
 */
