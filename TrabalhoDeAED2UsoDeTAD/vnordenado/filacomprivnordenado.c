#include "stdio.h"
#include "stdlib.h"
#include "vnordenado.h"
#include "filacomprivnordenado.h"

struct fila_cp{
    t_nord* vnord;
    // 
};


t_fila_cp* criar_fila_cp(int tam, TCompararFilaCP comparar){
    
    t_fila_cp *fcp = malloc(sizeof(t_fila_cp));
    fcp->vnord = criar_vnordenado(tam, comparar);
    
    return fcp;

}

int enfileirarCP(t_fila_cp *f, void* elem){

    return inserir_vnordenado(f->vnord, elem);

}

void* desenfileirarCP(t_fila_cp *f, int ind){
    return remover_vnordenado(f->vnord, ind);
}

void* primeiro_FCP(t_fila_cp *f){
    
    return maior_vnordenado(f->vnord);

}

void* ultimo_FCP(t_fila_cp*f){
    return menor_vnordenado(f->vnord);
}

int ocupacao_FCP( t_fila_cp *f){
    return ocupacao_vnordenado(f->vnord);
}

int tamanho_FCP(t_fila_cp *f){
    return tamanho_vnordenado(f->vnord);
}

void estatistica_FCP(t_fila_cp*f){
    return estatistica_vnordenado(f->vnord);
}