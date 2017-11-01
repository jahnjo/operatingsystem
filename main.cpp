#include "os.h"

int main(void) {

hardware hw;
process process;
user user;

int i = 0;
std::thread t1(&user::userInput, &user);
t1.detach(); 

while (1) {
    //cout << "main loop: " << i << endl;
    i++;
    if(user.detectInput() == "exit") {
        sleep(1);
        break;
    }
    if(user.detectInput() == "mem") {
        cout << endl << "Memory used: " << hw.getMemory() << endl;
        sleep(1);
    }
}

cout << endl << "Loop exited" << endl;

return 0;
}