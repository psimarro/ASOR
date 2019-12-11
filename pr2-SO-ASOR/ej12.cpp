#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv){

    int salida = open("out.txt", O_WRONLY);

    dup2(salida, 1);
    std::cout << "HEY\n";

    return 0;
}