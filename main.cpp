#include "os.h"

int main(void) {

hardware hw;
process process;
user user;

//Creates a seperate thread to scan for user input asynchronously
thread t1(&user::userInput, &user);
t1.detach();
cout << "Type 'user' to enter user mode and use os commands" << endl;
cout << "Type 'exit' to abort program" << endl;


while (1) {
    if(user.detectInput() == "exit") {
        break;
    }
    //Scans for 'user' and sends user to user mode
    else if(user.detectInput() == "user") {
        user.input.clear();
        cout << "--------------------" << endl;
        cout << "|Entering User Mode|" << endl;
        cout << "--------------------" << endl << endl;
        cout << endl << "choose from the following commands" << endl;
        cout << "'load  - load predefined jobs into system" << endl;
        cout << "'exe'  - execute a chosen amount of cycles (let OS run on its own)" << endl;
        cout << "'proc' - show unfinshed jobs + job info" << endl;
        cout << "'rand' - choose how many jobs system should randomly generate" << endl;
        cout << "'mem'  - display how much memory is used by processes in system" << endl;
        cout << "'exit' - exit back to kernel mode" << endl;
        user.startUserMode();
        thread t1(&user::userInput, &user);
        t1.detach();
    }
   //restarts the thread  if no user input detected but not an expected input
   else if (!user.detectInput().empty()) {
        cout << "unsupported command - try again please" << endl;
        thread t1(&user::userInput, &user);
        t1.detach();
   } 
    //0.2 seconds sleep
    usleep(200000);
}   

return 0;
}