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
	printf("[-t iter] - number of iterations. \n");
	printf("EX: if you wanted to run 5 processes, 3 to run simultaneously and have each process perform 2 iterations, then it'd look like:\n");
	printf("./oss -n 5 -s 3 -t 2\n"); 
}

int main(int argc, char **argv) { 
	int opt; 
	const char optstr[] = "hn:s:t:"; 
	int proc = 0; // total number of processes 
	int simul = 0; // maximum number of child processes that can simultaneously run
	char *iter; // number of iterations 
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
				iter = optarg; 
				break; 
				
		}
	}

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

