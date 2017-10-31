#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <unistd.h>
#ifndef OS_H
#define OS_H

using namespace std;

<<<<<<< HEAD
=======
string input;
>>>>>>> 3b37df60f22bb61bf3ab414af9aaf7aef865ef5b

class hardware {
	public:
		hardware();
        void takeMemory(int);
        void returnMemory(int);
        int getMemory();
  
	private:
	    int memory;
        string coreOne[10], coreTwo[10], coreThree[10], coreFour[10];
};

class process {
    public: 
        process();
        void openJob(string);
        int parseJob();
        int parseMemory();
        int parseTime();
        void exitThread();

    private:
        string jobType[20];
        int jobMemory[20], jobTime[20];
};

class user {
    public:
        user();
        string detectInput();
        void userInput();
<<<<<<< HEAD
        string input;
=======
>>>>>>> 3b37df60f22bb61bf3ab414af9aaf7aef865ef5b
        
};




#endif