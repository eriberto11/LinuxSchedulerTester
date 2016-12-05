# 	makefile
#   jon leijon
#   Laboration 3 Systemnära Programmering HT 2016
#	Kompilerar mish  till en executable, med massvis med flaggor.
#	dv14jln
#   2016-09-09

CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -Wmissing-declarations -Wmissing-prototypes -Werror-implicit-function-declaration -Wreturn-type -Wparentheses -Wunused -Wold-style-definition -Wundef -Wshadow -Wstrict-prototypes -Wswitch-default -Wstrict-prototypes -Wunreachable-code

TFLAGS=-std=c11 -Wall

all:SchedulerTester

SchedulerTester: workerProg.c schedTest.c	
	$(CC) $(TFLAGS) -g schedTest.c  workerProg.h workerProg.c -lpthread  -o SchedulerTester



clean:
	rm SchedulerTester
