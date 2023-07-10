#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void(*da_funcao_trocar)(int*, int*);

void __trocar1(int *nro1, int *nro2){
    int aux;
    aux=*nro1;
    *nro1=*nro2;
    *nro2=aux;
    printf("Troca 1: ");
}

void __trocar2(int *nro1, int*nro2){
    int aux;
    aux=*nro1;
    *nro1=*nro2;
    *nro2=aux;
    printf("Troca 2: ");
}

void chamadora(da_funcao_trocar trocador, int nro_1, int nro_2){
    printf("%d %d\n", nro_1, nro_2);
    trocador(&nro_1, &nro_2);
    printf("%d %d\n", nro_1, nro_2);
}

int main(){
    int maior=30, menor=20;
    da_funcao_trocar trocador;
    trocador=__trocar1;
    printf("%p\n", __trocar1);
    printf("%p\n", trocador);
    __trocar1(&maior, &menor);
    printf("%d %d\n", maior, menor);
    trocador(&maior, &menor);
    printf("%d %d\n", maior, menor);

    chamadora(__trocar1, maior, menor);
    chamadora(__trocar2, maior, menor);
}