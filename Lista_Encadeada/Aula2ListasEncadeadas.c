#include <stdio.h>

typedef struct no No; //da um apelido para esta estrutura com o nome No
struct no{      // o no com dados como data e prox
    int data;
    No*prox;
};

No*criarNo(int val){
    No *novo=(No*)malloc(sizeof(No)); //um cria no que armazena essas informacoes
    novo->data=val;
    novo->prox=NULL;
    return novo;
}

typedef struct LSE{ //cria lista com o inicio da lista e podendo conter outros dados estatisticos como tamanho, numero de insercoes, numero de delecoes etc
    No*inicio;
    int tamanho;
    int num_insercao;
    int num_delecao;
}T_LSE;

T_LSE*criarLista(){
    T_LSE*novo=malloc(sizeof(struct LSE));//Aloca dinamicamente a memoria. Em seguida, ela atribui o valor NULL ao ponteiro inicio do novo objeto T_LSE, indicando que a lista está vazia.
    novo->inicio=NULL;
    return novo;
}

//Busca por posicao
// inserir no inicio
void inserirInicio(T_LSE* lista, int val) {
    No* novo = criarNo(val);
    novo->prox = lista->inicio;
    lista->inicio = novo;
}

// remover no inicio
void removerInicio(T_LSE* lista) {
    if (lista->inicio == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    No* removido = lista->inicio;
    lista->inicio = removido->prox;
    free(removido);
}
// acessa lista
void imprimirLista(T_LSE* lista) {
    if (lista->inicio == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    No* atual = lista->inicio;
    while (atual != NULL) {
        printf("%d -> ", atual->data);
        atual = atual->prox;
    }
    printf("NULL\n");
}
// inserir no final
void inserirFinal(T_LSE* lista, int val) {
    No* novo = criarNo(val);
    if (lista->inicio == NULL) {
        lista->inicio = novo;
        return;
    }
    No* atual = lista->inicio;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = novo;
}
// remover no final
void removerFinal(T_LSE* lista) {
    if (lista->inicio == NULL) {
        return;
    }
    No* anterior = NULL;
    No* atual = lista->inicio;
    while (atual->prox != NULL) {
        anterior = atual;
        atual = atual->prox;
    }
    if (anterior == NULL) {
        lista->inicio = NULL;
    } else {
        anterior->prox = NULL;
    }
    free(atual);
}


//Busca por conteudo

