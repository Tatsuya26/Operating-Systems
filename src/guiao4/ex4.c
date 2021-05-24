#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <string.h>


int main(int argc, char* argv[]) {
    int input_fd, output_fd, res;
    if(!strcmp(argv[1],"-i") && argc > 2) {
        input_fd = open(argv[2], O_RDONLY);
        res = dup2(input_fd, 0);
    } 
    else printf("No entry file!\n");

    if(!strcmp(argv[3],"-o") && argc > 4) {
        output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        res = dup2(output_fd, 1);
    }
    else {
        printf("No output file\n");
    }

	close(input_fd);
	close(output_fd);

	char buffer[100];
	while((res = read(0, &buffer, 100)) > 0) write(1, &buffer, res);
    lseek(0,0,SEEK_SET);
    execlp(argv[5],argv[5],argv[6],NULL);
	return 0;
}