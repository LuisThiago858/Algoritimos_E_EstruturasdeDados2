#include "stdio.h"
#include "stdlib.h"
#include "arv_red.h"

#define RED 0
#define BLACK 1

typedef struct no TNo;
struct no {
    void* info;
    int cor;
    TNo* sae;
    TNo* sad;
    TNo* ancestral;
};

TNo* criar_no(TNo* ancestral, void* info) {
    TNo* novo = (TNo*)malloc(sizeof(TNo));
    novo->info = info;
    novo->cor=RED;
    novo->sae = NULL;
    novo->sad = NULL;
    novo->ancestral = ancestral;

    return novo;
}

typedef struct status {
    int i_nro;
    int b_nro;
    int r_nro;
    int b_cmps;
    int i_cmps;
    int r_cmps;
} t_status;

typedef int(*TCompararRED)(void* s1, void* s2);
typedef struct red{
    TNo* raiz;
    //TImprimirRED imprimir;
    TCompararRED comparar;
    t_status status;
    // removerInfoNo
} t_red;

t_red* criarRED(TCompararRED comparar){
    t_red* red = malloc(sizeof(t_red));

    red->raiz = NULL;
    //red->imprimir = imprimir;
    red->comparar = comparar;
    red->status=(t_status){.b_cmps = 0, .i_cmps = 0, .r_cmps = 0, .i_nro = 0, .b_nro = 0, .r_nro = 0};

    return red;
}

void rotacao_esquerda(t_red*red, TNo* no) {
    TNo* direita = no->sad;
    no->sad = direita->sae;
    if (direita->sae != NULL) {
        direita->sae->ancestral = no;
    }
    direita->ancestral = no->ancestral;
    if (no->ancestral == NULL) {
        red->raiz = direita;
    } else if (no == no->ancestral->sae) {
        no->ancestral->sae = direita;
    } else {
        no->ancestral->sad = direita;
    }
    direita->sae = no;
    no->ancestral = direita;
}

void rotacao_direita(t_red* red, TNo* no) {
    TNo* esquerda = no->sae;
    no->sae = esquerda->sad;
    if (esquerda->sad != NULL) {
        esquerda->sad->ancestral = no;
    }
    esquerda->ancestral = no->ancestral;
    if (no->ancestral == NULL) {
        red->raiz = esquerda;
    } else if (no == no->ancestral->sad) {
        no->ancestral->sad = esquerda;
    } else {
        no->ancestral->sae = esquerda;
    }
    esquerda->sad = no;
    no->ancestral = esquerda;
}

void inserirRED(t_red* red, void* info) {
    TNo* novo = criar_no(NULL, info);

    // Caso especial: árvore vazia
    if (red->raiz == NULL) {
        novo->cor = BLACK; // O primeiro nó inserido é sempre preto
        red->raiz = novo;
        return;
    }

    // Busca pelo local de inserção
    TNo* atual = red->raiz;
    TNo* anterior = NULL;
    while (atual != NULL) {
        anterior = atual;

        // Comparação de chaves
        int comparacao = red->comparar(info, atual->info);
        red->status.i_cmps++;

        if (comparacao < 0) {
            atual = atual->sae;
        } else if (comparacao > 0) {
            atual = atual->sad;
        } else {
            // Já existe um nó com a mesma chave, não é permitida a inserção
            free(novo); // Liberar o nó recém-criado
            return;
        }
    }

    // Inserção do novo nó
    novo->ancestral = anterior;
    int comparacao = red->comparar(info, anterior->info);
    red->status.i_cmps++;

    if (comparacao < 0) {
        anterior->sae = novo;
    } else {
        anterior->sad = novo;
    }

    // Realizar ajustes na árvore após a inserção
    while (novo != red->raiz && novo->ancestral->cor == RED) {
        if (novo->ancestral == novo->ancestral->ancestral->sae) {
            TNo* tio = novo->ancestral->ancestral->sad;
            if (tio != NULL && tio->cor == RED) {
                novo->ancestral->cor = BLACK;
                tio->cor = BLACK;
                novo->ancestral->ancestral->cor = RED;
                novo = novo->ancestral->ancestral;
            } else {
                if (novo == novo->ancestral->sad) {
                    novo = novo->ancestral;
                    rotacao_esquerda(red, novo);
                    red->status.i_nro++;
                }
                novo->ancestral->cor = BLACK;
                novo->ancestral->ancestral->cor = RED;
                rotacao_direita(red, novo->ancestral->ancestral);
                red->status.i_nro++;
            }
        } else {
            TNo* tio = novo->ancestral->ancestral->sae;
            if (tio != NULL && tio->cor == RED) {
                novo->ancestral->cor = BLACK;
                tio->cor = BLACK;
                novo->ancestral->ancestral->cor = RED;
                novo = novo->ancestral->ancestral;
            } else {
                if (novo == novo->ancestral->sae) {
                    novo = novo->ancestral;
                    rotacao_direita(red, novo);
                    red->status.i_nro++;
                }
                novo->ancestral->cor = BLACK;
                novo->ancestral->ancestral->cor = RED;
                rotacao_esquerda(red, novo->ancestral->ancestral);
                red->status.i_nro++;
            }
        }
    }

    red->raiz->cor = BLACK; // Garantir que a raiz seja sempre preta
    
}

void* removerRED(t_red* red, void* info) {
    TNo* no = red->raiz;
    TNo* pai = NULL;
    TNo* temp = NULL;
    TNo* substituto = NULL;

    // Busca pelo nó a ser removido
    while (no != NULL) {
        int comparacao = red->comparar(info, no->info);
        red->status.r_cmps++;

        if (comparacao == 0) {
            break;  // Nó encontrado
        }

        pai = no;

        if (comparacao < 0) {
            no = no->sae;
        } else {
            no = no->sad;
        }
    }

    if (no == NULL) {
        return NULL;  // Nó não encontrado, retorna NULL
    }

    

    // Caso 1: nó com dois filhos
    if (no->sae != NULL && no->sad != NULL) {
        TNo* sucessor = no->sad;
        while (sucessor->sae != NULL) {
            sucessor = sucessor->sae;
        }

        no->info = sucessor->info;
        no = sucessor;
    }

    // Define o substituto para o filho do nó a ser removido (caso exista)
    if (no->sae != NULL) {
        substituto = no->sae;
    } else {
        substituto = no->sad;
    }

    // Caso 2: nó sem filhos
    if (substituto == NULL) {
        if (no == red->raiz) {
            red->raiz = NULL;
        } else {
            if (no == pai->sae) {
                pai->sae = NULL;
            } else {
                pai->sad = NULL;
            }
        }

        void* removido = no->info;
        free(no);
        return removido;  // Retorna o valor removido
    }

    // Caso 3: nó com um filho
    substituto->ancestral = pai;
    if (no == red->raiz) {
        red->raiz = substituto;
    } else {
        if (no == pai->sae) {
            pai->sae = substituto;
        } else {
            pai->sad = substituto;
        }
    }

    // Caso especial: o nó removido é vermelho
    if (no->cor == RED) {
        void* removido = no->info;
        free(no);
        return removido;  // Retorna o valor removido
    }

    // Caso 4: nó preto com um filho vermelho
    if (substituto->cor == RED) {
        substituto->cor = BLACK;
        void* removido = no->info;
        free(no);
        return removido;  // Retorna o valor removido
    }

    // Caso 5: nó preto com um filho preto
    while (substituto != red->raiz && substituto->cor == BLACK) {
        if (substituto == substituto->ancestral->sae) {
            temp = substituto->ancestral->sad;

            // Caso 5.1: irmão do substituto é vermelho
            if (temp->cor == RED) {
                temp->cor = BLACK;
                substituto->ancestral->cor = RED;
                rotacao_esquerda(red, substituto->ancestral);
                red->status.r_nro++;
                temp = substituto->ancestral->sad;
            }

            // Caso 5.2: irmão do substituto é preto e seus filhos são pretos
            if ((temp->sae == NULL || temp->sae->cor == BLACK) &&
                (temp->sad == NULL || temp->sad->cor == BLACK)) {
                temp->cor = RED;
                substituto = substituto->ancestral;
            } else {
                // Caso 5.3: irmão do substituto é preto e seu filho à direita é preto
                if (temp->sad == NULL || temp->sad->cor == BLACK) {
                    temp->sae->cor = BLACK;
                    temp->cor = RED;
                    rotacao_direita(red, temp);
                    red->status.r_nro++;
                    temp = substituto->ancestral->sad;
                }

                // Caso 5.4: irmão do substituto é preto e seu filho à direita é vermelho
                temp->cor = substituto->ancestral->cor;
                substituto->ancestral->cor = BLACK;
                temp->sad->cor = BLACK;
                rotacao_esquerda(red, substituto->ancestral);
                red->status.r_nro++;
                substituto = red->raiz;
            }
        } else {
            temp = substituto->ancestral->sae;

            // Caso 5.1: irmão do substituto é vermelho
            if (temp->cor == RED) {
                temp->cor = BLACK;
                substituto->ancestral->cor = RED;
                rotacao_direita(red, substituto->ancestral);
                red->status.r_nro++;
                temp = substituto->ancestral->sae;
            }

            // Caso 5.2: irmão do substituto é preto e seus filhos são pretos
            if ((temp->sae == NULL || temp->sae->cor == BLACK) &&
                (temp->sad == NULL || temp->sad->cor == BLACK)) {
                temp->cor = RED;
                substituto = substituto->ancestral;
            } else {
                // Caso 5.3: irmão do substituto é preto e seu filho à esquerda é preto
                if (temp->sae == NULL || temp->sae->cor == BLACK) {
                    temp->sad->cor = BLACK;
                    temp->cor = RED;
                    rotacao_esquerda(red, temp);
                    red->status.r_nro++;
                    temp = substituto->ancestral->sae;
                }

                // Caso 5.4: irmão do substituto é preto e seu filho à esquerda é vermelho
                temp->cor = substituto->ancestral->cor;
                substituto->ancestral->cor = BLACK;
                temp->sae->cor = BLACK;
                rotacao_direita(red, substituto->ancestral);
                red->status.r_nro++;
                substituto = red->raiz;
            }
        }
    }

    substituto->cor = BLACK;
    void* removido = no->info;
    free(no);
    return removido;  // Retorna o valor removido
}


void* buscarRED(t_red* red, void* info) {
    TNo* no = red->raiz;

    while (no != NULL) {
        int comparacao = red->comparar(info, no->info);
        if (comparacao == 0) {
            red->status.b_cmps++;
            // Realizar ações com o nó encontrado, se necessário
            return no->info;  // Retorna o valor buscado
        } else if (comparacao < 0) {
            no = no->sae;
            red->status.b_cmps++;
        } else {
            red->status.b_cmps++;
            no = no->sad;
        }
    }
    return NULL;  // O nó não foi encontrado, retorna NULL
}


void estatisticaRED(t_red* red) {
    t_status* status = &(red->status);
    printf("I: {Cmp=%d, Rot: %d}, B: {Cmp=%d, Rot: %d}, R: {Cmp=%d, Rot: %d}\n", status->i_cmps, status->i_nro, status->b_cmps, status->b_nro, status->r_cmps, status->r_nro);
}