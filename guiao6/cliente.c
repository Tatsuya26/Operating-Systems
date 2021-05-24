#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int fd = open("fifo",O_WRONLY,0666);
    for(int i = 1; i < argc; i++) {
        char *r = strcat(argv[i]," ");
        write(fd,r,100);
    }
    close(fd);
    return 0;
}