#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

bool procesa_peticion(const char *m, char *msg);

int main(int argc, char** argv){

    std::cout << argc << " " << argv[1] << " " << argv[2] << "\n";
    if(argc < 3){
        std::cout << "Introduce dirección del host y puerto.\n";
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE; //Devolver 0.0.0.0 o ::
    hints.ai_family = AF_UNSPEC; //IPv4 o IPv6
    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo *result;
    getaddrinfo(argv[1], argv[2], &hints, &result);
    int serv_sock = socket(result->ai_family, result->ai_socktype, 0);

    bind(serv_sock, (struct sockaddr *) result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);
    
    char buf[2] = "";
    int bytes_rec;
    struct addrinfo addr_rec;
    socklen_t leng_addr_rec;

    bool end = false;
    while(!end){
        (bytes_rec = recvfrom(serv_sock, &buf, 2, 0,
        (struct  sockaddr *) &addr_rec, &leng_addr_rec));
        if(strlen(buf) >= 2) buf[2] = '\0';

        char host[NI_MAXHOST];
        getnameinfo((struct sockaddr* ) &addr_rec, leng_addr_rec, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

        std::cout << bytes_rec << " bytes de: " << host << "\n";

        char msg[256];
        
        if(procesa_peticion(buf, msg)){
            if(strcmp(msg, "") == 0){
                std::cout << "Saliendo...\n";
                close(serv_sock);
                end = true;
            }
            else{ //Comando valido: d, t
                sendto(serv_sock, msg, strlen(msg), 0, (struct sockaddr*)&addr_rec, leng_addr_rec);
            }
        } 

        strcpy(buf, "");
        strcpy(msg, "");
        
    }

    freeaddrinfo(&addr_rec);
    
    return 0;
}

bool procesa_peticion(const char *buf, char* msg){
    struct tm *tm;
    time_t t;
    bool ok = true;

    if(strcmp(buf, "q") == 0) strcpy(msg, "");
    else if(strcmp(buf, "t")== 0){
        t=time(NULL);
        tm = localtime(&t);
        strftime(msg, 100, "%T", tm);
    }
    else if(strcmp(buf, "d") == 0){
        t=time(NULL);
        tm = localtime(&t);
        strftime(msg, 100, "%D", tm);
    }
    else{
        std::cout << "Comando no soportado.\n";
        ok = false;
    }

    return ok;
}