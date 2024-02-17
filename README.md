# OS-1: Skeleton multiple processes 
-----------------------------------
This program enters a loop that runs as many times as the child processes specified by the user (-n). In each iteration, the program forks to create a child process. The user is passed a number of iterations also specified by the user (-t). Lastly, a counter keeps track of the number of running child processes. After all child processes has been created, the remaining will finish before termination. 

## How to run: 
This can only be ran from the oss. First, run the command: make or make all. 
As an example, if you wanted to launch oss with 3 user processes but never allow more than 2 to be running simultaneously in addition to 5 iterations, then this would need to be entered in the terminal: 

./oss -n 3 -s 2 -t 5 

## Problems During Testing: 
There weren't any outstanding problems during testing. 
