#include "os.h"


hardware hw;
process process;
user user;

/******************** Hardware Class ********************/

hardware::hardware() {
    memoryAvailable = 4096;
}

void hardware::takeMemory(int requestedMemory) {
    if(memoryAvailable > requestedMemory) {
        memoryAvailable = memoryAvailable - requestedMemory;
    }
    else {
        cout << "Not enough memory" << endl;
    }
}

void hardware::returnMemory(int returnedMemory) {
    memoryAvailable += returnedMemory;
}

int hardware::getMemory() {
    return memoryAvailable;
}

/******************** Process Class ********************/


process::process() {
    jobs.push_back("job1.txt");
    jobs.push_back("job2.txt");
    jobs.push_back("job3.txt");
    jobs.push_back("job4.txt");
    jobIncrement = -1;
    cycle = 200000;
    done = false;
    quantum = 10;
    //op1 = 0;
    //op2 = 0;
    //op3 = 0;
    //op4 = 0;
}

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
                //op1 = jobsInSystem[jobIncrement].operation1_time;
            }
            else {
                jobsInSystem[jobIncrement].operation1_time = rand() % 100 + 1;
                //op1 = jobsInSystem[jobIncrement].operation1_time;
            }
        }
        else if (j == 3) {
            jobsInSystem[jobIncrement].process_operation2 = contents;
            if (jobsInSystem[jobIncrement].process_operation2 == "i/o") {
                jobsInSystem[jobIncrement].operation2_time = rand() % 50 + 25;
                //op2 = jobsInSystem[jobIncrement].operation2_time;
            }
            else {
                jobsInSystem[jobIncrement].operation2_time = rand() % 100 + 1;
                //op2 = jobsInSystem[jobIncrement].operation2_time;
            }
        }
        else if (j == 4) {
            jobsInSystem[jobIncrement].process_operation3 = contents;
            if (jobsInSystem[jobIncrement].process_operation3 == "i/o") {
                jobsInSystem[jobIncrement].operation3_time = rand() % 50 + 25;
                //op3 = jobsInSystem[jobIncrement].operation3_time;
            }
            else {
                jobsInSystem[jobIncrement].operation3_time = rand() % 100 + 1;
                //op3 = jobsInSystem[jobIncrement].operation3_time;
            }
        }
        else if (j == 5) {
            jobsInSystem[jobIncrement].process_operation4 = contents;
            if (jobsInSystem[jobIncrement].process_operation4 == "i/o") {
                jobsInSystem[jobIncrement].operation4_time = rand() % 50 + 25;
                //op4 = jobsInSystem[jobIncrement].operation4_time;
            }
            else {
                jobsInSystem[jobIncrement].operation4_time = rand() % 100 + 1;
                //op4 = jobsInSystem[jobIncrement].operation4_time;
            }
        }
        else if (j == 6) {
            if (contents == "EXE") {
                cout << endl
                     << "STARTING JOB EXECUTION" << endl;
                longTerm();
            }
        }
    }
    cout << "PROCESS MEM REQUIREMENT: " << jobsInSystem[jobIncrement].process_mem_required << "mb" << endl;
    cout << "JOB NAME: " << jobsInSystem[jobIncrement].job_name << " " << endl;
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation1 << " " << endl;
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation2 << " " << endl;
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation3 << " " << endl;
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation4 << " " << endl;
  
   
}

void process::cpuThread(int jobNumber) {
    string job;
    int op1,op2,op3,op4;
    op1 = 0;
    op2 = 0;
    op3 = 0;
    op4 = 0;

    op1 = jobsInSystem[jobIncrement].operation1_time;
    op2 = jobsInSystem[jobIncrement].operation2_time;
    op3 = jobsInSystem[jobIncrement].operation3_time;
    op4 = jobsInSystem[jobIncrement].operation4_time;

    job = jobsInSystem[jobNumber].job_name;
    readyQueue.pop();

    cout << "Job Name: ";
    cout << job << endl;

    int mem = jobsInSystem[jobNumber].process_mem_required;
    hw.takeMemory(mem);
    if (op1 > 0) {
        cout << "Operation is: " << jobsInSystem[jobNumber].process_operation1 << endl;
        cout << "Time: " << op1 << endl;
        op1 = op1 - quantum;
        cout << "Time left: " << op1 << endl;
        if (op1 > 0) {
            readyQueue.push(jobNumber);
        }       
    } else if (op1 <= 0) {
        cout << "Process: " << jobsInSystem[jobNumber].process_operation1 << " finished" << endl;
        if (op2 > 11) {
            cout << "Operation is: " << jobsInSystem[jobNumber].process_operation2 << endl;
            cout << "Time: " << op2 << endl;
            op2 = op2 - quantum;
            cout << "Time left: " << op2 << endl;
            if (op2 > 0) {
                readyQueue.push(jobNumber);
            } 
        } else if (op2 <= 0) {
            cout << "Process: " << jobsInSystem[jobNumber].process_operation2 << " finished" << endl;
            if (op3 > 11) {
                cout << "Operation is: " << jobsInSystem[jobNumber].process_operation3 << endl;
                cout << "Time: " << op3 << endl;
                op3 = op3 - quantum;
                cout << "Time left: " << op3 << endl;
                if (op3 > 0) {
                    readyQueue.push(jobNumber);
                } 
            } else if (op3 <= 0) {
                cout << "Process: " << jobsInSystem[jobNumber].process_operation3 << " finished" << endl;
                if (op4 > 11) {
                    cout << "Operation is: " << jobsInSystem[jobNumber].process_operation4 << endl;
                    cout << "Time: " << op4 << endl;
                    op4 = op4 - quantum;
                    cout << "Time left: " << op4 << endl;
                    if (op4 > 0) {
                        readyQueue.push(jobNumber);
                    } 
                } else if (op4 <= 0) {
                    cout << "Process: " << jobsInSystem[jobNumber].process_operation4 << " finished" << endl << endl << endl;
                    hw.returnMemory(mem);
                }
            }
        }
    }
    cout << endl << endl << endl;
}



void process::roundRobin(vector<process_control_block> jobsInSystem) {
    cout << "Total Jobs: " << jobIncrement << endl;
    int k = 0;
    while (k < 5) {
        cout << endl << endl << "****** Cycle:  " << k << " ******" << endl << endl;
        thread cpu1(&process::cpuThread, this, readyQueue.front());
        cpu1.join();
        thread cpu2(&process::cpuThread, this, readyQueue.front());
        cpu2.join();
        thread cpu3(&process::cpuThread, this, readyQueue.front());
        cpu3.join();
        thread cpu4(&process::cpuThread, this, readyQueue.front());    
        cpu4.join();
        k++;
        sleep(1);
    }
}

void process::longTerm() {
    //move new queue items to ready queue
    readyQueue.push(newQueue.front());
    newQueue.pop();
}


/******************** User Class ********************/

user::user() {}

void user::userInput() {
    getline(cin,input);
}


string user::detectInput() {
    return input;
}

bool user::startUserMode() {
    int i = 0;
    cout << "Waiting for input..." << endl;
    while(1) { 
        getline(cin, commandInput);
        if (commandInput == "proc") {
            cout << "Input recieved " << commandInput << endl;
        } else if (commandInput == "mem") {
            hw.memoryUsed = hw.getMemory() - hw.memory;
            hw.percentMemory = (hw.memoryUsed / hw.memory) * 100;
            cout << endl << "Current memory usage: " << hw.memoryUsed << " MB"<< " (" << hw.percentMemory << "%)" << endl;
        } else if (commandInput == "load" ) {
            for(int i = 0; i < 4; i++) {
                process.openJob(process.jobs[i]);
            }
            /*cout << "ready q size: " << process.readyQueue.size() << endl;
            for(i = 0; i < 4; i++) {
                cout << process.readyQueue.front() << endl;
                process.readyQueue.pop();
            }*/ 
            process.roundRobin(process.jobsInSystem);        
        } else if (commandInput == "exe") {
            cout << commandInput << endl;
        } else if (commandInput == "reset") {
            cout << "detected ";
            cout << commandInput << endl;
        } else if (commandInput == "exit") {
            cout << "Exiting User Mode" << endl;
            return true;
        }
        i++;
    }
}
