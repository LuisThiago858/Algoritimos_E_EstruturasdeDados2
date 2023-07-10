/*
#include <stdio.h>

void intercala(double vetor[], int k, int l, int m){
    double aux[m-k-l];

    int ki=k;
    int mi=l-1;
    int n=0;

    while((ki<=l)&&(mi<=n)){
        if(vetor[ki]<vetor[mi]){
            aux[n]=vetor[ki];
            ki++;
        }
        else{
            aux[n]=vetor[mi];
            mi++;
        }
        n++;
    }
    while(mi<=m){
        aux[n]=vetor[mi];
        n++; mi++;
    }
    while(ki<=l){
        aux[n]=vetor[ki];
        n++; l++;
    }
    for(int i=0; i<m-k-l; i++){
        vetor[k+i]=aux[i];
    }
}

int main(){
    double vetor[]={8.0,9.5,10.0,7.0,8.5,9.0};
    int tam = 6;
    intercala(vetor, 0, 2, 3);
    for(int i=0; i<tam; i++){
        printf("%.2lf ", vetor[i]);
    }
    printf("\n");
    return 0;
}
*/

#include <stdio.h>

void intercala(double vetor[], int k, int l, int m){
    double aux[m-k-l];

    int ki=k;
    int mi=l;
    int n=0;

    while((ki<l)&&(mi<m)){
        if(vetor[ki]<vetor[mi]){
            aux[n]=vetor[ki];
            ki++;
        }
        else{
            aux[n]=vetor[mi];
            mi++;
        }
        n++;
    }
    while(mi<m){
        aux[n]=vetor[mi];
        n++; mi++;
    }
    while(ki<l){
        aux[n]=vetor[ki];
        n++; ki++;
    }
    for(int i=0; i<m-k; i++){
        vetor[k+i]=aux[i];
    }
}

int main(){
    double vetor[]={8.0,9.5,10.0,7.0,8.5,9.0};
    int tam = 6;
    intercala(vetor, 0, 2, 3);
    printf("Resultado: ");
    for(int i=0; i<tam; i++){
        printf("%.2lf ", vetor[i]);
    }
    printf("\n");
    return 0;
}