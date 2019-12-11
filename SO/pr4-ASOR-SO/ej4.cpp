#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
    
    int tub = open("tub_nombre", O_WRONLY);

    char *msg = strcat(argv[0], "\n");
    write(tub, msg, MAX_HANDLE_SZ);
    close(tub);

    return 0;
}