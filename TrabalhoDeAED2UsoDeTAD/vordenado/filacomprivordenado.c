#include "stdio.h"
#include "stdlib.h"
#include "vordenado.h"
#include "filacomprivordenado.h"

struct fila_cp{
    t_vord* vord;
    // 
};


t_fila_cp* criar_fila_cp(int tam, TCompararFilaCP comparar){
    
    t_fila_cp *fcp = malloc(sizeof(t_fila_cp));
    fcp->vnord = criar_vordenado(tam, comparar);
    
    return fcp;

}

void enfileirarCP(t_fila_cp *f, void* elem){

    return inserir_vordenado(f->vord, elem);

}

void desenfileirarCP(t_fila_cp *f, void* elem){
    return remover_vordenado(f->vord, elem);
}

void* primeiro_FCP(t_fila_cp *f){
    
    return maior_vordenado(f->vord);

}

void* ultimo_FCP(t_fila_cp*f){
    return menor_vordenado(f->vord);
}

int ocupacao_FCP( t_fila_cp *f){
    return ocupacao_vordenado(f->vord);
}

int tamanho_FCP(t_fila_cp *f){
    return tamanho_vordenado(f->vord);
}

void estatistica_FCP(t_fila_cp*f){
    return estatistica_vordenado(f->vord);
}