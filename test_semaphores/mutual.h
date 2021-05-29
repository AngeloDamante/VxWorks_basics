TASK_ID myTaskId;

/**
 * Type "m1 = semMCreate(1)" 
 * (note that the initial state of a mutual exclusion semaphore is always full) 
 * and then type "tid1 = sp (semM, m1)" and "tid2 = sp (semM, m1)".
 * 
 * What happens? Task tid1 takes the semaphore and suspends itself,
 * while task tid2 is suspended while taking the semaphore (pended).
 * 
 * Then type tr(tid1): this resumes task tid1, which gives the semaphore 
 * and finishes its execution. As a consequence, task tid2 is awakened,
 * takes the semaphore, and suspends itself.
 * 
 * Finally, type tr (tid2).
 */

void semM (SEM_ID mutexId)
{
	if (semTake(mutexId, WAIT_FOREVER) == ERROR) {
		printErr ("Error: semTake failed\n");
		return;
	}
	taskSuspend(0);
	printf ("%s resumed\n", taskName (0));
	semGive(mutexId);
}
