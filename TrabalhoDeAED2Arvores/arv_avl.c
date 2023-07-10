#include "stdio.h"
#include "stdlib.h"
#include "arv_avl.h"

typedef struct no TNo;
struct no {
    void* info;
    TNo* sae;
    TNo* sad;
    TNo* ancestral;
};

TNo* criar_no(TNo* ascentral, void* info) {
    TNo* novo = malloc(sizeof(TNo));
    novo->info = info;
    novo->sae = NULL;
    novo->sad = NULL;
    novo->ancestral = ascentral;

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

typedef struct avl {
    TNo* raiz;
    TCompararAVL comparar;
    t_status status;
} t_avl;

t_avl* criarAVL(TCompararAVL comparar) {
    t_avl* avl = malloc(sizeof(t_avl));

    avl->raiz = NULL;
    avl->comparar = comparar;
    avl->status = (t_status){.b_cmps = 0, .i_cmps = 0, .r_cmps = 0, .i_nro = 0, .b_nro = 0, .r_nro = 0};

    return avl;
}

int altura(TNo* no) {
    if (no == NULL)
        return -1;
    else {
        int sae_altura = altura(no->sae);
        int sad_altura = altura(no->sad);
        return (sae_altura > sad_altura) ? sae_altura + 1 : sad_altura + 1;
    }
}

int fator_balanceamento(TNo* no) {
    if (no == NULL)
        return 0;
    else
        return altura(no->sae) - altura(no->sad);
}

TNo* rotacao_direita(TNo* no) {
    TNo* novo_pai = no->sae;
    no->sae = novo_pai->sad;
    if (novo_pai->sad != NULL)
        novo_pai->sad->ancestral = no;
    novo_pai->sad = no;
    novo_pai->ancestral = no->ancestral;
    no->ancestral = novo_pai;

    return novo_pai;
}

TNo* rotacao_esquerda(TNo* no) {
    TNo* novo_pai = no->sad;
    no->sad = novo_pai->sae;
    if (novo_pai->sae != NULL)
        novo_pai->sae->ancestral = no;
    novo_pai->sae = no;
    novo_pai->ancestral = no->ancestral;
    no->ancestral = novo_pai;

    return novo_pai;
}

TNo* balancear_no(TNo* no, t_status* status) {
    int fb = fator_balanceamento(no);

    if (fb > 1) {
        if (fator_balanceamento(no->sae) > 0) {
            no = rotacao_direita(no);
            //status->r_nro++;
        } else {
            no->sae = rotacao_esquerda(no->sae);
            no = rotacao_direita(no);
            //status->r_nro += 2;
        }
        status->r_cmps++;
    } else if (fb < -1) {
        if (fator_balanceamento(no->sad) < 0) {
            no = rotacao_esquerda(no);
            //status->r_nro++;
        } else {
            no->sad = rotacao_direita(no->sad);
            no = rotacao_esquerda(no);
            //status->r_nro += 2;
        }
        //status->r_cmps++;
    }

    return no;
}

//incompleto

static TNo* __inserirAVL(TNo* raiz, void* info, TCompararAVL comparar, t_status* status) {
    if (raiz == NULL) {
        raiz = criar_no(NULL, info);
        return raiz;
    }

    if (comparar(info, raiz->info) < 0) {
        raiz->sae = __inserirAVL(raiz->sae, info, comparar, status);
        raiz->sae->ancestral = raiz;
        status->i_cmps++;
    } else if (comparar(info, raiz->info) > 0) {
        raiz->sad = __inserirAVL(raiz->sad, info, comparar, status);
        raiz->sad->ancestral = raiz;
        status->i_cmps++;
    }

    int fb = fator_balanceamento(raiz);

    if (fb > 1) {
        if (comparar(info, raiz->sae->info) < 0) {
            raiz = rotacao_direita(raiz);
            status->i_nro++;
            status->i_cmps++;
        } else {
            raiz->sae = rotacao_esquerda(raiz->sae);
            raiz = rotacao_direita(raiz);
            status->i_nro++;
            status->i_cmps += 2;
        }
    } else if (fb < -1) {
        if (comparar(info, raiz->sad->info) > 0) {
            raiz = rotacao_esquerda(raiz);
            status->i_nro++;
            status->i_cmps++;
        } else {
            raiz->sad = rotacao_direita(raiz->sad);
            raiz = rotacao_esquerda(raiz);
            status->i_nro++;
            status->i_cmps += 2;
        }
    }

    return raiz;
}

void inserirAVL(t_avl *avl, void* info) {
    t_status* status = &(avl->status);
    avl->raiz = __inserirAVL(avl->raiz, info, avl->comparar, status);
}


static TNo* __buscarAVL(TNo* raiz, void* info, TCompararAVL comparar, t_status* status) {
    if (raiz == NULL || comparar(info, raiz->info) == 0) {
        status->b_cmps++;
        return raiz;
    }

    if (comparar(info, raiz->info) < 0) {
        status->b_cmps++;
        return __buscarAVL(raiz->sae, info, comparar, status);
    } else {
        status->b_cmps++;
        return __buscarAVL(raiz->sad, info, comparar, status);
    }
}

void* buscarAVL(t_avl *avl, void* info){
    t_status* status = &(avl->status);
    TNo* no = __buscarAVL(avl->raiz, info, avl->comparar, status);
    return (no != NULL?no->info:NULL);
}

static void trocar(TNo* no, TNo* no2) {
    void* aux = no->info;
    no->info = no2->info;
    no2->info = aux;
}

static TNo* __removerAVL(TNo* raiz, void* info, TCompararAVL comparar, t_status* status) {
    if (raiz == NULL)
        return raiz;

    if (comparar(info, raiz->info) < 0) {
        raiz->sae = __removerAVL(raiz->sae, info, comparar, status);
        status->r_cmps++;
    } else if (comparar(info, raiz->info) > 0) {
        raiz->sad = __removerAVL(raiz->sad, info, comparar, status);
        status->r_cmps++;
    } else {
        if (raiz->sae == NULL || raiz->sad == NULL) {
            TNo* temp = raiz->sae ? raiz->sae : raiz->sad;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }

            free(temp);
            status->r_nro++;
        } else {
            TNo* temp = raiz->sad;

            while (temp->sae != NULL) {
                temp = temp->sae;
                status->r_cmps++;
            }

            trocar(raiz, temp);

            raiz->sad = __removerAVL(raiz->sad, info, comparar, status);
            status->r_cmps++;
        }
    }

    if (raiz == NULL)
        return raiz;

    int fb = fator_balanceamento(raiz);

    if (fb > 1) {
        if (fator_balanceamento(raiz->sae) >= 0) {
            raiz = rotacao_direita(raiz);
            status->r_nro++;
        } else {
            raiz->sae = rotacao_esquerda(raiz->sae);
            raiz = rotacao_direita(raiz);
            status->r_nro += 2;
        }
        status->r_cmps++;
    } else if (fb < -1) {
        if (fator_balanceamento(raiz->sad) <= 0) {
            raiz = rotacao_esquerda(raiz);
            status->r_nro++;
        } else {
            raiz->sad = rotacao_direita(raiz->sad);
            raiz = rotacao_esquerda(raiz);
            status->r_nro += 2;
        }
        status->r_cmps++;
    }

    return raiz;
}

void* removerAVL(t_avl* avl, void* removivel) {
    t_status* status = &(avl->status); 
    avl->raiz = __removerAVL(avl->raiz, removivel, avl->comparar, status);  

}

void estatisticaAVL(t_avl* avl) {
    t_status* status = &(avl->status);
    printf("I: {Cmp=%d, Rot: %d}, B: {Cmp=%d, Rot: %d}, R: {Cmp=%d, Rot: %d}\n", status->i_cmps, status->i_nro, status->b_cmps, status->b_nro, status->r_cmps, status->r_nro);
    
}
