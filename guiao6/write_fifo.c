#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define max 1000
int write_from_fifo() {
    char* buffer;
    int fd = open("fifo",O_RDONLY,0666);
    while(read(fd,buffer,max) > 0) {
        write(1,buffer,strlen(buffer));
    }
    return 0;
}

int main() {
    write_from_fifo();
    return 0;
}
