#include "workerProg.h"

/**
*	Should be called as the test starts
*	Timer inspiration from 
*   http://stackoverflow.com/questions/459691/best-timing-method-in-c
*/



void* doWork(void *workStruct) {
	//static int CLOCKS_PER_SEC=10000;
	//int diff=0;
	clock_t diff;
	struct stuff *wk = workStruct;
	wk->workload=100;
	clock_t start = clock();
	runIt(100000);
	diff = clock() - start;
	wk->ClockCycles=diff;
	int msec = diff  ;
	printf("Starting of the program, start_t = %ld\n", start);
	printf("After runit loop, diff  = %ld\n", wk->ClockCycles);
    
   printf("Going to scan a big loop, workload = %ld\n", wk->workload);    
	printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

	return workStruct;
}

int runIt(int q) { 
	int z=0;	
	for(int i =0;i<q;i++) {
		;	
	}
	printf("done with %d cycles\n",q);
	return z;
}
