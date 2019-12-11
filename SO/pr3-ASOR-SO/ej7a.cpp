#include <iostream>
#include <stdlib.h>

int main(int argc, char **argv){

    if(system(argv[1]) == EXIT_SUCCESS)
        std::cout << "El comando terminó de ejecutarse\n";

    return 0;
}