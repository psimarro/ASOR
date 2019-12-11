#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

    pid_t pid = fork();

    switch(pid){
        case -1: {
            perror("fork");
            exit(1);
        }
        case 0:{
            setsid(); 
            chdir("/tmp");
            std::cout << "Proceso hijo\n-------\n";
            std::cout << "PID: " << getpid() << "\n";
            std::cout << "PPID: " << getppid() << "\n";
            std::cout << "GID: " << getgid() << "\n";
            std::cout << "SID: " << getsid(getpid()) << "\n";
            //pause();
            break;
        }
        default:{
             std::cout << "Proceso padre\n-------\n";
            std::cout << "PID: " << getpid() << "\n";
            std::cout << "PPID: " << getppid() << "\n";
            std::cout << "GID: " << getgid() << "\n";
            std::cout << "SID: " << getsid(getpid()) << "\n";
           pause();
            break;
        }
    }

    return 0;
}
