#include <iostream>
#include <time.h>

int main(){
    time_t t = time(NULL);
    struct tm t2 = *(localtime(&t));


    std::cout << t2.tm_year + 1900<< "\n";

    return 1;
}