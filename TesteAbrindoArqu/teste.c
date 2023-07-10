#include <stdio.h>
#include <stdlib.h>

typedef struct medicao {
    int dia, mes, ano, hora;
    struct medicao *prox;
} Medicao;

Medicao *criar_medicao(int dia, int mes, int ano, int hora) {
    Medicao *nova_medicao = (Medicao*) malloc(sizeof(Medicao));
    nova_medicao->dia = dia;
    nova_medicao->mes = mes;
    nova_medicao->ano = ano;
    nova_medicao->hora = hora;
    nova_medicao->prox = NULL;
    return nova_medicao;
}

void inserir_medicao(Medicao **lista, Medicao *nova_medicao) {
    printf("chegou na insercao");
    if (*lista == NULL) {
        *lista = nova_medicao;
    } else {
        Medicao *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = nova_medicao;
    }
}

void imprimir_medicoes(Medicao *lista) {
    Medicao *atual = lista;
    printf("chegou na medicao");
    while (atual != NULL) {
        printf("%02d/%02d/%04d %02d:00\n", atual->dia, atual->mes, atual->ano, atual->hora);
        atual = atual->prox;
    }
}

int main() {
    FILE *arquivo;
    int dia, mes, ano, hora;
    Medicao *lista_medicoes = NULL;

    arquivo = fopen("arquivo.txt", "r");
    while (fscanf(arquivo, "%d/%d/%d %d", &dia, &mes, &ano, &hora) == 4) {
        Medicao *nova_medicao = criar_medicao(dia, mes, ano, hora);
        printf("Leu: %d/%d/%d %d\n", dia, mes, ano, hora);
        inserir_medicao(&lista_medicoes, nova_medicao);
    }

    fclose(arquivo);

    imprimir_medicoes(lista_medicoes);

    return 0;
}
