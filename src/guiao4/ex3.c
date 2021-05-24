#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main() {
	int input_fd = open("/etc/passwd", O_RDONLY);
    int res;
	int output_fd = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int error_fd = creat("erros.txt", 0644);

	res = dup2(input_fd, 0);
	res = dup2(output_fd, 1);
	res = dup2(error_fd, 2);
	
	close(input_fd);
	close(output_fd);
	close(error_fd);

	char buffer[100];
	while((res = read(0, &buffer, 100)) > 0) {
		write(1, &buffer, res);
	}
    lseek(0,0,SEEK_SET);
    execlp("wc","wc",NULL);
    return 0;
}