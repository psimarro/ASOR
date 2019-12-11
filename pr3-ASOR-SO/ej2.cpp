#include <iostream>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>



int main(){

    int scheduler = sched_getscheduler(0);
    std::cout << "Current scheduler: ";
    switch(scheduler){
        case SCHED_OTHER: std::cout << "SCHED_OTHER\n"; break;
        case SCHED_BATCH: std::cout << "SCHED_BATCH\n"; break;
        case SCHED_IDLE: std::cout << "SCHED_IDLE\n"; break;
        case SCHED_FIFO: std::cout << "SCHED_FIFO\n"; break;
        case SCHED_RR: std::cout<< "SCHED_RR\n"; break;
    }

    std::cout << "Max prio: " << sched_get_priority_max(scheduler) << "\n";
    std::cout << "Min prio: " << sched_get_priority_min(scheduler) << "\n";

    pid_t id = getpid();
    std::cout << "Current prio: " << getpriority(PRIO_PROCESS, id) << "\n";

    return 0;
}