#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

    std::cout << "PID: " << getpid() << "\n";
    std::cout << "PPID: " << getppid() << "\n";
    std::cout << "GID: " << getgid() << "\n";
    std::cout << "SID: " << getsid(0) << "\n";
    std::cout << "CWD: " << get_current_dir_name() << "\n";
    
    struct rlimit rlim;
    getrlimit(RLIMIT_NOFILE, &rlim);
    std::cout << "Max NO files limit (soft, hard): "
     << rlim.rlim_cur << " " << rlim.rlim_max << "\n";

    return 0;
}