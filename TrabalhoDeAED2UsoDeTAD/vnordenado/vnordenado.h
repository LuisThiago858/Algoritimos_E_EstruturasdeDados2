typedef int(*TCompararVNOrd)(void*,void*);

typedef struct vetor_nao_ordenado t_nord;
t_nord* criar_vnordenado(int tam, TCompararVNOrd comparar);
int inserir_vnordenado(t_nord* v, void* elem);
void* remover_vnordenado(t_nord* v, int ind);
void* maior_vnordenado(t_nord* v);
void* menor_vnordenado(t_nord* v);
int ocupacao_vnordenado(t_nord* v);
int tamanho_vnordenado(t_nord*v);
void estatistica_vnordenado(t_nord* v);