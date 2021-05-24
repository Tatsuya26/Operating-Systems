#include "guiao1.h"


int mycp(char *source, char *dest) {
    int fd_source = open(source, O_RDONLY),
        fd_dest   = open(dest, O_CREAT | O_TRUNC | O_WRONLY, 0600);
    
    ssize_t read_bytes = 0, writen_bytes = 0;
    char *buffer = malloc(sizeof(char)* 100);

    while((read_bytes = read(fd_source, buffer, 100)) > 0) writen_bytes += write(fd_dest, buffer, read_bytes);

    close(fd_source);
    close(fd_dest);
    free(buffer);
    printf("Copied bytes = %ld\n", writen_bytes);
    return writen_bytes;
}

int my_cat() {
    char *buffer = malloc(sizeof(char) * 10);
    int read_bytes;
    while((read_bytes = read(0, buffer, 10) > 0)) write(1,buffer,10);
    free(buffer);
    return 0;
}

ssize_t my_readln(int fd, char *line, size_t size) {
    ssize_t read_bytes = 0;
    while(line[0] != '\n') {
        read(0,line,1);
        write(fd,line,1);
        read_bytes++;
    }
    printf("Read %ld bytes.\n",read_bytes);
    return read_bytes;
}
/*
ssize_t my_nl(int fd, char *line, size_t size) {
    
    for(lines = 0)
}
*/

int main(int argc, char *argv[]) {
    int fd = open(argv[1],O_CREAT | O_TRUNC | O_WRONLY, 0640);
    char *buffer = malloc(sizeof(char));
    my_readln(fd,buffer,1);

 
}