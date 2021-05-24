#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

/*
* Terminar ex3 com alarmes
*/
void handler_alarm(unsigned int sig,pid_t pid) {
    if(sig == 10) kill(pid,SIGKILL);
}

int main(int argc, char* argv[]) {
    pid_t pid, pidFound = -1;
    int status, found = 0;
    pid_t pids[argc - 2];
    char* pal = "ola";
    for(int i = 0 ;i < argc - 2; i++){
        pids[i] = fork(); 
        if(pids[i] == 0) {
            unsigned int res = alarm(10);
            execlp("grep","grep",pal,argv[i],NULL);
            handler_alarm(res,pids[i]);
            _exit(0); // irelevante
        }
        if(pids[i] == -1) printf("Erro\n");
    }
    
    for(int i = 0;i < argc - 2 && !found; i++) {
        pid_t terminated = wait(&status); // status tem o resultado devolvido pelo filho
        //if(signal(SIG_Al))
        if(WEXITSTATUS(status) == 0) {
            printf("Encontrou a palvra: %s\n",pal);
            pidFound = i;
        }
        else if(status >= 1) printf("Nao encontrou %s no ficheiro %d\n",pal,i);
        
        else if(pidFound != -1) 
            for(int i = 0; i < argc;i++) {
                if(pids[i] != pidFound && pids[i] != -1) kill(pids[i],SIGKILL);
                found = 1;
            }
        else printf("Erro na execução de grep\n");

    }


}