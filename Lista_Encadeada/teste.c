#include <stdio.h>
#include <stdlib.h>

typedef struct no No;
struct no{
    int data;
    No*prox;
};

No*criarNo(int val){
    No*novo=(No*)malloc(sizeof(No));
    novo->data=val;
    novo->prox=NULL;
    return novo;
}

typedef struct LSE{
    No*inicio;
    int tamanho;
}T_LSE;

T_LSE*criarLista(){
    T_LSE*novo=malloc(sizeof(T_LSE));
    novo->inicio=NULL;
}

void inserirInicio(T_LSE*lista, int val){
    No*novo=criarNo(val);
    novo->prox=lista->inicio;
    lista->inicio=novo;
    lista->tamanho++;
}
int removerInicio(T_LSE*lista){
    int carga=0;
    if(lista->inicio!=NULL){
        No*remover=lista->inicio;
        carga=remover->data;
        lista->inicio=remover->prox;
        lista->tamanho--;
        free(remover);
    }
    return carga;
}

void imprimirLista(T_LSE*lista){
    if(lista->inicio!=NULL){
        No*atual=lista->inicio;
        while(atual!=NULL){
            printf("%d-", atual->data);
            atual=atual->prox;
        }
    }
}

int acessarNaLista(T_LSE*lista, int pos){
    int i=1, carga=0;
    No*cam=lista->inicio;
    if(pos<=lista->tamanho){
        while(i<pos){
            cam=cam->prox;
            i++;
        }
        carga=cam->data;
    }
    return carga;
}

int main(){
    T_LSE*musicas=criarLista();
    for(int i=1; i<10; i++){
        inserirInicio(musicas, i);
    }
    imprimirLista(musicas);
    int musica=removerInicio(musicas);
    printf("\nremoveu - %d\n", musica);
    imprimirLista(musicas);
    musica=acessarNaLista(musicas, 5);
    printf("\nacessou - %d\n", musica);
    return 0;
}