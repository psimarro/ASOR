#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>

int main(){

    mkfifo("pipe_1", 0666);

    char buf[256];
    int fd_tub_nombre = open("tub_nombre", O_RDONLY | O_NONBLOCK);
    int fd_pipe1 = open("pipe_1", O_RDONLY | O_NONBLOCK);
    fd_set rdfs;
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    while(true){
        FD_ZERO(&rdfs);
        FD_SET(fd_tub_nombre, &rdfs);
        FD_SET(fd_pipe1, &rdfs);
        
        int cambios = select(fd_pipe1 + 1, &rdfs, NULL, NULL, &timeout);

        if(cambios == -1){
            perror("select()");
        }
        else if(cambios){
            if(FD_ISSET(fd_tub_nombre, &rdfs)){
                read(fd_tub_nombre, buf, 256);
                std::cout << "tub_nombre: " << buf;
                memset(buf, '\0', 256);
                close(fd_tub_nombre);
                fd_tub_nombre = open("tub_nombre", O_RDONLY | O_NONBLOCK);
            }
            if(FD_ISSET(fd_pipe1, &rdfs)){
                read(fd_pipe1, buf, 256);
                std::cout << "pipe_1: " << buf;
                memset(buf, '\0', 256);
                close(fd_pipe1);
                fd_pipe1 = open("pipe_1", O_RDONLY | O_NONBLOCK);
            }
        }


    }
    
    return 0;
}