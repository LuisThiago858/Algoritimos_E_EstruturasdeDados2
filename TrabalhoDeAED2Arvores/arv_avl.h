typedef int(*TCompararAVL)(void* s1, void* s2);
typedef struct avl t_avl;
typedef struct status t_status;
typedef struct no TNo;

t_avl* criarAVL(TCompararAVL comparar);
int altura(TNo*no);
int fator_balanceamento(TNo*no);
TNo*rotacao_direita(TNo*no);
TNo*rotacao_esquerda(TNo*no);
TNo*balancear_no(TNo*no, t_status*status);
void inserirAVL(t_avl *avl, void* info);
void* buscarAVL(t_avl *avl, void* info);
static void trocar(TNo*no, TNo* no2);
void* removerAVL(t_avl *avl, void* removivel);
void estatisticaAVL(t_avl *avl);
//void imprimirAVL(t_avl* avl);
