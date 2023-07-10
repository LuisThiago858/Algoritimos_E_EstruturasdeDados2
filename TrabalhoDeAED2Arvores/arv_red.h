typedef int(*TCompararRED)(void* s1, void* s2);

typedef struct no TNo;
typedef struct status t_status;
typedef struct red t_red;

t_red*criarRED(TCompararRED comparar);
void rotacao_esquerda(t_red*red, TNo*no);
void rotacao_direita(t_red*red, TNo*no);
void inserirRED(t_red*red, void*info);
void* removerRED(t_red*red, void*info);
void* buscarRED(t_red*red, void*info);
void estatisticaRED(t_red*red);

