#include <stdio.h>
#include <stdio.h>
#include <time.h>

struct stuff
{
int workload;
long ClockCycles;
long latency;
long workClocker;
} stuff;



void* doWork(void *workStruct)  ;
int runIt(int q);
