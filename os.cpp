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
        memoryAvailable = memory - requestedMemory;
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
    i = 0;
}

void process::openJob(string job) {
    i++;
    fstream fs;
    string contents;
    fs.open(job);
    if(fs.fail()) {
        cerr << "ERROR: File could not be opened." << endl;
    }
    else {
        cout << "FILE OPENED" << endl;
    }
    struct process_control_block {
        string process_mem_required;
        string job_name;
        string process_operation1;
        string process_operation2;
        string process_operation3;
        string process_operation4;
        int operation1_time;
        int operation2_time; 
        int operation3_time;
        int operation4_time;

    };
       vector<process_control_block> jobsInSystem(5);
    
        for (int j = 0; j < 7; j++){
            fs >> contents;
            if (j == 0){
                jobsInSystem[i].process_mem_required = contents;
            }
            else if (j == 1){
                jobsInSystem[i].job_name = contents;
            }
            else if (j == 2){
                jobsInSystem[i].process_operation1 = contents;
                    if (jobsInSystem[i].process_operation1 == "i/o"){
                        jobsInSystem[i].operation1_time = rand() % 50 + 25;
                    }
                    else (jobsInSystem[i].operation1_time = rand() % 100 + 1);
            }
            else if (j == 3){
                jobsInSystem[i].process_operation2 = contents;
                if (jobsInSystem[i].process_operation2 == "i/o"){
                        jobsInSystem[i].operation2_time = rand() % 50 + 25;
                    }
                    else (jobsInSystem[i].operation2_time = rand() % 100 + 1);
            }
            else if (j == 4){
                jobsInSystem[i].process_operation3 = contents;
                if (jobsInSystem[i].process_operation3 == "i/o"){
                        jobsInSystem[i].operation3_time = rand() % 50 + 25;
                    }
                    else (jobsInSystem[i].operation3_time = rand() % 100 + 1);
            }
            else if (j == 5){
                jobsInSystem[i].process_operation4 = contents;
                if (jobsInSystem[i].process_operation4 == "i/o"){
                        jobsInSystem[i].operation4_time = rand() % 50 + 25;
                    }
                    else (jobsInSystem[i].operation4_time = rand() % 100 + 1);
            }
            else if (j == 6){
                if (contents == "EXE"){
                    cout << endl <<"STARTING JOB EXECUTION" << endl;
                    newQueue.push(jobsInSystem[i].job_name);
                }
            }           
        }
   cout << "PROCESS MEM REQUIREMENT: " << jobsInSystem[i].process_mem_required << "mb" << endl;
   cout << "JOB NAME: " << jobsInSystem[i].job_name << " " << endl; 
   cout << "NOW EXECUTING: " << jobsInSystem[i].process_operation1 << " " << endl;
   cout << "NOW EXECUTING: " << jobsInSystem[i].process_operation2 << " " << endl;
   cout << "NOW EXECUTING: " << jobsInSystem[i].process_operation3 << " " << endl;
   cout << "NOW EXECUTING: " << jobsInSystem[i].process_operation4 << " " << endl;
  
   
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
            //size of queue it says 2 but should be 4
            cout << process.newQueue.size() << endl;
            //printing the queue
            for(i = 0; i < 4; i++) {
                cout << process.newQueue.front() << endl;
                process.newQueue.pop();
            }           
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




