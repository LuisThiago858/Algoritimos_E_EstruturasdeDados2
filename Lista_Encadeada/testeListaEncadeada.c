#include <stdio.h>
#include <stdlib.h>
//cria o apelido para a estrutura que armazena os dados.
//cria a estrutura
//cria o no
//cria a lista
//armazena na lista


typedef struct no No;//define um apelido No para struct no
struct no{ // struct no que vai armazenar as informacoes
    int data; //int data que vai armazenar a informcao que eu vou querer guardar
    No*prox;// um ponteiro no para o proximo
};
No*criarNo(int val){//define a funcao criarNo recebendo como parametro um inteiro val
    No *novo=(No*)malloc(sizeof(No)); //aloca dinamicamente este espaco na memoria
    novo->data=val;//define que a data atual será o valor passado como parametro
    novo->prox=NULL;//define o ponteiro para o prox como sendo NULL
    return novo;//retorna o novo
}
typedef struct LSE{//define a estrutura LSE que será a ideia da lista
    No*inicio;//Um ponteiro no*inicio que define o comeco da lista
}T_LSE;//define o apelido para essa struct LSE

T_LSE*criaLista(){//cria a funcao para struct LSE que cria efetivamente a lista
    T_LSE*novo=malloc(sizeof(T_LSE));//aloca dinamicamete e e cria um ponteira para a lista chamado novo
    novo->inicio=NULL;//define o inicio como sendo NULL para evitar armazenar em um local onde ja tem algo
    return novo;//retorna o ponteiro para o primeiro elemento da lista
}

//inserir no inicio

void inserirInicio(T_LSE*lista, int val){
    No*novo=criarNo(val);
    novo->prox=lista->inicio;
    lista->inicio=novo;
}

void removerInicio(T_LSE*lista){
    if(lista->inicio==NULL){
        printf("lista vazia\n");
    }
    No* removido=lista->inicio;
    lista->inicio=removido->prox;
    free(removido);
}

void acessarLista(T_LSE*lista){
    if(lista->inicio==NULL){
        printf("Lista Vazia\n");
    }
    No*atual=lista->inicio;
    while(atual!=NULL){
        printf("%d-",atual->data);
        atual=atual->prox;
    }
}
