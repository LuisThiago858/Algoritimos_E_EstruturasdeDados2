#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no No;
struct no{
    void*data;
    No*prox;
};

No*criarNo(void* val){
    No*novo=malloc(sizeof(No));
    novo->data=val;
    novo->prox=NULL;
    printf("Criando: %d\n", novo->data);
    return novo;
}

typedef struct LSE{
    No*inicio;
    int tamanho;
}T_LSE;

T_LSE*criarLista(){
    T_LSE*novo=malloc(sizeof(T_LSE));
    novo->inicio=NULL;
    novo->tamanho=0;
}
//operacoes baseadas em posicao
void inserirInicio(T_LSE*lista, void*val){
    No*novo=criarNo(val);
    novo->prox=lista->inicio;
    lista->inicio=novo;
    lista->tamanho++;
}

void* removerInicio(T_LSE*lista){
    void*carga=NULL;
    No*removido=lista->inicio;
    if(lista->inicio!=NULL){
        
        lista->inicio=removido->prox;
        lista->tamanho--;
        carga=removido->data;

        free(removido);
    }
    return carga;
}

void inserirFinal(T_LSE*lista, void*val){
    No*novo=criarNo(val);
    if(lista->tamanho==0){
        lista->inicio=novo;
    }else{
        No*cam=lista->inicio;
        while(cam->prox!=NULL){
            cam=cam->prox;
        }
        cam->prox=novo;
    }
    lista->tamanho++;
}
void* removerFinal(T_LSE*lista){
    void*carga=NULL;
    No*ant=NULL;
    No*cam=lista->inicio;
    if(lista->tamanho==0){
        return carga;
    }else if(lista->tamanho==1){
        cam=lista->inicio;
        lista->inicio=NULL;
    }else{
        while(cam->prox!=NULL){
            ant=cam;
            cam=cam->prox;
        }
        ant->prox=NULL;
    }
    carga=cam->data;
    free(cam);
    lista->tamanho--;
    return carga;
}


void* acessarNaLista(T_LSE*lista, int pos){
    int i=1;
    void*carga=NULL;//entrada invalida
    if(pos<0){
        pos=(pos%lista->tamanho)+(lista->tamanho+1);//corrigido o cálculo para obter o índice correto
        pos=(pos==0?1:pos);//alterado o operador de comparação
    }else if(pos>0){
        pos=pos%lista->tamanho;
        pos=(pos==0?lista->tamanho:pos);
    }else{
        return carga;
    }


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


//listas neutralizadas 

typedef struct musica{
    char nome[50];
    double duracao;
    char artista[50];
    L_musica*prox;
}L_musica;

L_musica*criarListaMusicas(char nome[50], double duracao, char artista[50]){
    L_musica*musica=malloc(sizeof(L_musica));
    musica->duracao=duracao;
    strcpy(musica->artista, artista);
    strcpy(musica->nome, nome);
    musica->prox=NULL;
    return musica;
}

typedef struct albuns{
    char nome_do_album[50];
    int numero_de_faixas;
    char artista[50];
    L_albuns*prox;
}L_albuns;

L_albuns*criarListaAlbuns(char nome_do_album[50], int numero_de_faixas, char artista[50]){
    L_albuns*album=malloc(sizeof(L_albuns));
    album->numero_de_faixas=numero_de_faixas;
    strcpy(album->nome_do_album, nome_do_album);
    strcpy(album->artista, artista);

    album->prox=NULL;

    return album;
}

//Listas no contexto neutralizadas(genérico)

int main(){
    T_LSE*musicas=criarLista();
    //adicionando as listas neutralizadas
    T_LSE*albuns_mais_tocados=criarLista();
    T_LSE*musicas_mais_tocados=criarLista();

    for(int i=1; i<10; i++){
        inserirFinal(musicas, i);
    }
    //imprimirLista(musicas);
    int musica=removerFinal(musicas);
    printf("\nremoveu - %d\n", musica);

    musica=acessarNaLista(musicas, -2);
    printf("\nacessou - %d\n", musica);

    musica=acessarNaLista(musicas, 15);
    printf("\nacessou - %d\n", musica);
    //imprimirLista(musicas);
    return 0;
}