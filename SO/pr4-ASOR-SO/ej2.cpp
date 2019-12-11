#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    int p_h[2], h_p[2];
    pipe(p_h);
    pipe(h_p);

    pid_t pid = fork();
    if(pid == 0){ //hijo
        int numMensajes = 0;    
        char cad[100];

        close(p_h[1]);
        close(h_p[0]);
        write(h_p[1], "l", 1);
        while(numMensajes < 10){
            if(read(p_h[0], cad, 100) != -1){
                numMensajes++;
                std::cout <<  "Hijo escribe: " << cad << " | Num mensajes = " << numMensajes << "\n";
                if(numMensajes == 10) write(h_p[1], "q", 1);
                else write(h_p[1], "l", 1); 
            }
        }
    }
    else{ //padre
        close(p_h[0]);
        close(h_p[1]);
        char cad[100];

        while(read(h_p[0], cad, 1) && cad != "q"){
            std::cout << "Padre lee: ";
            std::cin >> cad;
            write(p_h[1], cad, 100);
        }
    }

    

    return 0;
}