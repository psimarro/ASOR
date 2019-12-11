#include <iostream>
#include <sys/utsname.h>

int main(){
    struct utsname info;
    uname(&info);
    std::cout << "System name: " << info.sysname << "\n";
    std::cout << "Node name: " << info.nodename << "\n";
    std::cout << "Release: " << info.release << "\n";
    std::cout << "Version: " << info.version << "\n";
    std::cout << "Machine: " << info.machine << "\n";
    std::cout << "Domain name: "<< info.domainname << "\n";

    return 1;
}