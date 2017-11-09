#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <vector>
#ifndef OS_H
#define OS_H

using namespace std;

class hardware {
	public:
		hardware();
        void takeMemory(int);
        void returnMemory(int);
        int getMemory();
	    int memoryUsed;
        int memoryAvailable;
        int percentMemory;
        const int memory = 4096;
                
  
	private:
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
        void loadProcess(string);

    private:
        string jobType[20];
        int jobMemory[20], jobTime[20], i;

};

class user {
    public:
        user();
        string detectInput();
        void userInput();
        void startUserThread();
        void enterUserGUi();
        string input;  
        string jobFile;     
};




#endif