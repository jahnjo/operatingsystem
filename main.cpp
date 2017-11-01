#include "os.h"

int main(void) {

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
}