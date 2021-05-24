#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <string.h>


int main(int argc, char* argv[]) {
    int p[2], res;
    char b[120];
    pipe(p);
    pid_t pid = fork();
    if(pid == 0) { // filho quer calcular o ls e depois escrever no pipe, fechar terminal de leitura
        close(p[0]);
        dup2(p[1],1);
        close(p[1]);
        execlp("ls","ls -l","/etc",NULL);
        exit(0);
    }
    else { // pai quer ler do tipo o result do ls e depois aplucar o programa wc -l ao result
        close(p[1]);
        char buffer[120];
        dup2(p[0],0);
        close(p[0]);
        execlp("wc","wc","-l",NULL);
    }
    return 0;
}
