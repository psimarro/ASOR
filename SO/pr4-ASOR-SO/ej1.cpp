#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char **argv){

    int fd[2];
    pipe(fd);
    pid_t pid;

    pid = fork();
    if(pid == 0){ 
        dup2(fd[0], 0);
        close(fd[1]);
        execlp(argv[3], argv[3], argv[4], NULL);
    }
    else{
        dup2(fd[1], 1);
        close(fd[0]);
        execlp(argv[1], argv[1], argv[2], NULL);
        wait(NULL);
    }

    


    return 0;
}