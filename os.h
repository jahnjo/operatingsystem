#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <queue>
#include <cstdlib>
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
        vector <string> jobs;
        queue <string> newQueue;
        queue <string> readyQueue;

    private:       
        int i;
};

class user {
    public:
        user();
        string detectInput();
        void userInput();
        bool startUserMode();
        string input;  
        string jobFile; 
        string commandInput;    
};
#endif