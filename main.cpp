#include "os.h"

int main(void) {
string job = "job1.txt";
hardware hw;
process process;
user user;

thread t1(&user::userInput, &user);
process.openJob(job);

while (1) {
    if(user.detectInput() == "exit") {
        break;
    }
    /*if(user.detectInput() == "user") {
        user()
    }
    user.detectInput();*/
    
}

cout << endl << "Loop exited" << endl;

return 0;
}