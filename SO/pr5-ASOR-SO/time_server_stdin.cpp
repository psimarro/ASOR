#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <time.h>

int serv_sock;

bool procesa_peticion(const char *, char*);
void from_client(char*, struct addrinfo *,  socklen_t*);
void from_stdin(char*);

int main(int argc, char **argv){

    //std::cout << argc << " " << argv[1] << " " << argv[2] << "\n";
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
    serv_sock = socket(result->ai_family, result->ai_socktype, 0);

    bind(serv_sock, (struct sockaddr *) result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);

    bool end = false;

    while(!end){
        //Establecemos el conjunto de descriptores
        fd_set rdfs;
        FD_ZERO(&rdfs);
        FD_SET(0, &rdfs);
        FD_SET(serv_sock, &rdfs);

        int cambios = select(serv_sock + 1, &rdfs, NULL, NULL, NULL);

        char buf[2] = "";
        struct addrinfo addr_cli;
        socklen_t leng_addr_cli;

        if(cambios == -1){
            perror("select()");
        }
        else if(FD_ISSET(0, &rdfs)){
           from_stdin(buf);
        }
        else if(FD_ISSET(serv_sock, &rdfs)){
            from_client(buf, &addr_cli, &leng_addr_cli);
        }

        if(strlen(buf) >= 2) buf[1] = '\0';

        char msg[256] = "";
        if(procesa_peticion(buf, msg)){
            if(strcmp(msg, "") == 0){
                    std::cout << "Saliendo...\n";
                close(serv_sock);
                end = true;
            }
            else if(FD_ISSET(serv_sock, &rdfs)){ //Comando valido: d, t
                strcat(msg, "\n");
                sendto(serv_sock, msg, strlen(msg), 0, (struct sockaddr*)&addr_cli, leng_addr_cli);
            }
            else if(FD_ISSET(0, &rdfs)){
                strcat(msg, "\n");
                write(1, msg, strlen(msg));
            } 
        }        

        strcpy(msg, "");
        strcpy(buf, "");
        freeaddrinfo(&addr_cli);
    }
    
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

void from_client(char * buf, struct addrinfo * addr_cli, socklen_t *leng_addr_cli){

    struct addrinfo a;
    socklen_t l;
    int bytes_rec = recvfrom(serv_sock, buf, 2, 0,
    (struct  sockaddr *) &a, &l);

    char host[NI_MAXHOST];
    getnameinfo((struct sockaddr* ) &a, l, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

    std::cout << bytes_rec << " bytes de: " << host << "\n";

    memcpy(addr_cli, &a, sizeof(struct addrinfo));
    memcpy(leng_addr_cli, &l, sizeof(socklen_t));
}

void from_stdin(char *buf){
    int bytes_rec = read(0, buf, 2);
    std::cout << bytes_rec << " bytes de entrada estándar\n";
}