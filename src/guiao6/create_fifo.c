
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int create_fifo() {
    if(mkfifo("fifo",0666) == -1) perror("mkfifo");
    return 0;
}

int main() {
    create_fifo();
    return 0;
}