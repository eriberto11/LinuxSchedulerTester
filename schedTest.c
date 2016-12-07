#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include "workerProg.h"

/*struct sched_param {
   //            ...
               int sched_priority;
     //          ...
};*/

//void *dummyfunc(void *empty);
long globalCntr;
long allUpdates;
typedef enum {SYNCH,LOAD,FLOATOPS,EMPTYLOOP} ttype;
int doSomeMath(int inVal){
	double d = atan2((double) inVal,0.1);
	d=log(d);
	int q=(int)ceil(d);
	return 1;
}

int dummyfunc(void *empty) {
    empty=malloc(1);
	printf("scheduler set ? !\n");
    return empty;
}
int synchFuncer(struct evaluatorStat *gg){
	pthread_mutex_t *mlock=gg->lock;
	//try(pt)
	/*for (int i = 0; i < gg->NrOfWork; ++i)
	{*/
		int calc=doSomeMath(55);
		pthread_mutex_lock(mlock);
		globalCntr=globalCntr+1;
		pthread_mutex_unlock(mlock);
		allUpdates++;

		/* code */
	//}
		gg->stop=clock();
}
void printdiff(struct evaluatorStat *gg) {
	printf("time taken for thread %d : %d\n",gg->id, gg->stop-gg->start );
}
void calculateAvg(struct evaluatorStat *gg[],int length){
	int avg=0;
	for(int i = 0;i<length;i++){
		avg+=gg[i]->stop - gg[i]->start;
	}
	printf("AVG : %d",avg /length); 	
}


int main ( int argc , char *argv[] ) {
	// To gather options of program. 
	int op=0;
	globalCntr=0;
	allUpdates=0;
	char *testtype="synch";
	ttype t = SYNCH;
	int noOfTimes=100;
	while((op =	getopt(argc,argv,"n:slfe")) != -1) {
		switch(op) {
		/*	case 't':
				printf("t %s\n", optarg);
				testtype=optarg;
				break;
		*/	case 'n':
				noOfTimes=atoi(optarg);
				printf("n %s\n", optarg);
				break;
			case 's':
				t=SYNCH;
				break;
			case 'l':
				t=LOAD;
				break;
			case 'f':
				t=FLOATOPS;
				break;
			case 'e':
				t=EMPTYLOOP;
				break;
			default:
				printf("DEFAULT %s\n", optarg);
				break;
		}
	}
	int results[noOfTimes] ;
	pthread_mutex_t newLock ;
	if(pthread_mutex_init(&newLock,NULL)<0) {
		fprintf(stderr, "Lock not initiated\n");
	}
	struct evaluatorStat *ct[noOfTimes];
	for(int i =0;i<noOfTimes;i++){
		ct[i]= malloc(sizeof(struct evaluatorStat)*noOfTimes);
	}

	for(int i=0;i<noOfTimes;i++) {
/*		switch(t) {
			case SYNCH:
			printf("SYNCH %d",i);
			break;
			case LOAD:
			printf("LOAD %d",i);
			break;
			case FLOATOPS:
			printf("FLÖPAT %d",i);
			break;
			case EMPTYLOOP:
			printf("EMPTYLOOP %d",i);
			break;
		}
*/		ct[i]->id=i;
		ct[i]->clock=20;
		ct[i]->NrOfWork=noOfTimes;
		ct[i]->lock = &newLock;
		switch(t) {
			case SYNCH:
			ct[i]->funcPtr=&synchFuncer;
		//	printf("SYNCH %d",i);
			break;
			case LOAD:
			ct[i]->funcPtr=&synchFuncer;
		//	printf("LOAD %d",i);
			break;
			case FLOATOPS:
			ct[i]->funcPtr=&synchFuncer;
		//	printf("FLÖPAT %d",i);
			break;
			case EMPTYLOOP:
			ct[i]->funcPtr=&synchFuncer;
		//	printf("EMPTYLOOP %d",i);
			break;
		}
	}


	pthread_t threadpool[noOfTimes];
	for(int i=0;i<noOfTimes;i++){


		ct[i]->start=clock();
		if(pthread_create(&threadpool[i],NULL,ct[i]->funcPtr,ct[i])<0)
			fprintf(stderr, "Thread create error\n" );	
	}
	for(int i=0;i<noOfTimes;i++){
		if(pthread_join(&threadpool[i],NULL)<0)
			fprintf(stderr, "Thread join error\n" );
	}
	for(int i=0;i<noOfTimes;i++){
		printdiff(ct[i]);
	}
	calculateAvg(ct,noOfTimes);
	fprintf(stdout, "nr of updates for globalCntr: %d, and globalCntr itself: %d\n",allUpdates,globalCntr );
	//http://man7.org/linux/man-pages/man2/sched_setscheduler.2.html
	// int sched_setscheduler(pid_t pid, int policy,
    //                          const struct sched_param *param);
	//Om arg 1 == 0 så sätts sched för nuvarnade tråd.
	/*struct sched_param *param = malloc(sizeof(struct sched_param));
//	param->sched_priority=2;	
//	sched_setscheduler(0,SCHED_BATCH,param);
//	sched_setscheduler(0,SCHED_IDLE,param);
//	sched_setscheduler(0,SCHED_OTHER,param);
//	sched_setscheduler(0,SCHED_FIFO,param);
//	sched_setscheduler(0,SCHED_RR,param);
	sched_setscheduler(0,0,param);
	int i = sched_getscheduler(0);
	printf("Current scheduler is %d\n"	,i);	
	struct stuff *blo = malloc(sizeof(struct stuff));
	struct evaluatorStat *evla= malloc(sizeof(struct evaluatorStat));
	evla->clock= 10;
	evla->funcPtr=&runIt;
	fprintf(stdout, "clock = %d\n",evla->clock );
	void* p;
	doWork(blo);
	printf("\nafter doWork\n");
	pthread_t pt ;
	evla->funcPtr();

	int qt=pthread_create(&pt,NULL,&doWork,blo);
	if(t) {
		fprintf(stdout, "Something bad from pthread \n" );
	}else {
		fprintf(stdout, "Something good from pthread \n" );
	}
	pthread_join(pt,NULL);*/
    return 0;
}
