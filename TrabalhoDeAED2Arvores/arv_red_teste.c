#include "stdio.h"
#include "stdlib.h"
#include "arv_red.h"

#define WITHOUT_MEMORY {printf("Without memory\n"); return 0; }
#define ERRO_CODE(x) if(!x){printf("VALOR NULO, MAS Não deveria se nulo\n"); return 0; }

typedef struct Person{

    int id;
    char* name;
    char* email;
    int age;
    double weigth;

}Person;

int isEquals(void* p1, void* p2){

    if(p1==p2) return 1;

    Person* pp1 = p1;
    Person* pp2 = p2;
    
    if(pp1->id != pp2->id) return 0;
    if(pp1->age != pp2->age) return 0;

    return 1;

}

int cmp(void* a, void* b){

    Person* aa = a;
    Person* bb = b;
  
    return aa->id - bb->id;
}

void print(void* person){
    if(!person) return;

    Person* p = person;

    printf("Person:{id=%d, name: %s, email: %s, age:%d, weight:%lf}\n", p->id,p->name, p->email, p->age, p->weigth);

}

int main(){

    t_red* tree = criarRED(&cmp);

    int qnt;
    Person* p;
    Person* *people;

    scanf("%d", &qnt);
    people = malloc(sizeof(Person*)*qnt);
    
    if(!people) WITHOUT_MEMORY

    estatisticaRED(tree);

    for(int i=0; i < qnt; i++){
        
        p = (Person*) malloc(sizeof(Person));
        
        if(p){
            p->name =  (char*) malloc(sizeof(char)*25);
            p->email = (char*) malloc(sizeof(char)*25);

            if(scanf("%d %[^\n]%*c %lf %d %[^\n]%*c",&p->id, p->name, &p->weigth, &p->age, p->email) != 5) 
                print("ERROR AO LER");

           
            inserirRED(tree, p);
            people[i] = p;
         

        }else WITHOUT_MEMORY
        

    }

    for(int i=0; i < qnt; i++){

        void* getPerson = buscarRED(tree, people[i]);
        ERRO_CODE(getPerson)

        if(!isEquals(getPerson, people[i])){
            printf("Valores não iguais");
            return 0;
        }
        // print(getPerson);

    }
    

 
    for(int i=0; i < qnt ; i++){

        void* getPerson = removerRED(tree, people[i]);
        ERRO_CODE(getPerson)


    }

    for(int i=0; i < qnt; i++){

        void* getPerson = buscarRED(tree, people[i]);

        if(getPerson != NULL){
            printf("Deveria ser NULL");
            return 0;
        }
    }


    estatisticaRED(tree);

}