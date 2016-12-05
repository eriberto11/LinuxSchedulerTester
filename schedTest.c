#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "workerProg.h"

/*struct sched_param {
   //            ...
               int sched_priority;
     //          ...
};*/

//void *dummyfunc(void *empty);

void *dummyfunc(void *empty){
    empty=malloc(1);
	printf("scheduler set ? !");
    return empty;
}
int main ( int argc , char *argv[] ) {
	//pthread_t pt ;
	//int t=pthread_create(&pt,NULL,&dummyfunc,NULL);
	//http://man7.org/linux/man-pages/man2/sched_setscheduler.2.html
	// int sched_setscheduler(pid_t pid, int policy,
    //                          const struct sched_param *param);
	//Om arg 1 == 0 så sätts sched för nuvarnade tråd.
	struct sched_param *param = malloc(sizeof(struct sched_param));
//	param->sched_priority=2;	
//	sched_setscheduler(0,SCHED_BATCH,param);
//	sched_setscheduler(0,SCHED_IDLE,param);
//	sched_setscheduler(0,SCHED_OTHER,param);
//	sched_setscheduler(0,SCHED_FIFO,param);
//	sched_setscheduler(0,SCHED_RR,param);
	//sched_setscheduler(0,0,param);
	int i = sched_getscheduler(0);
	printf("Current scheduler is %d\n"	,i);	
	struct stuff *blo = malloc(sizeof(struct stuff));
	void* p;
	doWork(blo);
    return 0;
}
