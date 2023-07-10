#include "stdio.h"
#include "stdlib.h"
#include "vordenado.h"

typedef struct v_ordenado t_ord;
struct v_ordenado{
   void* *elem;
   int ocupacao;
   int tamanho;
   int e_infinito;

   int nro_cmp_ins; // contador para comparações na inserção
   int nro_cmp_pri; // contador para comparações retornar o primeiro
   int nro_cmp_rem; // contador para comparações na remoção
   int nro_cmp_ult;

   TCompararVOrd comparar;
};

t_ord* criar_vnordenado(int tam, TCompararVOrd comparar) {
    t_ord* h =malloc(sizeof(t_ord));
    h->tamanho = (tam>0?tam:2);
    h->e_infinito = (tam<=0?1:0);
    h->ocupacao = 0;
    h->elem = malloc(sizeof(void*) * h->tamanho);
    h->comparar = comparar;

    h->nro_cmp_ins=0; 
    h->nro_cmp_pri=0; 
    h->nro_cmp_rem=0;
    h->nro_cmp_ult=0;
    return h;
}

void inserir_vordenado(t_ord* v, void* elemento) {
    int i;
    // Verificar se o v está cheio
    if (v->ocupacao == v->tamanho) {
        v->tamanho *= 2; // Dobrar o tamanho do v
        v->elem = realloc(v->elem, sizeof(void*) * v->tamanho);
    }
    // Encontrar a posição correta para inserir o elemento
    for (i = v->ocupacao-1; i >= 0 && v->comparar(v->elem[i], elemento) > 0; i--) {
        v->elem[i+1] = v->elem[i];
        v->nro_cmp_ins++;
    }
    v->elem[i+1] = elemento;
    v->ocupacao++;
}

void remover_vordenado(t_ord* v, void* elemento) {
    int i, j;
    // Encontrar a posição do elemento a ser removido
    for (i = 0; i < v->ocupacao && v->comparar(v->elem[i], elemento) != 0; i++) {
        v->nro_cmp_rem++;
    }
    if (i == v->ocupacao) {
        // Elemento não encontrado
        return;
    }
    // Deslocar os elementos à direita do elemento removido uma posição para a esquerda
    for (j = i+1; j < v->ocupacao; j++) {
        v->elem[j-1] = v->elem[j];
    }
    v->ocupacao--;
    // Verificar se é necessário reduzir o tamanho do v
    if (v->e_infinito == 0 && v->ocupacao <= v->tamanho/4) {
        v->tamanho /= 2; // Reduzir o tamanho do v pela metade
        v->elem = realloc(v->elem, sizeof(void*) * v->tamanho);
    }
}

void* maior_vordenado(t_ord* v) {
    if (v->ocupacao == 0) {
        // Vetor vazio
        return NULL;
    }
    v->nro_cmp_pri++;
    return v->elem[v->ocupacao-1];
}

void* menor_vordenado(t_ord* v) {
    if (v->ocupacao == 0) {
        // Vetor vazio
        return NULL;
    }
    v->nro_cmp_ult++;
    return v->elem[0];
}

int ocupacao_vnordenado(t_ord*v){
    return v->ocupacao;
}
int tamanho_vnordenado(t_ord*v){
    return v->tamanho;
}

void estatistica_vordenado(t_ord* v){
    printf("Numero de comparacoes de insercao: %d\n", v->nro_cmp_ins);
    printf("Numero de comparacoes de remocao: %d\n", v->nro_cmp_rem);
    printf("Numero de comparacoes de primeiro: %d\n", v->nro_cmp_pri);
    printf("Numero de comparacoes de ultimo: %d\n", v->nro_cmp_ult);
}






