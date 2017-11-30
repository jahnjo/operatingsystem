# operatingsystem

Authors:
John Foster - V00699030
Adeeb Stwodah - V00702089
Spandan Fadnis - V00708853

Dependencies:
unix
pthreads
c++11

to compile all the code 
    "g++ -std=c++11 -pthread os.cpp main.cpp"


USER GUIDE:

When program launched you will be ‘kernel mode’
2 input options: 

‘exit’ - exits program

‘user’ - will take you to ‘user mode’ where you can run all commands


User Mode:

In user mode you have the following commands:

‘load’ - loads all preset jobs into the pcb and will put them into the readyQueue to run.

‘proc’ - shows all unfinished jobs and all important information about each job. If you run proc before load
	 you will get an error as there are no jobs loaded yet.

‘exe’  - you will be asked how many cycles you would like to run the os. However, if all the jobs are finished before
	 the # of cycles chosen are reaches the os will send you back to user mode.

	 WHILE IN EXE:
	 You have the option to stop mid execution and you will be returned to user mode by typing ‘stop’.

	 NOTE: When the os is done servicing all the jobs you will have 5 seconds to type ‘d’ to go back to user mode 
	 or the os will exit.

‘mem’  - shows current memory usage and percentage as well. Mem will run on its own after you run ‘exe’ and show memory
	 usage for each job and as they are entering the cpu. If you run ‘men’ while stopped mem usage will be 0 because all
	 jobs are returned to their respective queues and removed from the cpu. 


‘reset’ - Resets all data within the os.

‘exit  - Returns user back to ‘kernel mode’.


