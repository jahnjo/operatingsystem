#include "os.h"

int main(void) {

hardware hw;
process process;
user user;

thread t1(&user::userInput, &user);
t1.detach();
cout << "Type 'user' to enter user mode and use os commands" << endl;
cout << "Type 'exit' to abort program" << endl;


while (1) {
    if(user.detectInput() == "exit") {
        break;
    }
    else if(user.detectInput() == "user") {
        user.input.clear();
        cout << "--------------------" << endl;
        cout << "|Entering User Mode|" << endl;
        cout << "--------------------" << endl << endl;
        user.startUserMode();
        thread t1(&user::userInput, &user);
        t1.detach();
    }
   else if (!user.detectInput().empty()) {
        thread t1(&user::userInput, &user);
        t1.detach();
   } 
    sleep(1);
}   

return 0;
}