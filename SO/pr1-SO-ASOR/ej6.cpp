#include <iostream>
#include <unistd.h>

int main(){
    const char *desktop = "/home/pedro/Escritorio";

    std::cout << "Enlaces máximos de " << desktop << ": " << pathconf(desktop, _PC_LINK_MAX) << "\n";
    std::cout << "Tamaño máximo ruta " << desktop << ": " << pathconf(desktop, _PC_PATH_MAX) << "\n";
    std::cout << "Tamaño máximo de un fichero: " << pathconf(desktop, _PC_NAME_MAX) << "\n";

    return 1;
}