#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define KEY 123


int main(int argc, char* argv[]){
    int senha;
    pid_t pid;
    int id_fila ;  /* ID da fila de mensagens */
    int pfd[2];

    if (pipe(pfd)<0) { // abre o pipe com 2 saidas
        perror("pipe()");
        exit(EXIT_FAILURE);
    }

    int desc = dup2(senha, 0);
    if(desc == -1){
        perror("dup2 falhou!");
        exit(EXIT_FAILURE);
    }
    if((pid=fork())<0){
        perror("Erro no fork");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){ //processo filho
        if(execlp("zenity", "zenity","--entry", NULL)<0){ //verificar
            perror("exec falhou");
            exit(-1);
        }
    }

    id_fila =  mq_open("nova_fila", O_RDWR | O_CREAT, 0666, NULL);
    if(id_fila == -1){
          perror("Erro ao abrir fila") ;
          exit(1) ;
     }

    return 0;
}

