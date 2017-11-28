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

void hardware::resetMemory() {
    memoryAvailable = 4096;
    cout << "Memory has been reset" << endl;
}

/******************** Process Class ********************/


process::process() {
    jobs.push_back("job1.txt");
    jobs.push_back("job2.txt");
    jobs.push_back("job3.txt");
    jobs.push_back("job4.txt");
    jobIncrement = -1;
    cycle = 200000;
    quantum = 10;
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
            }
            else {
                jobsInSystem[jobIncrement].operation1_time = rand() % 100 + 1;
            }
        }
        else if (j == 3) {
            jobsInSystem[jobIncrement].process_operation2 = contents;
            if (jobsInSystem[jobIncrement].process_operation2 == "i/o") {
                jobsInSystem[jobIncrement].operation2_time = rand() % 50 + 25;
            }
            else {
                jobsInSystem[jobIncrement].operation2_time = rand() % 100 + 1;
            }
        }
        else if (j == 4) {
            jobsInSystem[jobIncrement].process_operation3 = contents;
            if (jobsInSystem[jobIncrement].process_operation3 == "i/o") {
                jobsInSystem[jobIncrement].operation3_time = rand() % 50 + 25;
            }
            else {
                jobsInSystem[jobIncrement].operation3_time = rand() % 100 + 1;
            }
        }
        else if (j == 5) {
            jobsInSystem[jobIncrement].process_operation4 = contents;
            if (jobsInSystem[jobIncrement].process_operation4 == "i/o") {
                jobsInSystem[jobIncrement].operation4_time = rand() % 50 + 25;
            }
            else {
                jobsInSystem[jobIncrement].operation4_time = rand() % 100 + 1;
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
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation1 << " time: " << jobsInSystem[jobIncrement].operation1_time << endl;
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation2 << " time: " << jobsInSystem[jobIncrement].operation2_time << endl;
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation3 << " time: " << jobsInSystem[jobIncrement].operation3_time << endl;
    cout << "NOW EXECUTING: " << jobsInSystem[jobIncrement].process_operation4 << " time: " << jobsInSystem[jobIncrement].operation4_time << endl;
  
   
}

void process::cpuThread(int jobNumber) {
    string job;

    //cout << endl << "**DEBUG MSG**" << endl << jobsInSystem[jobNumber].operation2_time << endl << endl;

    job = jobsInSystem[jobNumber].job_name;
    readyQueue.pop();

    cout << "Job Name: ";
    cout << job << endl;
    int mem = jobsInSystem[jobNumber].process_mem_required;
    hw.takeMemory(mem);
    cout << endl << "Current memory usage: " << hw.memoryAvailable << " MB"<< " (" << hw.percentMemory << "%)" << endl;
    if (jobsInSystem[jobNumber].operation1_time > 0) {
        cout << "Operation is: " << jobsInSystem[jobNumber].process_operation1 << endl;
        cout << "Time: " << jobsInSystem[jobNumber].operation1_time << endl;
        jobsInSystem[jobNumber].operation1_time = jobsInSystem[jobNumber].operation1_time - quantum;
        cout << "Time left: " << jobsInSystem[jobNumber].operation1_time << endl;
        readyQueue.push(jobNumber);     
    } else if (jobsInSystem[jobNumber].operation1_time <= 0) {
        cout << "Process: " << jobsInSystem[jobNumber].process_operation1 << " finished" << endl << endl << endl;
        if (jobsInSystem[jobNumber].operation2_time > 0) {
            cout << endl << "Operation Two PHASE" << endl;
            cout << "Operation is: " << jobsInSystem[jobNumber].process_operation2 << endl;
            cout << "Time: " << jobsInSystem[jobNumber].operation2_time << endl;
            jobsInSystem[jobNumber].operation2_time = jobsInSystem[jobNumber].operation2_time - quantum;
            cout << "Time left: " << jobsInSystem[jobNumber].operation2_time << endl;
            readyQueue.push(jobNumber);
        } else if (jobsInSystem[jobNumber].operation2_time <= 0) {
            cout << "Process: " << jobsInSystem[jobNumber].process_operation2 << " finished" << endl << endl << endl;
            if (jobsInSystem[jobNumber].operation3_time > 0) {
                cout << endl << "Operation Three PHASE" << endl;
                cout << "Operation is: " << jobsInSystem[jobNumber].process_operation3 << endl;
                cout << "Time: " << jobsInSystem[jobNumber].operation3_time << endl;
                jobsInSystem[jobNumber].operation3_time = jobsInSystem[jobNumber].operation3_time - quantum;
                cout << "Time left: " << jobsInSystem[jobNumber].operation3_time << endl;
                readyQueue.push(jobNumber);
            } else if (jobsInSystem[jobNumber].operation3_time <= 0) {
                cout << "Process: " << jobsInSystem[jobNumber].process_operation3 << " finished" << endl << endl << endl;
                if (jobsInSystem[jobNumber].operation4_time > 0) {
                    cout << endl << "Operation Four PHASE" << endl;
                    cout << "Operation is: " << jobsInSystem[jobNumber].process_operation4 << endl;
                    cout << "Time: " << jobsInSystem[jobNumber].operation4_time << endl;
                    jobsInSystem[jobNumber].operation4_time = jobsInSystem[jobNumber].operation4_time - quantum;
                    cout << "Time left: " << jobsInSystem[jobNumber].operation4_time << endl;
                    readyQueue.push(jobNumber);
                } else if (jobsInSystem[jobNumber].operation4_time <= 0) {
                    cout << "Process: " << jobsInSystem[jobNumber].process_operation4 << " finished" << endl << endl << endl;
                    hw.returnMemory(mem);
                }
            }
        }
    }
    cout << endl << endl << endl;
    hw.returnMemory(mem);
}



void process::roundRobin(vector<process_control_block> jobsInSystem, int k) {
    cout << "Total Jobs: " << jobIncrement << endl;
    int i = 0;
    thread t1(&user::userInput, &user);
    t1.detach();
    while (i < k) {
        cout << endl << endl << "****** Cycle:  " << i << " ******" << endl << endl;
        if (!readyQueue.empty()) {
            thread cpu1(&process::cpuThread, this, readyQueue.front());
            cpu1.join();
            thread cpu2(&process::cpuThread, this, readyQueue.front());
            cpu2.join();
            thread cpu3(&process::cpuThread, this, readyQueue.front());
            cpu3.join();
            thread cpu4(&process::cpuThread, this, readyQueue.front());    
            cpu4.join();
            //cpu1.join();
            //cpu2.join();
            //cpu3.join();
            //cpu4.join();
        }
        if (user.detectInput() == "stop") {
            cout << "Ready Queue size: " << readyQueue.size() << endl;
            break;
        }
        else if (!user.detectInput().empty()) {
            thread t1(&user::userInput, &user);
            t1.detach();
        }
        if (readyQueue.size() == 0) {
            cout << "Done servicing all processes" << endl;
            break;
        }
        cout << endl << endl << "Length of ready q: " << readyQueue.size() << endl << endl; 
        i++;
        sleep(1);
    }
    cout << "breaking out of roundRobin()" << endl;
}

void process::longTerm() {
    //move new queue items to ready queue
    cout << "************** " << newQueue.front() << " **************" << endl;
    readyQueue.push(newQueue.front());
    newQueue.pop();
}

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
    hw.resetMemory();
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

            queue <int> procQueue;
            procQueue = process.readyQueue;
            int size = procQueue.size();
            cout << size << endl;
            for (int i = 0; i < size; i++) {
                cout << procQueue.front() << endl;
                procQueue.pop();
            }



        } else if (commandInput == "mem") {
            hw.percentMemory = (hw.memoryAvailable / hw.memory) * 100;
            cout << endl << "Current memory usage: " << hw.memoryUsed << " MB"<< " (" << hw.percentMemory << "%)" << endl;
        } else if (commandInput == "load" ) {
            //cin.clear();
            //cin.ignore(10000,'\n');
            for(int i = 0; i < 4; i++) {
                process.openJob(process.jobs[i]);
            }
            //process.roundRobin(process.jobsInSystem, 100);        
        } else if (commandInput == "exe") {
            /*for(int i = 0; i < 4; i++) {
                process.openJob(process.jobs[i]);
            }*/
            cout << endl << endl;
            int cycles = 0;
            cout << "How many cycles would you like to run?" << endl;
            cin >> cycles;
            cin.clear();
            cin.ignore(10000,'\n');
            process.roundRobin(process.jobsInSystem, cycles);
        } else if (commandInput == "reset") {
            cout << "detected ";
            cout << commandInput << endl;
            process.resetData();
        } else if (commandInput == "exit") {
            cout << "Exiting User Mode" << endl;
            return true;
        }
        i++;
    }
}
