#include "stdio.h"
#include "stdlib.h"
#include "vnordenado.h"

typedef struct vetor_nao_ordenado t_nord;
struct vetor_nao_ordenado{
   void* *elem;
   int ocupacao;
   int tamanho;
   int e_infinito;

   int nro_cmp_ins; // contador para comparações na inserção
   int nro_cmp_pri; // contador para comparações retornar o primeiro
   int nro_cmp_rem; // contador para comparações na remoção
   int nro_cmp_ult;

   TCompararVNOrd comparar;
};

t_nord* criar_vnordenado(int tam, TCompararVNOrd comparar) {
    t_nord* h =malloc(sizeof(t_nord));
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

int inserir_vnordenado(t_nord* v, void* elem) {
    if (v->e_infinito == 0 && v->ocupacao == v->tamanho) {
        return 0; 
    }
    v->elem[v->ocupacao] = elem;
    v->ocupacao++;
    v->nro_cmp_ins++;
    return 1;
}

void* remover_vnordenado(t_nord* v, int ind) {
    if (ind < 0 || ind >= v->ocupacao) {
        return NULL; // índice inválido
    }
    void* removido = v->elem[ind];
    v->elem[ind] = v->elem[v->ocupacao-1];
    v->ocupacao--;
    v->nro_cmp_rem++;
    return removido;
}

void* maior_vnordenado(t_nord* v) {
    if (v->ocupacao == 0) {
        return NULL; // vetor vazio
    }
    void* maior = v->elem[0];
    for (int i = 1; i < v->ocupacao; i++) {
        if (v->comparar(v->elem[i], maior) > 0) {
            maior = v->elem[i];
        }
        v->nro_cmp_pri++;
    }
    return maior;
}

void* menor_vnordenado(t_nord* v) {
    if (v == NULL || v->ocupacao == 0) {
        return NULL; // vetor vazio
    }
    void* menor = v->elem[0];
    for (int i = 1; i < v->ocupacao; i++) {
        if (v->comparar(v->elem[i], menor) < 0) {
            menor = v->elem[i];
        }
    }
    v->nro_cmp_ult++; // atualiza o contador de comparações
    return menor;
}
int ocupacao_vnordenado(t_nord*v){
    return v->ocupacao;
}
int tamanho_vnordenado(t_nord*v){
    return v->tamanho;
}

void estatistica_vnordenado(t_nord* v){
    printf("Numero de comparacoes de insercao: %d\n", v->nro_cmp_ins);
    printf("Numero de comparacoes de remocao: %d\n", v->nro_cmp_rem);
    printf("Numero de comparacoes de primeiro: %d\n", v->nro_cmp_pri);
    printf("Numero de comparacoes de ultimo: %d\n", v->nro_cmp_ult);
}

/*
t_nord estatistica_vnordenado(t_nord* h){
    t_nord estatistica;
    estatistica.nro_cmp_ins=h->nro_cmp_ins;
    estatistica.nro_cmp_rem=h->nro_cmp_rem;
    estatistica.nro_cmp_pri=h->nro_cmp_rem;
    return estatistica;
}
*/

