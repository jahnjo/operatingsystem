<<<<<<< HEAD

=======
>>>>>>> 3b37df60f22bb61bf3ab414af9aaf7aef865ef5b
#include "os.h"


int main(void) {
<<<<<<< HEAD
hardware hw;
process process;
user user;

int i = 0;
std::thread t1(&user::userInput, &user);
t1.detach(); 
while (1) {
cout << "main loop: " << i << endl;
i++;
sleep(1);

}
cout << "we broke" << endl;


return 0;
=======
    hardware hw;
    process process;
    user user;
    /*int mem = 2000;
    hw.takeMemory(mem);
    cout << hw.getMemory() << endl;
    hw.returnMemory(mem);
    cout << hw.getMemory() << endl;*/


    int i = 0;
    thread t1(user.userInput());
    t1.detach(); 
    while (1) {
        cout << "main loop: " << i << endl;
        i++;
        user.detectInput();
        sleep(1);

    }
    cout << "we broke" << endl;
 


    return 0;
>>>>>>> 3b37df60f22bb61bf3ab414af9aaf7aef865ef5b

}