#include <stdio.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

struct stuff
{
int workload;
long ClockCycles;
long latency;
long workClocker;
int scheduler;
} stuff;

struct evaluatorStat {
long clock ;   // Keeps time from first operation to last after running the testpointer.
void *funcPtr; // Points to the test that is actually being run.
int NrOfWork; // should be variable, can't only try one work size.
long CPUCycles; // If we can actually count how many cpuCycles program uses, lets write it to this.
bool testComplete; // Could the test actually be run/completed ? Best to make sure.
} evaluator;


void* doWork(void *workStruct)  ;
int runIt(int q);