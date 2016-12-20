#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include "workerProg.h"
#include <errno.h>
/*struct sched_param {
   //            ...
               int sched_priority;
     //          ...
};*/

//void *dummyfunc(void *empty);
long globalCntr;
long allUpdates;

typedef enum {SYNCH,LOAD,FLOATOPS,EMPTYLOOP} ttype;

typedef enum {SCHEDFIFO,SCHEDRR } schedulerType;

int doSomeMath(int inVal){
	double d = atan2((double) inVal,0.1);
	d=log(d);
	int q=(int)ceil(d);
	return 1;
}

int floatOperations(struct  evaluatorStat *gg){
	float f1 = .4444;
	float f2 = .621678;
	for(int i = 0; i<gg->NrOfWork ; i++){
		f1=f1*f2;
	}
	gg->stop=clock();
}



int dummyfunc(void *empty) {
    empty=malloc(1);
	printf("scheduler set ? !\n");
    return empty;
}
int synchFuncer(struct evaluatorStat *gg) {
	for (int i = 0; i < gg->NrOfWork; ++i)
	{
		int calc=doSomeMath(55);
		pthread_mutex_lock(gg->lock);
		globalCntr=globalCntr+1;
		//doSomeMath(globalCntr);
		pthread_mutex_unlock(gg->lock);
		allUpdates++;

		/* code */
	}
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
	schedulerType sched = SCHED_FIFO;
	int noOfTimes=100;

	struct sched_param *sp = malloc(sizeof(struct sched_param));
	sp->sched_priority=99;
	const struct sched_param *ss= sp;
	while((op =	getopt(argc,argv,"S:n:slfe")) != -1) {
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
			case 'S':
				sched = SCHED_RR;
				int sSet=sched_setscheduler(0,SCHED_FIFO,  ss);
				printf("Set Scheduler %d\n",sSet);
				if(sSet<0)
		//			printf("probs %s\n", strerror(errno));
					;
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
		ct[i]->id=i;
		ct[i]->clock=20;
		ct[i]->NrOfWork=noOfTimes;
		ct[i]->lock = &newLock;
		ct[i]->funcPtr=&synchFuncer;
		switch(t) {
			case SYNCH:
			ct[i]->funcPtr=&synchFuncer;
			break;
			case LOAD:
			ct[i]->funcPtr=&synchFuncer;
			break;
			case FLOATOPS:
			ct[i]->funcPtr=&floatOperations;
			break;
			case EMPTYLOOP:
			ct[i]->funcPtr=&synchFuncer;
			break;
		}
	}

	pthread_t theThreads[noOfTimes];
	for (int i = 0; i < noOfTimes; ++i)
	{
		ct[i]->start=clock();
		int q=	pthread_create(&theThreads[i],NULL,ct[i]->funcPtr,ct[i]);

		int bu=		sched_setscheduler(q,SCHED_FIFO,ss);
		printf("pthread created %d sched %d\n",q, bu );
	}

	for (int i = 0; i < noOfTimes; ++i)
	{
		int q = pthread_join(theThreads[i],NULL);
	//	fprintf(stdout, "pthread joined %d\n",q );
	}


	for(int i=0;i<noOfTimes;i++) {
		printdiff(ct[i]);
	}
	calculateAvg(ct,noOfTimes);
	fprintf(stdout, "nr of updates for globalCntr: %d, and globalCntr itself: %d\n",allUpdates,globalCntr );

    return 0;
}
