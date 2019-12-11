#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

double procesa(struct dirent*, char*);

int main(int argc, char **argv){

    struct stat in;
    stat(argv[1], &in);
    if(!S_ISDIR(in.st_mode)){
        std::cout << "El parámetro no es un directorio.\n";
    }
    else{
        DIR *dir = opendir(argv[1]);
        struct dirent *read_dir;
        double total_size = 0;
        while((read_dir = readdir(dir)) != NULL){
           total_size += (procesa(read_dir, argv[1])/1024);
        }
        std::cout << "Tamaño total de los archivos en " << argv[1]  << " :\n" << total_size << "\n";
    }
}

double procesa(struct dirent *r, char *path){
    double ret_size = 0;
    struct stat f;
    char *cur_path = new char[strlen(path)];
    strcat(cur_path, path);
    strcat(strcat(cur_path, "/"), r->d_name);
    stat(cur_path, &f);

    switch(r->d_type){
        case DT_REG: {
            std::cout << r->d_name;
            if(f.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)){
                std::cout << "*\n";
            }
            else std::cout << "\n";
            ret_size = f.st_size;
            break;
        } 
        case DT_DIR: std::cout << "/" << r->d_name << "\n"; break;
        case DT_LNK:{
            std::cout << r->d_name << " -> ";
            char *buf = new char[MAXNAMLEN];
            readlink(cur_path, buf, MAXNAMLEN);
            std::cout << buf << "\n";
            free(buf);
            //ret_size = f.st_size;
            break;
        }
    }
    free(cur_path);
    return ret_size;
}