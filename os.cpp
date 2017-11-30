#include "os.h"

/*
Creating objects for each class
*/
hardware hw;
process process;
user user;

/******************** Hardware Class ********************/

/*
Constructor for hardware class
Initialize memory available and percent memory
*/
hardware::hardware() {
    memoryAvailable = 4096;
    percentMemory = 0.0;
}

/*
Removes requested memory from memory bank
Parameter: requestedMemory - Memory required for each process/job
*/
void hardware::takeMemory(int requestedMemory) {
    if(memoryAvailable > requestedMemory) {
        memoryAvailable = memoryAvailable - requestedMemory;
    }
    else {
        cout << "Not enough memory" << endl;
    }
}

/*
Returns memory after job is finished
Parameter: returnedMemory - how much memory the job borrowed and is returning.
*/
void hardware::returnMemory(int returnedMemory) {
    memoryAvailable += returnedMemory;
}

/*
Getter for memory
Return: memory used by a single job.
*/
int hardware::getMemory() {
    return memory - memoryAvailable;
}

/*
Used in resetData() to reset memory back to 4096 MB
*/
void hardware::resetMemory() {
    memoryAvailable = 4096;
    cout << "Memory has been reset" << endl;
}

/*
Takes in memory used by a job and calculates the percentage out of the total memory
Parameter: mem - Memory used by job.
Return: percentMemory - percent out of the total memory
*/
float hardware::getPercentMemory(int mem) {
    percentMemory = (float(mem) / float(memory)) * 100;
    return percentMemory;
}

/******************** Process Class ********************/

/*
Constructor process class
Loading in preset jobs into the jobs vector to be loaded into the PCB
Initializing varibles needed for algorithm and job loader
*/
process::process() {
    jobs.push_back("job1.txt");
    jobs.push_back("job2.txt");
    jobs.push_back("job3.txt");
    jobs.push_back("job4.txt");
    jobs.push_back("job5.txt");
    jobs.push_back("job6.txt");
    jobs.push_back("job7.txt");
    jobs.push_back("job8.txt");
    jobs.push_back("job9.txt");
    jobs.push_back("job10.txt");
    jobIncrement = -1;
    cycle = 200000;
    quantum = 10;
}

/*
Takes jobs from preloaded vector and loads all job information into the pcb as well
as print information about the job as well as moving each job into the newQueue and running
the long term scheduler once fully complete.
Parameter: job - Name of job like "job1.txt"
*/
void process::openJob(string job) {
    jobIncrement++;
    fstream fs;
    string contents;
    fs.open(job);
    if(fs.fail()) {
        cerr << "ERROR: File could not be opened." << endl;
    }
    else {
        cout << "FILE OPENED" << endl;
    }
    jobsInSystem[jobIncrement].PID = jobIncrement;
    newQueue.push(jobsInSystem[jobIncrement].PID);
    for (int j = 0; j < 7; j++){
        fs >> contents;
        if (j == 0) {
            jobsInSystem[jobIncrement].process_mem_required = stoi(contents);
        }
        else if (j == 1) {
            jobsInSystem[jobIncrement].job_name = contents;
            
        }
        else if (j == 2) {
            jobsInSystem[jobIncrement].process_operation1 = contents;
            if (jobsInSystem[jobIncrement].process_operation1 == "i/o") {
                jobsInSystem[jobIncrement].operation1_time = rand() % 50 + 25;
                jobsInSystem[jobIncrement].totalTime += jobsInSystem[jobIncrement].operation1_time;

            }
            else {
                jobsInSystem[jobIncrement].operation1_time = rand() % 100 + 1;
                jobsInSystem[jobIncrement].totalTime += jobsInSystem[jobIncrement].operation1_time;
            }
        }
        else if (j == 3) {
            jobsInSystem[jobIncrement].process_operation2 = contents;
            if (jobsInSystem[jobIncrement].process_operation2 == "i/o") {
                jobsInSystem[jobIncrement].operation2_time = rand() % 50 + 25;
                jobsInSystem[jobIncrement].totalTime += jobsInSystem[jobIncrement].operation2_time;
            }
            else {
                jobsInSystem[jobIncrement].operation2_time = rand() % 100 + 1;
                jobsInSystem[jobIncrement].totalTime += jobsInSystem[jobIncrement].operation2_time;
            }
        }
        else if (j == 4) {
            jobsInSystem[jobIncrement].process_operation3 = contents;
            if (jobsInSystem[jobIncrement].process_operation3 == "i/o") {
                jobsInSystem[jobIncrement].operation3_time = rand() % 50 + 25;
                jobsInSystem[jobIncrement].totalTime += jobsInSystem[jobIncrement].operation3_time;
            }
            else {
                jobsInSystem[jobIncrement].operation3_time = rand() % 100 + 1;
                jobsInSystem[jobIncrement].totalTime += jobsInSystem[jobIncrement].operation3_time;
            }
        }
        else if (j == 5) {
            jobsInSystem[jobIncrement].process_operation4 = contents;
            if (jobsInSystem[jobIncrement].process_operation4 == "i/o") {
                jobsInSystem[jobIncrement].operation4_time = rand() % 50 + 25;
                jobsInSystem[jobIncrement].totalTime += jobsInSystem[jobIncrement].operation4_time;
            }
            else {
                jobsInSystem[jobIncrement].operation4_time = rand() % 100 + 1;
                jobsInSystem[jobIncrement].totalTime += jobsInSystem[jobIncrement].operation4_time;
            }
        }
        else if (j == 6) {
            if (contents == "EXE") {
                cout << endl
                     << "STARTING JOB EXECUTION" << endl;
                jobsInSystem[jobIncrement].timeLeft = jobsInSystem[jobIncrement].totalTime;
                longTerm();
            }
        }
    }
    cout << "PROCESS MEM REQUIREMENT: " << jobsInSystem[jobIncrement].process_mem_required << "mb" << endl;
    cout << "JOB NAME, PID: " << jobsInSystem[jobIncrement].job_name << " ," << jobsInSystem[jobIncrement].PID << endl;
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation1 << " time: " << jobsInSystem[jobIncrement].operation1_time << endl;
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation2 << " time: " << jobsInSystem[jobIncrement].operation2_time << endl;
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation3 << " time: " << jobsInSystem[jobIncrement].operation3_time << endl;
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation4 << " time: " << jobsInSystem[jobIncrement].operation4_time << endl;
    cout << "TOTAL TIME: " << jobsInSystem[jobIncrement].totalTime << endl;
  
   
}

/*
Random input files generator that prompts user and asked them how many jobs they would like to create.
After generating the job, it will call the long term scheduler and move jobs from newQueue to readQueue.
Parameter: numFiles - number of files user wants to create.
*/
void process::randGen(int numFiles) {
    string names[] = {"vivado","modelsim","netbeans","mozilla","clion","paint","word","visual_studio","runescape","task_manager"};
    string operation[] = {"i/o","out","yield","calculate"};
    for (int i = 0; i < numFiles; i++) {
        jobIncrement++;
        //cout << names[rand() % 9 + 0] << endl;
        jobsInSystem[jobIncrement].PID = jobIncrement;
        newQueue.push(jobIncrement);
        jobsInSystem[jobIncrement].job_name = names[rand() % 9 + 0];
        jobsInSystem[jobIncrement].process_operation1 = operation[rand() % 3 + 0];
        jobsInSystem[jobIncrement].process_operation2 = operation[rand() % 3 + 0];
        jobsInSystem[jobIncrement].process_operation3 = operation[rand() % 3 + 0];
        jobsInSystem[jobIncrement].process_operation4 = operation[rand() % 3 + 0];

        if(jobsInSystem[jobIncrement].process_operation1 == "i/o") {
            jobsInSystem[jobIncrement].operation1_time = rand() % 50 + 25;
            jobsInSystem[jobIncrement].totalTime = jobsInSystem[jobIncrement].operation1_time;
        } else {
            jobsInSystem[jobIncrement].operation1_time = rand() % 100 + 1;
            jobsInSystem[jobIncrement].totalTime = jobsInSystem[jobIncrement].operation1_time;
        }

        if(jobsInSystem[jobIncrement].process_operation2 == "i/o") {
            jobsInSystem[jobIncrement].operation2_time = rand() % 50 + 25;
            jobsInSystem[jobIncrement].totalTime = jobsInSystem[jobIncrement].operation2_time;
        } else {
            jobsInSystem[jobIncrement].operation2_time = rand() % 100 + 1;
            jobsInSystem[jobIncrement].totalTime = jobsInSystem[jobIncrement].operation2_time;
        }

        if(jobsInSystem[jobIncrement].process_operation3 == "i/o") {
            jobsInSystem[jobIncrement].operation3_time = rand() % 50 + 25;
            jobsInSystem[jobIncrement].totalTime = jobsInSystem[jobIncrement].operation3_time;
        } else {
            jobsInSystem[jobIncrement].operation3_time = rand() % 100 + 1;
            jobsInSystem[jobIncrement].totalTime = jobsInSystem[jobIncrement].operation3_time;
        }

        if(jobsInSystem[jobIncrement].process_operation4 == "i/o") {
            jobsInSystem[jobIncrement].operation4_time = rand() % 50 + 25;
            jobsInSystem[jobIncrement].totalTime = jobsInSystem[jobIncrement].operation4_time;
        } else {
            jobsInSystem[jobIncrement].operation4_time = rand() % 100 + 1;
            jobsInSystem[jobIncrement].totalTime = jobsInSystem[jobIncrement].operation4_time;
        }

        jobsInSystem[jobIncrement].process_mem_required = rand() % 1 + 1028;
        jobsInSystem[jobIncrement].timeLeft = jobsInSystem[jobIncrement].totalTime;

        cout << endl << endl;
        cout << "PROCESS MEM REQUIREMENT: " << jobsInSystem[jobIncrement].process_mem_required << "mb" << endl;
        cout << "JOB NAME, PID: " << jobsInSystem[jobIncrement].job_name << " ," << jobsInSystem[jobIncrement].PID << endl;
        cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation1 << " time: " << jobsInSystem[jobIncrement].operation1_time << endl;
        cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation2 << " time: " << jobsInSystem[jobIncrement].operation2_time << endl;
        cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation3 << " time: " << jobsInSystem[jobIncrement].operation3_time << endl;
        cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation4 << " time: " << jobsInSystem[jobIncrement].operation4_time << endl;
        cout << "TOTAL TIME: " << jobsInSystem[jobIncrement].totalTime << endl;
        cout << endl;
        longTerm();

    }

}


/*
Algorithm that functions a single cpu thread that takes in 1 job and decrements the time by 1 quantum and as well as
gathers useful information like iocycles, time spent in cpu, time left to spend in cpu, and current operation
used to give information to 'proc' command. Also pushes and pops jobs from the readyQueue and pushes jobs into
the waitQueue if current operation is i/o or yield. Services out operation by printing pcb information to the 
terminal.
Paramter: jobNumber - PID of job used to access PCB data
*/
void process::cpuThread(int jobNumber) {
    string job;

    job = jobsInSystem[jobNumber].job_name;
    if (readyQueue.size() > 0) {
        readyQueue.pop();
    }

    cout << "Job Name: ";
    cout << job << endl;
    int mem = jobsInSystem[jobNumber].process_mem_required;
    hw.takeMemory(mem);
    cout << endl << "Current memory usage: " << hw.getMemory() << " MB"<< " (" << std::fixed << std::setprecision(2) << hw.getPercentMemory(hw.getMemory()) << "%)" << endl;
    if (jobsInSystem[jobNumber].operation1_time > 0) {
        cout << "Operation is: " << jobsInSystem[jobNumber].process_operation1 << endl;
        jobsInSystem[jobNumber].currentOperation = jobsInSystem[jobNumber].process_operation1;
        cout << "Time: " << jobsInSystem[jobNumber].operation1_time << endl;
        jobsInSystem[jobNumber].operation1_time = jobsInSystem[jobNumber].operation1_time - quantum;
        jobsInSystem[jobNumber].timeElapsed += quantum;
        cout << "Time left: " << jobsInSystem[jobNumber].operation1_time << endl;

        if (jobsInSystem[jobNumber].process_operation1 == "i/o") {
            jobsInSystem[jobNumber].ioCycles++;
        }
        
        if (jobsInSystem[jobNumber].process_operation1 == "i/o" || jobsInSystem[jobNumber].process_operation1 == "yield") {
            cout << jobsInSystem[jobNumber].job_name << " is pushed to the wait queue for: " << float(jobsInSystem[jobNumber].operation1_time) / 10 << " cycles" << endl;
            waitQueue.push(jobNumber);
        }

        if (jobsInSystem[jobNumber].process_operation1 == "out") {
            cout << endl << endl << "Out operation detected" << endl;
            cout << "PID: " << jobNumber << endl;
            cout << "Unfinished process name: " << jobsInSystem[jobNumber].job_name << endl;
            cout << "Current process operation: " << jobsInSystem[jobNumber].currentOperation << endl;
            cout << "Time needed to complete: " << jobsInSystem[jobNumber].timeLeft << endl;
            cout << "Time already completed: " << jobsInSystem[jobNumber].timeElapsed << endl;
            cout << "I/O requests performed: " <<  jobsInSystem[jobNumber].ioCycles << endl;
            }

        readyQueue.push(jobNumber);     
    } else if (jobsInSystem[jobNumber].operation1_time <= 0) {
        cout << "Process: " << jobsInSystem[jobNumber].process_operation1 << " finished" << endl << endl << endl;
        if (jobsInSystem[jobNumber].operation2_time > 0) {
            cout << endl << "Operation Two PHASE" << endl;
            cout << "Operation is: " << jobsInSystem[jobNumber].process_operation2 << endl;
            jobsInSystem[jobNumber].currentOperation = jobsInSystem[jobNumber].process_operation2;
            cout << "Time: " << jobsInSystem[jobNumber].operation2_time << endl;
            jobsInSystem[jobNumber].operation2_time = jobsInSystem[jobNumber].operation2_time - quantum;
            jobsInSystem[jobNumber].timeElapsed += quantum;
            cout << "Time left: " << jobsInSystem[jobNumber].operation2_time << endl;

            if (jobsInSystem[jobNumber].process_operation2 == "i/o") {
                jobsInSystem[jobNumber].ioCycles++;
            }

            if (jobsInSystem[jobNumber].process_operation2 == "i/o" || jobsInSystem[jobNumber].process_operation2 == "yield") {
                cout << jobsInSystem[jobNumber].job_name << " is pushed to the wait queue for: " << float(jobsInSystem[jobNumber].operation2_time) / 10 << " cycles" << endl;
                waitQueue.push(jobNumber);
            }
            
            if (jobsInSystem[jobNumber].process_operation2 == "out") {
                    cout << endl << endl << "Out operation detected" << endl;
                    cout << "PID: " << jobNumber << endl;
                    cout << "Unfinished process name: " << jobsInSystem[jobNumber].job_name << endl;
                    cout << "Current process operation: " << jobsInSystem[jobNumber].currentOperation << endl;
                    cout << "Time needed to complete: " << jobsInSystem[jobNumber].timeLeft << endl;
                    cout << "Time already completed: " << jobsInSystem[jobNumber].timeElapsed << endl;
                    cout << "I/O requests performed: " <<  jobsInSystem[jobNumber].ioCycles << endl; 
            }

            readyQueue.push(jobNumber);
        } else if (jobsInSystem[jobNumber].operation2_time <= 0) {
            cout << "Process: " << jobsInSystem[jobNumber].process_operation2 << " finished" << endl << endl << endl;
            if (jobsInSystem[jobNumber].operation3_time > 0) {
                cout << endl << "Operation Three PHASE" << endl;
                cout << "Operation is: " << jobsInSystem[jobNumber].process_operation3 << endl;
                jobsInSystem[jobNumber].currentOperation = jobsInSystem[jobNumber].process_operation3;
                cout << "Time: " << jobsInSystem[jobNumber].operation3_time << endl;
                jobsInSystem[jobNumber].operation3_time = jobsInSystem[jobNumber].operation3_time - quantum;
                jobsInSystem[jobNumber].timeElapsed += quantum;
                cout << "Time left: " << jobsInSystem[jobNumber].operation3_time << endl;

                if (jobsInSystem[jobNumber].process_operation3 == "i/o") {
                    jobsInSystem[jobNumber].ioCycles++;
                }

                if (jobsInSystem[jobNumber].process_operation3 == "i/o" || jobsInSystem[jobNumber].process_operation3 == "yield") {
                    cout << jobsInSystem[jobNumber].job_name << " is pushed to the wait queue for: " << float(jobsInSystem[jobNumber].operation3_time) / 10 << " cycles" << endl;
                    waitQueue.push(jobNumber);
                } 

                if (jobsInSystem[jobNumber].process_operation3 == "out") {
                    cout << endl << endl << "Out operation detected" << endl;
                    cout << "PID: " << jobNumber << endl;
                    cout << "Unfinished process name: " << jobsInSystem[jobNumber].job_name << endl;
                    cout << "Current process operation: " << jobsInSystem[jobNumber].currentOperation << endl;
                    cout << "Time needed to complete: " << jobsInSystem[jobNumber].timeLeft << endl;
                    cout << "Time already completed: " << jobsInSystem[jobNumber].timeElapsed << endl;
                    cout << "I/O requests performed: " <<  jobsInSystem[jobNumber].ioCycles << endl; 
                }

                readyQueue.push(jobNumber);
            } else if (jobsInSystem[jobNumber].operation3_time <= 0) {
                cout << "Process: " << jobsInSystem[jobNumber].process_operation3 << " finished" << endl << endl << endl;
                if (jobsInSystem[jobNumber].operation4_time > 0) {
                    cout << endl << "Operation Four PHASE" << endl;
                    cout << "Operation is: " << jobsInSystem[jobNumber].process_operation4 << endl;
                    jobsInSystem[jobNumber].currentOperation = jobsInSystem[jobNumber].process_operation4;
                    cout << "Time: " << jobsInSystem[jobNumber].operation4_time << endl;
                    jobsInSystem[jobNumber].operation4_time = jobsInSystem[jobNumber].operation4_time - quantum;
                    jobsInSystem[jobNumber].timeElapsed += quantum;
                    cout << "Time left: " << jobsInSystem[jobNumber].operation4_time << endl;

                    if (jobsInSystem[jobNumber].process_operation4 == "i/o") {
                        jobsInSystem[jobNumber].ioCycles++;
                    }

                    if (jobsInSystem[jobNumber].process_operation4 == "i/o" || jobsInSystem[jobNumber].process_operation4 == "yield") {
                        cout << jobsInSystem[jobNumber].job_name << " is pushed to the wait queue for: " << float(jobsInSystem[jobNumber].operation4_time) / 10 << " cycles" << endl;
                        waitQueue.push(jobNumber);
                    }
                    

                    if (jobsInSystem[jobNumber].process_operation4 == "out") {
                        cout << endl << endl << "Out operation detected" << endl;
                        cout << "PID: " << jobNumber << endl;
                        cout << "Unfinished process name: " << jobsInSystem[jobNumber].job_name << endl;
                        cout << "Current process operation: " << jobsInSystem[jobNumber].currentOperation << endl;
                        cout << "Time needed to complete: " << jobsInSystem[jobNumber].timeLeft << endl;
                        cout << "Time already completed: " << jobsInSystem[jobNumber].timeElapsed << endl;
                        cout << "I/O requests performed: " <<  jobsInSystem[jobNumber].ioCycles << endl; 
                    }
                    readyQueue.push(jobNumber);
                } else if (jobsInSystem[jobNumber].operation4_time <= 0) {
                    cout << "Process: " << jobsInSystem[jobNumber].process_operation4 << " finished" << endl << endl << endl;
                    hw.returnMemory(mem);
                    cout << endl << endl << endl;
                    return;
                }
            }
        }
    }
    cout << endl << endl << endl;
    hw.returnMemory(mem);
}

/*
Short term scheduler that uses round robin to pull jobs from the readyQueue and pushes them into the cpu. 
It runs 1 cpu core and 4 threads. It also services user input to stop/pause mid execution and sends user back 
user mode to run commands.
Parameter: jobsInSystem - vector of type pcb that contains all information regarding each job.
           k - integer containing number of cycles the user wants to run the os for.
           threadSelect - bool that chooses between which threading method the user wants the short term
                          scheduler to use.
*/
void process::roundRobin(vector<process_control_block> jobsInSystem, int k, bool threadSelect) {
    cout << "Total Jobs: " << jobIncrement << endl;
    int i = 0;
    thread t1(&user::userInput, &user);
    t1.detach();
    while (i < k) {
        cout << endl << endl << "****** Cycle:  " << i << " ******" << endl << endl;
        if (!readyQueue.empty()) {
            if (threadSelect == 0) {
                thread cpu1(&process::cpuThread, this, readyQueue.front());
                cpu1.join();
                thread cpu2(&process::cpuThread, this, readyQueue.front());
                cpu2.join();
                thread cpu3(&process::cpuThread, this, readyQueue.front());
                cpu3.join();
                thread cpu4(&process::cpuThread, this, readyQueue.front());    
                cpu4.join();
            } else if (threadSelect == 1) {
                thread cpu1(&process::cpuThread, this, readyQueue.front());
                thread cpu2(&process::cpuThread, this, readyQueue.front());
                thread cpu3(&process::cpuThread, this, readyQueue.front());
                thread cpu4(&process::cpuThread, this, readyQueue.front());    
                cpu1.join();
                cpu2.join();
                cpu3.join();
                cpu4.join();
            }
        }
        if (user.detectInput() == "stop") {
            cout << "Ready Queue size: " << readyQueue.size() << endl;
            break;
        }
        else if (!user.detectInput().empty()) {
            thread t1(&user::userInput, &user);
            t1.detach();
        }
        cout << endl << endl << "Jobs in ready queue: " << readyQueue.size() << endl << endl;
        if (readyQueue.size() == 0) {
            cout << "Done servicing all processes" << endl;
            readyQueue = {};
            cout << "Type 'd' to return to user mode, you have 5 seconds.." << endl;
            break;
        } 
        i++;
        sleep(1);
    }
}

/*
Long term scheduler that moves jobs from newQueue to readyQueue when their PCB is fully loaded.
*/
void process::longTerm() {
    //move new queue items to ready queue
    readyQueue.push(newQueue.front());
    newQueue.pop();
}

/*
Function run when the user types 'reset' that will re-initialize all variables and reload all
jobs back into the jobs vector. It will also reset all queue's as well as delete all progress 
that each job has made within the cpu.
*/
void process::resetData() {
    jobIncrement = -1;
    jobs.clear();
    cout << "jobs vector cleared size is: " << jobs.size() << endl;
    jobsInSystem.clear();
    readyQueue = {};
    newQueue = {};
    cout << "new q size: " <<  newQueue.size() << endl;
    cout << "ready q size: " << readyQueue.size() << endl;
    jobs.push_back("job1.txt");
    jobs.push_back("job2.txt");
    jobs.push_back("job3.txt");
    jobs.push_back("job4.txt");
    jobs.push_back("job5.txt");
    jobs.push_back("job6.txt");
    jobs.push_back("job7.txt");
    jobs.push_back("job8.txt");
    jobs.push_back("job9.txt");
    jobs.push_back("job10.txt");
    hw.resetMemory();
    cout << "System reset" << endl;
}

/******************** User Class ********************/

/*
Constructor for user class
*/
user::user() {}

/*
Function created as a seperate thread to detect user input asynchronously
*/
void user::userInput() {
    getline(cin,input);
}

/*
Getter for user input so that user mode can service the input
*/
string user::detectInput() {
    return input;
}

/*
Function that services all user commands as well as exits user mode to go back to kernel mode
*/
void user::startUserMode() {
    int i = 0;
    while(1) { 
        cout << endl << "Waiting for user input..." << endl;
        getline(cin, commandInput);
        cout << "RECIEVED " << commandInput << endl;
        if (commandInput == "proc") {
            if (process.readyQueue.size() == 0) {
                cout << "ERROR: no jobs in the ready queue" << endl; 

            }
            queue <int> procQueue;
            procQueue = process.readyQueue;
            int size = procQueue.size();

            if (procQueue.size() > 0) {
                for (int i = 0; i < size; i++) {

                    process.jobsInSystem[procQueue.front()].timeLeft = process.jobsInSystem[procQueue.front()].totalTime - process.jobsInSystem[procQueue.front()].timeElapsed;

                    cout << "PID: " << procQueue.front() << endl;
                    cout << "Unfinished process name: " << process.jobsInSystem[procQueue.front()].job_name << endl;
                    cout << "Current process operation: " << process.jobsInSystem[procQueue.front()].currentOperation << endl;
                    cout << "Time needed to complete: " << process.jobsInSystem[procQueue.front()].timeLeft << endl;
                    cout << "Time already completed: " << process.jobsInSystem[procQueue.front()].timeElapsed << endl;
                    cout << "I/O requests performed: " <<  process.jobsInSystem[procQueue.front()].ioCycles << endl;                

                    procQueue.pop();
                    cout << endl << endl;
                }
            } else if (procQueue.size() == 0) {
                cout << endl << "ERROR: There are no unfinished processes" << endl;
            }


        } else if (commandInput == "mem") {
            cout << endl << "Current memory usage: " << hw.getMemory() << " MB"<< " (" << hw.getPercentMemory(hw.getMemory()) << "%)" << endl;
        } else if (commandInput == "load" ) {
            for(int i = 0; i < 10; i++) {
                process.openJob(process.jobs[i]);
            }        
        } else if (commandInput == "exe") {
            if (process.readyQueue.size() <= 0) {
                cout << endl << "ERROR: There are no jobs in the ready queue" << endl;
            } else {
                cout << endl << endl;
                int cycles = 0;
                bool type;
                cout << "How many cycles would you like to run?" << endl;
                cin >> cycles;
                cout << endl;
                cout << "Select thread type.." << endl;
                cout << "'1' = multithreading" << endl;
                cout << "'0' = singlethreading" << endl;
                cin >> type;
                cin.clear();
                cin.ignore(10000,'\n');
                process.roundRobin(process.jobsInSystem, cycles, type);
                sleep(2);
                if (detectInput() == "d") {
                }
                sleep(2);

            }
        } else if (commandInput == "reset") {
            process.resetData();

        } else if (commandInput == "rand") {
            cout << "How many files would you like to create?" << endl;
            int numFiles;
            cin >> numFiles;
            process.randGen(numFiles);
        } else if (commandInput == "exit") {
            cout << endl;
            cout << "---------------------" << endl;
            cout << "| Exiting User Mode |" << endl;
            cout << "=--------------------" << endl << endl;
            cout << "Type 'user' to enter user mode and use os commands" << endl;
            cout << "Type 'exit' to abort program" << endl;
            return;
        } else {
            cout << "unsupported command - try again please" << endl;
        }
        i++;
    }
}
