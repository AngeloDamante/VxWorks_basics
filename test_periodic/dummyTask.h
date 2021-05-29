/*
 * dummyTask.h
 *
 * 
 */

#ifndef DUMMYTASK_H_
#define DUMMYTASK_H_

#define LOWER_LIMIT 1000
#define UPPER_LIMIT 2000
#define UP 1
#define DOWN 0

#define TOTAL_SIMULATION_TICKS 250


#define OPSMSEC 551000

/* only for event tracing purposes */
void all_done(void);

/* to simulate actual computation: keeps CPU busy for n cycles */
void get_busy(int n);


#endif // DUMMYTASK_H_ 
