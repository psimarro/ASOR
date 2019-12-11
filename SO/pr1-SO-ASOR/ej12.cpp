#include <iostream>
#include <time.h>

int main(){

    time_t t = time(NULL);
    std::cout <<  t << "\n";

    return 1;
}