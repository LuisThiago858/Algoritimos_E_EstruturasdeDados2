#include "stdio.h"
#include "stdlib.h"
#include "ordenacao.h"
#include "math.h"


void contagem_rs_mins(void* vetor_A[], int tam, int d, TLerIdRadixSort ler_id){
    //int tam_c = maior(vetor_A, tam);

    void* vetor_B[tam];
    int vetor_C[10] = {0};

    for(int i=0;i<tam;i++){
        int k = (int)(ler_id(vetor_A[i])/pow(10,d)) % 10; 
        //printf("---- K=%d %d\n",k, vetor_A[i]);
        vetor_C[k] = vetor_C[k] + 1;
    }

    for(int i=1;i<10;i++){
        vetor_C[i] = vetor_C[i] + vetor_C[i-1];
    }
    
    for(int i=tam-1;i>=0;i--){
        int k = (int)(ler_id(vetor_A[i])/pow(10,d))%10;
        int j = vetor_C[k];
        vetor_B[j-1] = vetor_A[i];
        vetor_C[k] = vetor_C[k] - 1;
    }

    for(int i=0;i<tam;i++){
        vetor_A[i] = vetor_B[i];
        //printf("->%d\n", vetor_A[i]);
    }
}

void distribuindo(void* vetor_A[], int tam, int d, TLerIdRadixSort ler_id){
    //int tam_c = maior(vetor_A, tam);

    void* vetor_B[tam];

    //t_lse* caixas[10];

    for(int i=0;i<10;i++){
        //caixas[i] = criar_lse(NULL, NULL);
    }

    // Para ser implementado

    // usar a inserir no final

    // remover no inicio

    // reconstruir os vetor original

}

void radix_sort(void* vetor[], int tam, int digs, TLerIdRadixSort ler_id){
    for(int i=0;i<digs;i++){
        contagem_rs_mins(vetor, tam, i, ler_id);
    }
}
/*
void contagem_rs_mins(int vetor_A[], int tam, int d){
    //int tam_c = maior(vetor_A, tam);

    int vetor_B[tam];
    int vetor_C[10] = {0};

    for(int i=0;i<tam;i++){
        int k = (int)(vetor_A[i]/pow(10,d=1)) % 10; 
        //printf("---- K=%d %d\n",k, vetor_A[i]);
        vetor_C[k] = vetor_C[k] + 1;
    }

    for(int i=1;i<10;i++){
        vetor_C[i] = vetor_C[i] + vetor_C[i-1];
    }
    
    for(int i=tam-1;i>=0;i--){
        int k = (int)(vetor_A[i]/pow(10,d))%10;
        int j = vetor_C[k];
        vetor_B[j-1] = vetor_A[i];
        vetor_C[k] = vetor_C[k] - 1;
    }

    for(int i=0;i<tam;i++){
        vetor_A[i] = vetor_B[i];
        //printf("->%d\n", vetor_A[i]);
    }
}


void contagem_rs_maxs(int vetor_A[], int tam, int d){
    //int tam_c = maior(vetor_A, tam);

    int vetor_B[tam];
    int vetor_C[10] = {0};

    for(int i=0;i<tam;i++){
        int k = (int)(vetor_A[i]/pow(10,d)) % 10; 
        printf("---- K=%d %d\n",k, vetor_A[i]);
        vetor_C[k] = vetor_C[k] + 1;
    }

    for(int i=1;i<10;i++){
        vetor_C[i] = vetor_C[i] + vetor_C[i-1];
    }
    
    for(int i=0;i<tam;i++){
        int k = (int)(vetor_A[i]/pow(10,d))%10;
        int j = vetor_C[k];
        vetor_B[j-1] = vetor_A[i];
        vetor_C[k] = vetor_C[k] - 1;
    }

    for(int i=0;i<tam;i++){
        vetor_A[i] = vetor_B[i];
        printf("->%d\n", vetor_A[i]);
    }
}


void radixsort(int vetor[], int tam, int digs){
    for(int i=0;i<digs;i++){
        //contagem_rs_mins(vetor,tam,i);
        contagem_rs_maxs(vetor,tam,digs-i-1);
    }
}


int main(int argc, char const *argv[])
{
    int vetor[] = {3,3,7,2,7,4,7,6,4,8,8,3,0,2,1,0,2};
    int vetor_rs[] = {366,158,106,197,236,329,217};

    radixsort( vetor_rs, 7, 3);
    
    for(int i=0;i<7;i++){
        printf("%d ", vetor_rs[i]);
    }
    printf("\n");

    return 0;
}
*/