#include "os.h"

/******************** Hardware Class ********************/

hardware::hardware() {
    memory = 4096;
}

void hardware::takeMemory(int requestedMemory) {
    if(memory > requestedMemory) {
        memory -= requestedMemory;
    }
    else {
        cout << "Not enough memory" << endl;
    }
}

void hardware::returnMemory(int returnedMemory) {
    memory += returnedMemory;
}

int hardware::getMemory() {
    return memory;
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

/******************** User Class ********************/

user::user() {}

void user::userInput() {
    while (1) {
        cin >> input;
        cout << "***" << input << "***" << endl;
    }
}


string user::detectInput() {
    if (input == "proc") {
        cout << input << endl;
    } else if (input == "mem") {
        cout << input << endl;
    } else if (input == "load") {
        cout << input << endl;
    } else if (input == "exe") {
        cout << input << endl;
    } else if (input == "reset") {
        cout << input << endl;
    } else if (input == "exit") {
        cout << input << endl;
    } 
    return input;
}

