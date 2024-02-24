#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
// By Mindy Zheng

// 1) Implement shared memory and test 



int main(int argc, char** argv) {
	int iter = atoi(argv[1]); 
	for (int i = 1; i <= iter; i++) { 
		printf("USER PID: %i PPID: %i ITERATION: %i before sleeping\n", getpid(), getppid(), i); 
		sleep(1); 
		printf("USER PID: %i PPID: %i ITERATION: %i after sleeping\n", getpid(), getppid(), i);
	}
	return 0; 
} 

