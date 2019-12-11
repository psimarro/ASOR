#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){

    struct stat s;

    stat(argv[1], &s);
    cout << "Major, minor: " << s.st_dev << "\n";
    cout << "Inodo: " << s.st_ino << "\n";
    switch (s.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }
    cout << "Ultimo acceso: " << ctime(&s.st_mtime) << "\n";
    return 0;
}
