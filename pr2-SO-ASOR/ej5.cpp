#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

    remove("./fichero_ej5");
    open("./fichero_ej5", O_CREAT, 00645);

    return 0;
}


