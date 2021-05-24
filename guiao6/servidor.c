#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char *filename = "log", buffer[100];
    int fd, res, flog = open(filename,O_CREAT | O_TRUNC | O_WRONLY);
    if(mkfifo("fifo",0666) == -1) perror("mkfifo");
    while(1) {
        fd = open("fifo", O_RDONLY);
        while((res = read(fd,buffer,100)) > 0) {
            write(flog,buffer,strlen(buffer));
            printf("Client is done\n");
        }
        close(fd);
    }
    unlink("fifo");
    return 0;
}