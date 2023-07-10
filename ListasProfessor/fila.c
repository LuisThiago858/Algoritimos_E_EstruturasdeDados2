#include "stdio.h"
#include "stdlib.h"

typedef struct fila t_fila;
struct fila{
        void**elem;// *e uma referencia/ o tipo de dado associado e generico
        int tamanho;
        int inicio;
        int fim;
        int ocupacao;
        short e_infinita;
};
t_fila*criar_fila(int tamanho){
    t_fila* f=malloc(sizeof(t_fila));

    f->e_infinita=(tamanho<=0?1:0);
    f->tamanho=(tamanho<=0?1:tamanho);
    f->inicio=0;
    f->fim=0;
    f->ocupacao=0;

    f->elem=malloc(sizeof(void*)*f->tamanho);

    return f;
}

void enfileirar(t_fila*f, void*elem){
    if(f->e_infinita && f->ocupacao==f->tamanho){// se a fila e infinita
        f->tamanho=f->tamanho*2;//crescimento exponencial, ajuda com problemas que crescem rapido no comeco e depois dimimui
        f->elem=realloc(f->elem, sizeof(void*)*f->tamanho);
    }
    if(f->ocupacao<f->tamanho){
        f->elem[f->fim]=elem;
        f->fim=(f->fim+1)%f->tamanho;
        f->ocupacao++; 
    }
        
}

void* desenfileirar(t_fila*f){
    if(f->ocupacao>0){
        void*elem=f->elem[f->inicio];
        f->inicio=(f->inicio+1)%f->tamanho;
        f->ocupacao--;
        return elem;
    }
    return NULL;//correcao
}
void*primeiro_fila(t_fila*f){
    void*primeiro=NULL;
    if(f!=NULL && f->ocupacao>0){
        primeiro=f->elem[f->inicio];
    }
    return primeiro;
}
int tamanho_fila(t_fila*f){
    if(f!=NULL){
        return f->tamanho;
    }
    return -1;
}

void ocupacao_fila(t_fila*f){
    if(f!=NULL){
        return f->ocupacao;
    }
}