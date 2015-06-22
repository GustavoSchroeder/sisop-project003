#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <pthread.h>
#include <mqueue.h>

#define NOME_FILA1  "/fila_senhas_cadastro"
#define NOME_FILA2  "/fila_senhas_consulta"

const int BUFFSIZE = 64;

void faz_cadastro(mqd_t fila_cadastros);
void faz_consulta(mqd_t fila_consulta);

struct cadastro_senha{
	char *nome_senha;
	char *usuario;
	char *senha;
}

struct Cadastro_senha array_de_cadastros[60];


int main(){

    int senha = 0000;
    pid_t pid;
    int pfd[2];
    mqd_t mq_cadastro;/* ID da fila de mensagens */
    mqd_t mq_consulta;
    char* opcao;
    int conta == 0;


    if (pipe(pfd)<0) { // abre o pipe com 2 saidas
        perror("pipe()");
        exit(EXIT_FAILURE);
    }

    int desc = dup2(senha, 0); //muda a saida padra
    if(desc == -1){
        perror("dup2 falhou!");
        exit(EXIT_FAILURE);
    }
    if((pid=fork())<0){ //cria um novo processo
        perror("Erro no fork");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){ //processo filho
        if(execlp("zenity", "zenity","--entry", NULL)<0){ //inicia o zenity no processo filho
            perror("exec falhou");
            exit(-1);
        }
    }


     mq_cadastro = mq_open(NOME_FILA1, O_RDWR | O_CREAT, 00070, NULL);
	 mq_consulta = mq_open(NOME_FILA2, O_RDWR | O_CREAT, 00070, NULL);

	/*if(desc_cadastro == -1 || desc_consulta == -1){
        perror("Erro ao abrir fila");
        exit(EXIT_FAILURE);
	}*/

     while(0){ //loop infinito para gerar um "menu"
        printf("1 - Cadastro de Senha /n 2 - Consulta de senha");
        scanf("%i", &opcao);
        if(opcao == 1){
            if(mq_send(mq_cadastro, opcao*, 64, 20) == -1){
                perror("Erro ao enviar mensagem");
                exit(EXIT_FAILURE);
            }
        }
        if(opcao == 2){
            if(mq_send(mq_consulta, opcao*, 64, 20) == -1){
                perror("Erro ao enviar mensagem");
                exit(EXIT_FAILURE);
        }

	pthread_t thread[2];
	int th_cadastro = pthread_create(&thread[0], NULL, &faz_cadastro, mq_cadastro);// monitora fila 1
	int th_consulta = pthread_create(&thread[1], NULL, &faz_consulta, mq_consulta);// monitora fila 2
	if(th_consulta == -1 || th_cadastro == -1){
        perror("Erro ao criar thread de monitoramento!")
        exit(EXIT_FAILURE);
	}
	pthread_exit(NULL);
}

void faz_cadastro(mqd_t fila_cadastros){
    int cont = 0;
    char buffer[BUFFSIZE];
	char nome_senha[20];
	char usuario[20];
	char senha[20];
	int pointer = 0;

	while(true){
        while(pointer == 0){
            retorno = mq_receive(fila_cadastros, &buffer, BUFFSIZE, NULL); // retorno
        }
        if(pointer != -1)){
            printf("Nome da Senha");
            scanf("%s", nome_senha);
            printf("Usuário");
            scanf("%s", usuario);
            printf("Senha");
            scanf("%i", senha);
            struct cadastro_senha {nome_senha, usuario, senha};
            array_de_cadastros[conta] = cadastro_senha; // guarda cadastro no array
            conta++;
            pointer = 0;
        }
	}
}

void faz_consulta(mqd_t fila_consultas, senha){
            int pointer = 1;
            int ordem = 0;
            int cont = 0;
            char buffer[BUFFSIZE];
            char nome_senha[20];
            char login_usuario[20];
            char identificacao[20];
            char* nova_fila;

            int compara_senha = 0;
            int desc2 = dup2(compara_senha, 0); //muda a saida padra
            if(desc2 == -1){
                perror("dup2 falhou!");
                exit(EXIT_FAILURE);
            }
            if((pid=fork())<0){ //cria um novo processo
                perror("Erro no fork");
                exit(EXIT_FAILURE);
            }
            else if(pid==0){ //processo filho
                if(execlp("zenity", "zenity","--entry", NULL)<0){ //inicia o zenity no processo filho
                    perror("exec falhou");
                    exit(-1);
            }

            if(compara_senha == senha){
                printf("Fila para ser enviada a senha correspondente");
                scanf("%s", nova_fila);
                while(true){
                    while(retorno>0){
                        retorno = mq_receive(filacon, &buffer, BUFFSIZE, NULL);
                    }
                    for(int i = 0; i>60; i++){
                         if(strcmp((array_de_cadastros[i].nome_senha), nome_senha) == 0){ // compara nomes de senhas
                                mq_send(nova_fila, array_de_cadastros[i], BUFFSIZE, NULL); // envia mensagem
                                break;
                         }
                    }
                }
            }
            else{
                perror("Senha incorreta");
                exit(EXIT_FAILURE);
            }
      }
    return 0;
}

