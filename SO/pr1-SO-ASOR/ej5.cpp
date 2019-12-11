#include <iostream>
#include <unistd.h>

int main(){

    std::cout << "Longitud máxima de argumentos: " << sysconf(_SC_ARG_MAX) << "\n";
    std::cout << "Número máximo de hijos: " << sysconf(_SC_CHILD_MAX) << "\n";
    std::cout << "Número máximo de ficheros: " << sysconf(_SC_OPEN_MAX) << "\n";

    return 1;
}