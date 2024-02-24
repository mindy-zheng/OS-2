// Name: Mindy Zheng
// Date: 2/17/2024 
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/wait.h>

void help() { 
	printf("This program is designed to launch child processes specified by the user. Here are the parameters:\n"); 
	printf("[-h] - outputs a help message and terminates the program.\n");
	printf("[-n proc] - specifies total number of child processes.\n");
	printf("[-s simul] - specifies maximum number of child processes that can simultaneously run.\n");
	printf("[-t timeLimit for children] - specifies the bound of time a child process will be launched for ... b/w 1 second and -t]\n"); 
	printf("[-i intervalInMs] - specifies how often a children should be launched based on sys clock\n"); 
}

// the Process Table does not have to be in shared memory 
struct PCB { 
	int occupied;	// either true or false
	pid_t pid; 		// process id of current assigned child 
	int start_seconds; 	// start seconds when it was forked
	int start_nano; 	// start nano when it was forked 
}; 

struct PCB processTable[20];

// System clock - seconds and nanoseconds 
typedef struct Clock { 
	int seconds; 
	int nanoseconds;
} Clock; 

#define ONESEC_NANO 1000000000 // 1,000,000,000 (billion) nanoseconds is equal to 1 second 
#define INCREMENT_NANO 10000000 // 100,000,000 nanoseconds is equal to .1 second 
#define NANO_MAX 999999999

void incrementClock(Clock *clock_ptr) { 
	clock_ptr-> nanoseconds += INCREMENT_NANO;
		// a check to see if nanoseconds has reached 1 sec
		if (clock_ptr-> nanoseconds >= ONESEC_NANO) { 
				clock_ptr-> seconds -= 1; // incremenet 1 sec
				clock_ptr-> nanoseconds -= ONESEC_NANO;
		} 
}

// Key for shared memory stuff 
#define SH_KEY 89918991

/* random number generator - if it is called with -t 7, then when calling worker processes, it should call them with a time interval randomly between 1 second and 7 seconds (with nanoseconds also random).*/ 

int randomNum(int min, int max) { 
	if (min==max) { 
		return min; 
	} else { 
		return min + rand() / (RAND_MAX / (max-min+1) +1); 
	}
}


int main(int argc, char **argv) { 
	int opt; 
	const char optstr[] = "hn:s:t:f:"; 
	int proc = 0; // total number of processes -n 
	int simul = 0; // maximum number of child processes that can simultaneously run -s 
	char *iter; // number of iterations
	int timeLimit = 0; // time limit for children -t 
	int intervalMs = 0; // interval in Ms to launch children -i `
	
	// oss [-h] [-n proc] [-s simul] [-t timelimitForChildren] [-i intervalInMsToLaunchChildren]
	while ((opt = getopt(argc, argv, optstr)) != -1) { 
		switch(opt) { 
			case 'h': 
				help(); 
				break; 
			case 'n': 
				proc = atoi(optarg); 
				break;
			case 's': 
				simul = atoi(optarg); 
				break; 
			case 't': 
				timeLimit = atoi(optarg); 
				break; 
			case 'i': 
				intervalMs = atoi(optarg); 
				break; 
		}
	}

	srand(time(0)); 
	int random_seconds = randomNum(1, timeLimit); 
	int random_nanoseconds = randomNum(0, 999999999); 
	
	char str_seconds[10], str_nanoseconds[10]; 
	sprintf(str_seconds, "%d", random_seconds); 
	sprintf(str_nanoseconds, "%d", random_nanoseconds); 
	
	printf("Timelimit: 1 to %d, random generated num: %d\n", timeLimit, random_seconds); // debugging statement

	int running_processes = 0; 
	// Make sure that the processes never exceed user input
	for (int counter = 0; counter < proc; counter++) { 
		pid_t pid = fork(); // spins off another processes 
		running_processes++; 

		if (pid == 0) { 
			char* args[] = {"./user", iter, 0}; 
			execvp(args[0], args); 
		} 
		else if (pid < 0) { 
			perror("Fork failed\n"); 
		}
	
		if (pid != 0) { 
			while (running_processes == simul) { 
				if (waitpid(-1, NULL, WNOHANG) != 0) { 
					sleep(1); 
					running_processes--; 
				}
			}
		}
	}
	while (wait(NULL) > 0); 
	return 0; 

} 

