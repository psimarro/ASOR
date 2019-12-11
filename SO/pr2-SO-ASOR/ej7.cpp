#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int main(){

    umask(0027);
    remove("./fichero_ej7");
    open("./fichero_ej7", O_CREAT, 00645);
    return 0;
}


