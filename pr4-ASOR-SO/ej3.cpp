#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

int main(){

    mkfifo("tub_nombre", 0666);

    return 0;
}