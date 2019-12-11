#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv){

    if (argc < 4){
        std::cout << "Error: intoduce dirección del servidor, puerto y comando!\n";
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE; //Devolver 0.0.0.0 o ::
    hints.ai_family = AF_UNSPEC; //IPv4 o IPv6
    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo *result_c;
    struct addrinfo *result_s;
    //Conseguimos información del cliente
    getaddrinfo(NULL, argv[2], &hints, &result_c);
    //Creamos el socket del cliente y conectamos el socket
    int client_sock = socket(result_c->ai_family, result_c->ai_socktype, 0);
    connect(client_sock, (struct sockaddr* ) result_c->ai_addr, result_c->ai_addrlen);
    
    //Conseguimos la información del servidor
    getaddrinfo(argv[1], argv[2], &hints, &result_s);
    
    //Enviamos el comando
    sendto(client_sock, argv[3], 1, 0, (struct sockaddr *) result_s->ai_addr, result_s->ai_addrlen);

    //Recibimos la respuesta
    char r[100] = "";
    //memset(r, '\0', 100);
    recvfrom(client_sock, &r, 100, 0, (struct sockaddr *) &result_s->ai_addr, &result_s->ai_addrlen);

    std::cout << r << "\n";

    close(client_sock);
    return 0;
}