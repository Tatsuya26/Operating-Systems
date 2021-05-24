#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int pai2filho() {
    int p[2];
    char b[100];
    pipe(p);
    pid_t pid = fork();
    if(pid == 0) { // filho quer ler do pai portanto fechamos o terminal de escrita
        close(p[1]);
        read(p[0],&b,1024);
        printf("Filho leu %s\n", b);
        close(p[0]);
    }
    else { // pai quer escrever para o pipe portanto fechamos o terminal de leitura
        close(p[0]);
        printf("Escreva para o pipe\n");
        char buffer[10] = "hello";
        write(p[1],&buffer,1024);
        printf("Pai escreveu\n");
        close(p[1]);
    }
    return 0;
}


int ex2() {
    int p[2], res;
    char b[120];
    pipe(p);
    pid_t pid = fork();
    if(pid == 0) { // filho quer escrever para o pai por isso fechamos o terminal de leitura
        close(p[1]);
        printf("Filho a ler\n");
        while((res = read(p[0],&b,120)) > 0) {
            printf("filho:\n");
            write(1,&b,strlen(b));
        }
        close(p[0]);
    }
    else { // pai quer escrever para o pipe portanto fechamos o terminal de leitura
        close(p[0]);
        char buffer[120];
        printf("Insira um texto\n");
        while((res = read(0,&buffer,120)) > 0) {
            write(p[1],&buffer,120);
        }
        close(p[1]);
    }
    return 0;
}


int ex3() {
    int p[2], res;
    char b[120];
    pipe(p);
    pid_t pid = fork();
    if(pid == 0) { // filho quer escrever para o pai por isso fechamos o terminal de leitura
        close(p[1]);
        printf("Filho a ler\n");
        dup2(p[0],0);
        close(p[0]);
        execlp("wc","wc",NULL);
        exit(0);
    }
    else { // pai quer escrever para o pipe portanto fechamos o terminal de leitura
        close(p[0]);
        char buffer[120];
        printf("Insira um texto\n");
        while((res = read(0,&buffer,120)) > 0) {
            write(p[1],&buffer,120);
        }
        close(p[1]);
    }
    return 0;
}

int ex4() {
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

int ex5(int number_cmd) {
    int p[number_cmd - 1][2];
    char buffer[1024];
    pipe(p[0]);
    switch (fork()) {
        case -1:
            perror("Error. Invalid file descriptor\n");
            return -1;
        case 0: 
            //codigo filho -> fechar o descritor de escrita devido ao EOF
            close(p[0][0]); // end of file da escrita
            dup2(p[0][1],1);//redirecionar a aea de trabalho do processo para o stdin
            close(p[0][0]);
            execlp("grep -v ˆ# /etc/passwd","grep","-v","ˆ#","etc /etc/passwd",NULL);
            _exit(0);
        default:
            //codigo pai -> fechar o descritor de leitura
            close(p[0][0]);
            close(p[0][1]);
    }
    pipe(p[1]);
    switch (fork()) {
        case -1:
            perror("Error. Invalid file descriptor\n");
            return -1;
        case 0: 
            //codigo filho -> fechar o descritor de escrita devido ao EOF
            close(p[1][0]); // end of file da escrita
            dup2(p[1][1],1);//redirecionar a aea de trabalho do processo para o stdin
            close(p[1][0]);
            dup2(p[1][0],0);
            execlp("cut -f7 -d:","cut","-f7", "-d:", NULL);
            _exit(0);
        default:
            //codigo pai -> fechar o descritor de leitura
            close(p[1][0]);
            close(p[1][1]);
    }
    pipe(p[2]);
    switch (fork()) {
        case -1:
            perror("Error. Invalid file descriptor\n");
            return -1;
        case 0: 
            //codigo filho -> fechar o descritor de escrita devido ao EOF
            close(p[2][0]); // end of file da escrita
            dup2(p[2][1],1);//redirecionar a aea de trabalho do processo para o stdin
            close(p[2][0]);
            execlp("uniq","uniq",NULL);
            _exit(0);
        default:
            //codigo pai -> fechar o descritor de leitura
            close(p[2][0]);
            close(p[2][1]);
    }
    execlp("wc","wc","-l",NULL);
}

int main(int argc, char* argv) {
    ex4();
    return 0;
}
