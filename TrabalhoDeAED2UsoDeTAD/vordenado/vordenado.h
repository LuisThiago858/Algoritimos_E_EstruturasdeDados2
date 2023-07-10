typedef int(*TCompararVOrd)(void*,void*);

typedef struct v_ordenado t_ord;
t_ord* criar_vnordenado(int tam, TCompararVOrd comparar);
void inserir_vordenado(t_ord* v, void* elemento);
void remover_vordenado(t_ord* v, void* elemento);
void* maior_vordenado(t_ord* v);
void* menor_vordenado(t_ord* v);
int ocupacao_vnordenado(t_ord* v);
int tamanho_vnordenado(t_ord* v);
void estatistica_vordenado(t_ord* v);