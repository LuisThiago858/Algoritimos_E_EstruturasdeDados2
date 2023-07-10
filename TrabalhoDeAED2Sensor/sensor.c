#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "listase.h"

typedef struct dadosT ST_dados;

struct dadosT{
    int seq;
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int radiacao_solar;
    double temperatura;
    double umidade_relativa;
};

ST_dados*criarMedicaoT(int seq,int dia,int mes,int ano,int hora,int minuto, int radiacao_solar,double temperatura, double umidade_relativa){
    ST_dados* Ntemperatura=malloc(sizeof(ST_dados));
    Ntemperatura->seq=seq;
    Ntemperatura->dia=dia;
    Ntemperatura->mes=mes;
    Ntemperatura->ano=ano;
    Ntemperatura->hora=hora;
    Ntemperatura->minuto=minuto;
    Ntemperatura->radiacao_solar=radiacao_solar;
    Ntemperatura->temperatura=temperatura;
    Ntemperatura->umidade_relativa=umidade_relativa;

    return Ntemperatura;
}


typedef struct dadosMA SMA_dados;

struct dadosMA{
    int seq;
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    double velocidade_media;
    double velocidade_instantanea;
    int direcao;
};

SMA_dados*criarMedicaoM(int seq, int dia, int mes, int ano, int hora, int minuto, double velocidade_media, double velocidade_instantanea, int direcao){
    SMA_dados*MmedidasMA=malloc(sizeof(SMA_dados));
    MmedidasMA->seq=seq;
    MmedidasMA->dia=dia;
    MmedidasMA->mes=mes;
    MmedidasMA->ano=ano;
    MmedidasMA->hora=hora;
    MmedidasMA->minuto=minuto;
    MmedidasMA->velocidade_media=velocidade_media;
    MmedidasMA->velocidade_instantanea=velocidade_instantanea;
    MmedidasMA->direcao=direcao;

    return MmedidasMA;
}
//inicio funcoes para as medicoes de temperatura
void imprimir_temperatura(void* m){
    ST_dados* mm = m;
    printf("%d %02d/%02d/%d %02d:%02d %d %.2f %.2f\n", mm->seq, mm->dia, mm->mes, mm->ano, mm->hora, mm->minuto, mm->radiacao_solar, mm->temperatura, mm->umidade_relativa);
}

void remover_medicao(t_lse* lse, int diaR, int mesR, int anoR, int horaR, int minR) {
    ST_dados* chave = criarMedicaoT(0, diaR, mesR, anoR, horaR, minR, 0, 0, 0);
    void* resultado = remover_lse(lse, chave);
    free(chave);
}

void buscar_medicao(t_lse*lse, int diaB, int mesB, int anoB, int horaB, int minB){
    ST_dados*chave=criarMedicaoT(0, diaB, mesB, anoB, horaB, minB, 0, 0, 0);
    ST_dados*res=buscar_lse(lse, chave);
    free(chave);
    if(res!=NULL){
        printf("%d %02d/%02d/%d %02d:%02d %d %.2f %.2f\n", res->seq, res->dia, res->mes, res->ano, res->hora,res->minuto, res->radiacao_solar, res->temperatura, res->umidade_relativa);
    }
}

void imprimir_medicoesIntervalo(t_lse *lse, int prim, int segun) {
    for (int i = prim; i <= segun; i++) {
        ST_dados *chave = acessar_lse(lse, i);
        if (chave != NULL) {
            imprimir_temperatura(chave);
        }
    }
}
void acessar_medicao(t_lse*lse, int acess){
    ST_dados*chave=(ST_dados*)acessar_lse(lse, acess);
    if(chave!=NULL){
        printf("%d %02d/%02d/%d %02d:%02d %d %.2f %.2f\n", chave->seq, chave->dia, chave->mes, chave->ano, chave->hora,chave->minuto, chave->radiacao_solar, chave->temperatura, chave->umidade_relativa);
    }
}

void podar_medicoesIntervalo(t_lse*lse, int prim, int segun){
    for(int i=segun;i>=prim; i--){
        remover_lse(lse, (acessar_lse(lse, i)));
    }
}

int comparar_medicoesT(void* m1, void* m2){
    ST_dados *medicao1 = (ST_dados*)m1;
    ST_dados *medicao2 = (ST_dados*)m2;
    
    if (medicao1->ano != medicao2->ano) {
        return medicao1->ano - medicao2->ano;
    } else if (medicao1->mes != medicao2->mes) {
        return medicao1->mes - medicao2->mes;
    } else if (medicao1->dia != medicao2->dia) {
        return medicao1->dia - medicao2->dia;
    } else if (medicao1->hora != medicao2->hora) {
        return medicao1->hora - medicao2->hora;
    } else if (medicao1->minuto != medicao2->minuto) {
        return medicao1->minuto - medicao2->minuto;
    } else {
        return 0;
    }
}
//fim das funcoes de medicao de temperatura

//funcoes para a amostra de vento
void imprimir_vento(void* m){
    SMA_dados* mm = m;
    printf("%d %02d/%02d/%d %02d:%02d %.1f %.1f %d\n", mm->seq, mm->dia, mm->mes, mm->ano, mm->hora, mm->minuto, mm->velocidade_media, mm->velocidade_instantanea, mm->direcao);
}
void remover_amostraV(t_lse* lse, int diaR, int mesR, int anoR, int horaR, int minR) {
    SMA_dados* chave = criarMedicaoM(0, diaR, mesR, anoR, horaR, minR, 0, 0, 0);
    void* resultado = remover_lse(lse, chave);
    free(chave);
}
void buscar_amostraV(t_lse*lse, int diaB, int mesB, int anoB, int horaB, int minB){
    SMA_dados*chave=criarMedicaoM(0, diaB, mesB, anoB, horaB, minB, 0, 0, 0);
    SMA_dados*res=buscar_lse(lse, chave);
    free(chave);
    if(res!=NULL){
        printf("%d %02d/%02d/%d %02d:%02d %.1f %.1f %d\n", res->seq, res->dia, res->mes, res->ano, res->hora,res->minuto, res->velocidade_media, res->velocidade_instantanea, res->direcao);
    }
}
void imprimir_amostraIntervalo(t_lse *lse, int prim, int segun) {
    for (int i = prim; i <= segun; i++) {
        SMA_dados *chave = acessar_lse(lse, i);
        if (chave != NULL) {
            imprimir_vento(chave);
        }
    }
}
void acessar_amostraV(t_lse*lse, int acess){
    SMA_dados*chave=(SMA_dados*)acessar_lse(lse, acess);
    if(chave!=NULL){
        printf("%d %02d/%02d/%d %02d:%02d %.1f %.1f %d\n", chave->seq, chave->dia, chave->mes, chave->ano, chave->hora,chave->minuto, chave->velocidade_media, chave->velocidade_instantanea, chave->direcao);
    }
}

void podar_amostraIntervalo(t_lse*lse, int prim, int segun){
    for(int i=segun;i>=prim; i--){
        remover_lse(lse, (acessar_lse(lse, i)));
    }
}

int comparar_medicoesV(void* m1, void* m2){
    SMA_dados *medicao1 = (SMA_dados*)m1;
    SMA_dados *medicao2 = (SMA_dados*)m2;
    
    if (medicao1->ano != medicao2->ano) {
        return medicao1->ano - medicao2->ano;
    } else if (medicao1->mes != medicao2->mes) {
        return medicao1->mes - medicao2->mes;
    } else if (medicao1->dia != medicao2->dia) {
        return medicao1->dia - medicao2->dia;
    } else if (medicao1->hora != medicao2->hora) {
        return medicao1->hora - medicao2->hora;
    } else if (medicao1->minuto != medicao2->minuto) {
        return medicao1->minuto - medicao2->minuto;
    } else {
        return 0;
    }
}


int main(int argc, char const *argv[]){

    const int tipo =(int) argv[1][0]-48;
    const char* nome_arquivo = argv[2];
    t_lse*medicoes=criar_lse(&imprimir_temperatura, &comparar_medicoesT);
    t_lse*medicoes2=criar_lse(&imprimir_vento, &comparar_medicoesV);

    //variaveis para a lista de medicoes temperatura
    int diaR, mesR, anoR, horaR, minR;
    int xI, yI;
    int xA;
    int diaB, mesB, anoB, horaB, minB;
    int xP, yP;

    if((argc==3) && (strcmp(argv[1], "1")==0)){
        FILE *arquivo=fopen(argv[2], "r");
        int seq, dia, mes, ano, hora, minuto, radiacao_solar;
        double temperatura, umidade_relativa;
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
        while(fscanf(arquivo, "%d   %d/%d/%d %d:%d %d  %lf %lf", &seq, &dia, &mes, &ano, &hora, &minuto, &radiacao_solar,&temperatura,&umidade_relativa)==9){
            ST_dados*dados=criarMedicaoT(seq,dia,mes,ano,hora,minuto,radiacao_solar,temperatura,umidade_relativa);
            inserir_final_lse(medicoes, dados);
        }
        fclose(arquivo);
        char opcao;
        while (1) {
            scanf("%c", &opcao);
            if(opcao=='R'){ 
                    scanf("%d/%d/%d %d:%d", &diaR, &mesR, &anoR, &horaR, &minR);
                    remover_medicao(medicoes, diaR, mesR, anoR, horaR, minR);        
            }
            else if(opcao=='I'){
                    scanf("%d %d", &xI, &yI);
                    imprimir_medicoesIntervalo(medicoes, xI, yI);   
            }
            else if(opcao=='A'){
                    scanf("%d", &xA);
                    acessar_medicao(medicoes, xA);      
            }
            else if(opcao=='B'){
                    scanf("%d/%d/%d %d:%d", &diaB, &mesB, &anoB, &horaB, &minB);
                    buscar_medicao(medicoes, diaB, mesB, anoB, horaB, minB);      
            }
            else if(opcao=='P'){
                    scanf("%d %d", &xP, &yP);
                    podar_medicoesIntervalo(medicoes, xP, yP);        
            }else if(opcao=='F'){
                break;
            }
        }  
    }
    if( (argc==3) && (strcmp(argv[1], "2")==0)){
        FILE *arquivo2=fopen(argv[2], "r");
        int seq, dia, mes, ano, hora, minuto, direcao;
        double velocidade_media, velocidade_instantanea;
        if (arquivo2 == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
        while(fscanf(arquivo2, "%d  %d/%d/%d %d:%d %lf %lf %d", &seq, &dia, &mes, &ano, &hora, &minuto, &velocidade_media, &velocidade_instantanea, &direcao)==9){
            SMA_dados*dados2=criarMedicaoM(seq, dia, mes, ano, hora, minuto,velocidade_media, velocidade_instantanea, direcao);
            inserir_final_lse(medicoes2, dados2);
        }
        fclose(arquivo2);
        char opcao2;
        while (1) {
            scanf("%c", &opcao2);
            if(opcao2=='R'){ 
                    scanf("%d/%d/%d %d:%d", &diaR, &mesR, &anoR, &horaR, &minR);
                    remover_amostraV(medicoes2, diaR, mesR, anoR, horaR, minR);        
            }
            else if(opcao2=='I'){
                    scanf("%d %d", &xI, &yI);
                    imprimir_amostraIntervalo(medicoes2, xI, yI);   
            }
            else if(opcao2=='A'){
                    scanf("%d", &xA);
                    acessar_amostraV(medicoes2, xA);      
            }
            else if(opcao2=='B'){
                    scanf("%d/%d/%d %d:%d", &diaB, &mesB, &anoB, &horaB, &minB);
                    buscar_amostraV(medicoes2, diaB, mesB, anoB, horaB, minB);      
            }
            else if(opcao2=='P'){
                    scanf("%d %d", &xP, &yP);
                    podar_amostraIntervalo(medicoes2, xP, yP);        
            }else if(opcao2=='F'){
                break;
            }
        } 
    }
    
    return 0;
}