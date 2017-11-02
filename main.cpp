#include "os.h"

int main(void) {

hardware hw;
process process;
user user;

std::thread t1(&user::userInput, &user);

while (1) {
    if(user.detectInput() == "exit") {
        break;
    }
    user.detectInput();
    
}

cout << endl << "Loop exited" << endl;

return 0;
}