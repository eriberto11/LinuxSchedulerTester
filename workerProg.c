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
	clock_t start = clock();
	runIt(100000);
	diff = clock() - start;
	int msec = diff  ;
	printf("Starting of the program, start_t = %ld\n", start);
	printf("After runit loop, diff  = %ld\n", diff);
    
//   printf("Going to scan a big loop, start_t = %ld\n", start);    
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
