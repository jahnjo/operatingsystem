#include "os.h"

int main(void) {

hardware hw;
process process;
user user;

std::thread t1(&user::userInput, &user);
t1.detach(); 

while (1) {
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