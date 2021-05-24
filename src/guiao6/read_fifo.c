#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int read_from_stdin_to_stdout() {
    char* buffer;
    int fd = open("fifo",O_WRONLY, 0666);
    while(read(0,buffer,strlen(buffer)) > 0) write(fd,buffer,strlen(buffer));
    return 0;
}

int main() {
    read_from_stdin_to_stdout();
    return 0;
}
