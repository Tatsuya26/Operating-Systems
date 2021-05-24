#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void invoqueLs() {
    execlp("/bin/ls","/bin/ls","-l",NULL);
}

void ex2() {
    pid_t pid = fork();
    int terminated, status;
    if(pid == 0) {
        execlp("/bin/ls","/bin/ls","-l",NULL);
        exit(-1);
    } else {
        terminated = wait(&status);
        if(WIFEXITED(status)) printf("Tudo correu bem\n");
        else printf("error\n");
    }
}

void ex3(int argc, char ** argv) {
    for(int i = 0; i < argc; i++) {
        write(1,argv[i],strlen(argv[i]));
        write(1,"\n",1);
    }
}

int ex4(int argc, char **argv) {
    argv[0] = "./no.out";
    ex3(argc,argv);
}

void ex5(int argc, char* argv[]) {
    pid_t pid = fork();
    int terminated, status;
    for(int i = 0; i < argc; i++) {
        if(pid == 0) {
            execl("program","program","ola","mundo",NULL);
            exit(-1);
        }
    }
    for(int i = 0; i < argc; i++) {
        terminated = wait(&status);
        if(WIFEXITED(status)) printf("Tudo correu bem\n");
        else printf("error\n");
    }
}

void mySystem(char* cmd) {
    pid_t pid = fork();
    int terminated, status;
    if(pid == 0) {
        execlp(cmd,cmd,NULL);
        exit(-1);
    }
   else {
        terminated = wait(&status);
        if(!WIFEXITED(status)) printf("error\n");
    }
}

int main(int argc, char **argv) {
    mySystem("cat");
    return 0;
}