#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <string.h>

void ex1() {
    pid_t pid;
    if((pid = fork()) == 0) {//codigo filho 
        printf("Filho tem pid %d\n",getpid());
        exit(0);
    }
    else {
        sleep(1);
        printf("Pai tem pid %d\n", getppid());
    }
    return 0;
}

void ex2() {
    pid_t pid;
    int status;
    pid = fork();
    if(pid == 0) {
        printf("Pid do filho é %d, do pai %d\n" ,getpid(),getppid());
        exit(0);
    } else {
        pid_t terminated = wait(&status);
        printf("O pid do pai é %d, do pai do pai(bash) %d\n",getpid(), getppid());
    }
}

void ex3(int numProcess) {
    pid_t pid;
    int status;
    pid = fork();
    for(int i = 0; i < numProcess; i++) {
        printf("Filho %d\n",i);
        if(pid == 0) { 
            printf("Pid do filho é %d\n" ,getpid());
            exit(i);
        } else {
            pid_t terminated = wait(&status);
            if(WIFEXITED(status)) printf("O pid do pai é %d, filho terminou com codigo %d\n",getpid(),WEXITSTATUS(status));
        }
    }
}

void ex4(int numProcess) {
    pid_t pid;
    int status;
    for(int i = 0; i < numProcess; i++) {
        pid = fork();
        printf("Filho %d\n",i);
        if(pid == 0) { 
            printf("Pid do filho é %d\n" ,getpid());
            exit(i);
        }
    }
    for(int i = 0; i < 10; i++) {
        pid_t terminated = wait(&status);
        if(WIFEXITED(status)) printf("O pid do pai é %d, filho %d terminou com codigo %d\n",getpid(),i,WEXITSTATUS(status));
    }
}

void ex5(int numProcess) {
    pid_t pid;
    int status;
    for(int i = 0; i < numProcess; i++) {
        pid = fork();
        printf("Filho %d\n",i);
        if(pid == 0) printf("Pid do filho é %d\n" ,getpid());
        else {
            pid_t terminated = wait(&status);
            if(WIFEXITED(status)) printf("O pid do pai é %d, filho %d terminou com codigo %d\n",getpid(),i,WEXITSTATUS(status));
            exit(i);
        }
    }
}


void exMail(FILE f) {
    int i,j, status , fd = open(&f,O_RDONLY), FileNotEnded = 0;
    ssize_t mailFlag = 0;
    char* mail[1024], num_aluno[50],nota[5];
    pid_t pid;
    while(!FileNotEnded) {
        for(i = 0; i < 10; j++) {
            if((pid = fork()) == 0) {
                mailFlag = read(fd,mail,10);
                for(int k = 0; k < 6; k++) num_aluno[k] = mail[k];
                mail[6] = '\n';
                nota[0] = mail[7];
                nota[1] = mail[8];
                strcpy(mail,num_aluno);
                strcat(num_aluno,"@alunos.uminho.pt");
                if(mailFlag == 10) execlp("mail","mail","-s", "Sistemas_Operativos",mail,num_aluno,nota);
                else FileNotEnded = 1;
                exit(0);
            }
        }
        for(int j = 0; j < 10; j++) {
            int terminated = wait(&status);
            if(WIFEXITED(status)) printf("Email enviado com sucesso\n");
            else printf("Erro enviar email");
        }
        i+=10;
    }
}

void counter(char* pattern) {
    pid_t pid;
    int i = 0,res;
    char** matrix_to_search = malloc(sizeof(char*)* 50);
    matrix_to_search[0] = malloc(sizeof(char) * 128);
    while((res = read(0,matrix_to_search[i],128)) > 0) {
        matrix_to_search[i + 1] = malloc(sizeof(char) * 128);
        i++;
    }
    for(int j  =0; j < i; j++) printf("%s\n",matrix_to_search[i]);
}


