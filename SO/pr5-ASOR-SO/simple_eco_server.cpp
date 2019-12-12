#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

int serv_sock;
int cli_sock;

int main(int argc, char **argv){

    if(argc < 3){
        std::cout << "Introduce dirección del host y puerto.\n";
        return -1;
    }

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE; //Devolver 0.0.0.0 o ::
    hints.ai_family = AF_UNSPEC; //IPv4 o IPv6
    hints.ai_socktype = SOCK_STREAM; //IMPORTANTE PARA TCP

    struct addrinfo *result;
    getaddrinfo(argv[1], argv[2], &hints, &result);
    serv_sock = socket(result->ai_family, result->ai_socktype, 0);

    bind(serv_sock, (struct sockaddr *) result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);

    listen(serv_sock, 16);

    struct sockaddr_storage cli;
    socklen_t len_cli = sizeof(cli);        

    while(true){
        cli_sock = accept(serv_sock, (struct sockaddr *) &cli, &len_cli);

        char host[NI_MAXHOST], port[NI_MAXSERV];
        getnameinfo((struct sockaddr *) &cli, len_cli, host, NI_MAXHOST, port, NI_MAXSERV,
        NI_NUMERICHOST | NI_NUMERICSERV);

        std::cout << "Conexión desde: " << host << " " << port << "\n";

        int bytes_rec = 0;
        char buf[256];
        while(bytes_rec = recv(cli_sock, buf, 256, 0)){
            buf[bytes_rec+1] = '\0';
            send(cli_sock, buf, bytes_rec, 0);
        }

        std::cout << "Conexión terminada.\n";
        close(cli_sock);
    }
    
    close(serv_sock);
    

    return 0;
}