#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv){

    struct stat s;
    stat(argv[1], &s);
    if(S_ISREG(s.st_mode)){
        char hl[50] = "\0";
        strcat(strcat(hl, argv[1]), ".hard");
        link(argv[1], hl);
        char sym_l[50] = "\0";
        strcat(strcat(sym_l, argv[1]), ".sym");
        symlink(argv[1], sym_l);
    }

    
    return 0;
}