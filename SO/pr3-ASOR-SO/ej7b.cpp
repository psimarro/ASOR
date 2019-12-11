#include <iostream>
#include <unistd.h>

int main(int argc, char **argv){

    execvp(argv[1], &argv[1]);
        std::cout << "El comando terminó de ejecutarse\n";

    return 0;

}