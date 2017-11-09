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
    jobs[4] = ("job1.txt","job2.txt", "job3.txt", "job4.txt");
    i = 0;
}

void process::openJob(string job) {
    i++;
    fstream fs;
    string contents;
    fs.open(job);
    if(fs.fail()) {
        cerr << "not opened" << endl;
    }
    else {
        cout << "should be open" << endl;
    }
    struct process_control_block {
        string process_mem_required;
        string job_name;
        string process_operation1;
        string process_operation2;
        string process_operation3;
        string process_operation4;
    };
       vector<process_control_block> jobsInSystem(4);
    
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
            }
            else if (j == 3){
                jobsInSystem[i].process_operation2 = contents;
            }
            else if (j == 4){
                jobsInSystem[i].process_operation3 = contents;
            }
            else if (j == 5){
                jobsInSystem[i].process_operation4 = contents;
            }
            else if (j == 6){
                if (contents == "EXE"){
                    cout << endl <<"STARTING JOB EXECUTION" << endl;
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


void process::loadProcess(string input) {
    user.jobFile = user.input.erase(0, 5);
    cout << "Loading " << user.jobFile << endl;
    user.jobFile.clear(); 
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
        } else if (commandInput.size() >= 4 ) {
            if(commandInput.compare(0,4,"load") ==  0) {
                process.loadProcess(commandInput);
            }
        } else if (commandInput == "exe") {
            cout << commandInput << endl;
        } else if (commandInput == "rst") {
            cout << "detected ";
            cout << commandInput << endl;
        } else if (commandInput == "ex") {
            cout << "Exiting User Mode" << endl;
            return true;
        }
        i++;
        //cout << endl << "command is: " << commandInput << endl;
        //cout << endl << "User Loop " << i << endl;
    }
}




