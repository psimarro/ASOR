#include <iostream>
#include <sys/socket.h> 
#include <netdb.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc < 2){
        std::cout << "ERROR: introduce dirección.\n";
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = 0;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_addr = NULL;
    hints.ai_addrlen = 0;
    hints.ai_canonname = NULL;
    hints.ai_next = NULL;

    struct addrinfo *res;

    getaddrinfo(argv[1], NULL, &hints, &res);
    while(res != NULL){
        char host[NI_MAXHOST];

        getnameinfo(res->ai_addr, res->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);

        std::cout << host << " " << res->ai_family << " " << res->ai_socktype << "\n";

        res = res->ai_next;
    }

    return 0;   
}
