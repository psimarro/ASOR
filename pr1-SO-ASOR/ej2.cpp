#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(){
    char *s;
    if(setuid(0)== -1){
        std::cout<< "ERROR: " << errno << " " << strerror(errno) << "\n";
    }

    return 1;
}