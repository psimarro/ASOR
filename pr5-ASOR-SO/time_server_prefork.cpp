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

void from_client(char*, struct addrinfo *,  socklen_t*);
bool procesa_peticion(const char *m, char *msg);

void handler(int signal){
    // while(wait(NULL)){
    wait(NULL);
}

int main(int argc, char **argv){
    if(argc < 3){
        std::cout << "Introduce dirección del host y puerto.\n";
        return -1;
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

    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags = SA_RESTART;

    bool end = false;


    while(!end){

        char buf[2] = "";
        struct addrinfo addr_cli;
        socklen_t leng_addr_cli;

        from_client(buf, &addr_cli, &leng_addr_cli);
        if(strlen(buf) >= 2) buf[1] = '\0';

        pid_t pid = fork();
        if(pid == 0){//hijo
            char msg[256];
        
            if(procesa_peticion(buf, msg)){
                if(strcmp(msg, "") == 0){
                    std::cout << "Saliendo...\n";
                    close(serv_sock);
                    end = true;
                    //kill(getppid(), SIGKILL);
                }
                else{ //Comando valido: d, tsys/
                    strcat(msg, "\n");
                    sendto(serv_sock, msg, strlen(msg), 0, (struct sockaddr*)&addr_cli, leng_addr_cli);
                }
            }
            strcpy(msg, "");
            break;
        }
        else{
            sigaction(SIGCHLD, &act, NULL);
            strcpy(buf, "");
        }
    }

    return 0;
}

void from_client(char * buf, struct addrinfo * addr_cli, socklen_t *leng_addr_cli){

    struct sockaddr_storage a;
    socklen_t l = sizeof(a);
    int bytes_rec = recvfrom(serv_sock, buf, 2, 0, (struct  sockaddr *) &a, &l);

    char host[NI_MAXHOST];
    getnameinfo((struct sockaddr* ) &a, l, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

    std::cout << bytes_rec << " bytes de: " << host << "\n";

    memcpy(addr_cli, &a, sizeof(struct addrinfo));
    memcpy(leng_addr_cli, &l, sizeof(socklen_t));
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
