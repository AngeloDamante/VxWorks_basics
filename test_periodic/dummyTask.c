/*
 * dummyTask.c
 *
  */

#include "dummyTask.h"
#include <stdio.h>

void all_done(void) {
	printf("All DONE!!\n");
	fflush(stdout);
}

void get_busy(int n) {
	int i, r=LOWER_LIMIT, going=UP;
	for(i=0;i<n;i++) {
		if(going==UP) {
			if(r<UPPER_LIMIT)
				r++;
			else
				going=DOWN;
		}
		else {
			if(r>LOWER_LIMIT)
				r--;
			else
				going=UP;
		}
	}
	all_done();
}
