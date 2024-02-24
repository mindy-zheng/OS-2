# OS-2: Adding Functionality to our System
-----------------------------------
This program builds off of our previous project with more specific additions to the command line and our children launching. First, we hvae a simulated system clock (ran by our program manually) present in our shared memory. Our project is kinda dependent on our system clock. It tells us the bound at which we call our children (randomly)), as long as how often we should launch a child process. Our process control block will give us extensive details about our processes such as what entries are occupied, not occupied, and the starting and ending time.  

## How to run: 
Run 'make'. 
Make sure you include the arguments needed. For example: ./oss -n 6 -s 2 -t 100 -i 39999

## Problems During Testing: 
None outstanding that I know of. 
