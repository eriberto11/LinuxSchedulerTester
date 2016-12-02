#include <stdio.h>
#include <stdio.h>
#include <time.h>

struct stuff
{
int workload;
long ClockCycles;
long latency;
long workClocker;
};

void* doWork(void *workStruct)  ;
int runIt(int q);
