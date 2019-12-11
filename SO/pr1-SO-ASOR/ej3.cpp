#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <string.h>

const int MAX_ERR = 255;

int main(){
    char *s;

    for(int i = 0; i < MAX_ERR; ++i){
        std::cout << "ERROR(" << i << "): " << strerror(i) << "\n";
    }

    return 1;
}