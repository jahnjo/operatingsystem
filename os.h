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
            
};

class process {
    public: 
        process();
        void openJob(string);
        void longTerm();
        void cpuThread(int);
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
        };
        void roundRobin(vector<process_control_block>);
        vector <string> jobs;
        queue <int> newQueue;
        queue <int> readyQueue;
        vector<process_control_block> jobsInSystem{10};
        queue <string> waitQueue;
    private:       
        int jobIncrement;
        int cycle;
        bool done;
        int quantum;
        //int op1,op2,op3,op4;
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