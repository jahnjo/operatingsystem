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
    string jobs[4] = {"i/o","calculate", "yield", "out"};
}

void process::openJob(string job) {
    fstream fs;
    string contents;
    fs.open(job);
    if(fs.fail()) {
        cerr << "not opened" << endl;
    }
    else {
        cout << "should be open" << endl;
    }

    
    for (int i = 0;i < 3; i++) {
        fs >> contents;
        cout << contents << " " << endl;
        
   }
}

void process::loadProcess(string input) {
    user.jobFile = user.input.erase(0, 5);
    cout << "Loading " << user.jobFile << endl;
    user.jobFile.clear(); 
}

/******************** User Class ********************/

user::user() {}

void user::userInput() {
    while (1) {
        getline(cin,input);
        //cout << "***" << input << "***" << endl;

    }
}

string user::detectInput() {
    if (input == "proc") {
        cout << input << endl;
    } else if (input == "mem") {
        hw.memoryUsed = hw.getMemory() - hw.memory;
        hw.percentMemory = (hw.memoryUsed / hw.memory) * 100;
        cout << endl << "Current memory usage: " << hw.memoryUsed << " MB"<< " (" << hw.percentMemory << "%)" << endl;
    } else if (input.size() >= 4 ) {
        if(input.compare(0,4,"load") ==  0) {
            process.loadProcess(input);
        }
    } else if (input == "exe") {
        cout << input << endl;
    } else if (input == "reset") {
        cout << input << endl;
    }
    return input;
}

void startUserThread(){
    
}
void enterUserGUI(){

}

void user::startUserThread() {
    thread UserThread(enterUserGUI());
}




