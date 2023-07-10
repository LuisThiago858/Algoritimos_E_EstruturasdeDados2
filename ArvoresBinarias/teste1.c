#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* right;
    struct Node* left;
} Node;

Node* inserir(Node* root, int data){
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    if (root == NULL){
        root = temp;
    } else {
        Node* atual = root;
        Node* pai = NULL;
        while (1){
            pai = atual;
            if (data < pai->data){
                atual = atual->left;
                if (atual == NULL){
                    pai->left = temp;
                    return root;
                }
            } else {
                atual = pai->right;
                if (atual == NULL){
                    pai->right = temp;
                    return root;
                }
            }
        }
    }
}

void emordem_tranversal(Node* root){
    if (root){
        emordem_tranversal(root->left);
        printf("%d ", root->data);
        emordem_tranversal(root->right);
    }
}

Node* procurar(Node* root, int data){
    Node* atual = root;
    printf("Visitando o elemento: ");
    while (atual){
        printf("%d ", atual->data);
        if (data < atual->data){
            atual = atual->left;
        } else if (data > atual->data){
            atual = atual->right;
        } else {
            return atual;
        }
    }
    return NULL; // retorna NULL se o valor não for encontrado
}

int main(){
    int i;
    int array[14] = {34, 84, 15, 0, 2, 99, 79, 9, 88, 89, 18, 31, 39, 100};
    Node* root = NULL;

    for (i = 0; i < 13; i++){
        root = inserir(root, array[i]);
        printf("Inserindo: %d\n", array[i]);
    }

    printf("\nEm ordem tranversal:\n");
    emordem_tranversal(root);

    Node* temp = procurar(root, 88);
    if (temp){
        printf("\n[%d] Encontrado.\n", temp->data);
    } else {
        printf("\n[88] não encontrado.\n");
    }

    return 0;
}
