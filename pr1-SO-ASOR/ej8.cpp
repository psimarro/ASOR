#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main(){
    uid_t info = getuid();
    uid_t effinfo = geteuid();
    

    std::cout << info << "\n";
    std::cout << effinfo << "\n";
    return 1;
}