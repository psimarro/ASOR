#include <iostream>
#include <sys/time.h>

int main(){
    struct timeval ini;
    struct timeval fin;

   
    int x = 0;
    gettimeofday(&ini, NULL);
    for(int i = 0; i < 1000000; i++) x++;
    gettimeofday(&fin, NULL);

    std::cout << fin.tv_usec-ini.tv_usec << "\n";

    return 1;
}