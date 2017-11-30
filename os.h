#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#ifndef OS_H
#define OS_H

using namespace std;

class hardware {
	public:
		hardware();
        void takeMemory(int);
        void returnMemory(int);
        int getMemory();
        void resetMemory();
        float getPercentMemory(int);
	    int memoryUsed;
        int memoryAvailable;
        float percentMemory;
        const int memory = 4096;
            
};

class process {
    public: 
        process();
        void openJob(string);
        void longTerm();
        void cpuThread(int);
        void resetData();
        struct process_control_block {
            int process_mem_required;
            int PID;
            string job_name;
            string process_operation1;
            string process_operation2;
            string process_operation3;
            string process_operation4;
            int operation1_time;
            int operation2_time; 
            int operation3_time;
            int operation4_time;
            int totalTime;
            int timeElapsed;
            int timeLeft;
            int ioCycles;
            string currentOperation;
        };
        void roundRobin(vector<process_control_block>, int);
        void randGen(int);
        vector <string> jobs;
        queue <int> newQueue;
        queue <int> readyQueue;
        vector<process_control_block> jobsInSystem{1000};
        queue <int> waitQueue;
    private:       
        int jobIncrement;
        int cycle;
        int quantum;
};

class user {
    public:
        user();
        string detectInput();
        void userInput();
        void startUserMode();
        string input;  
        string jobFile; 
        string commandInput;    
};
#endif