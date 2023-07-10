#include <stdio.h>
#include <stdlib.h>

int main() {
    int *valor;
    valor = malloc(sizeof(int) * 10);  // aloca um array de 10 inteiros
    printf("%p\n", (void*) valor);     // imprime o endereço de memória do array
    printf("%d\n", *valor);            // imprime o valor do primeiro elemento do array
    int valor1;
    valor1 = 100;
    printf("%p\n", (void*) &valor1);   // imprime o endereço de memória da variável valor1
    printf("%d", valor1);              // imprime o valor da variável valor1
}


/*
Explicação:

A linha int *valor; declara um ponteiro para um inteiro.

A linha valor = malloc(sizeof(int) * 10); aloca dinamicamente um array de 10 inteiros e armazena o endereço de memória do
primeiro elemento no ponteiro "valor".

A linha printf("%p\n", (void*) valor); imprime o endereço de memória do array, convertendo o ponteiro para o tipo void* para
evitar um warning.

A linha printf("%d\n", *valor); imprime o valor do primeiro elemento do array, usando o operador de desreferência "*" para
acessar o valor apontado pelo ponteiro.

A linha int valor1; declara uma variável inteira.

A linha valor1 = 100; atribui o valor 100 para a variável valor1.

A linha printf("%p\n", (void*) &valor1); imprime o endereço de memória da variável valor1, usando o operador "&" para obter
o endereço de memória.

A linha printf("%d", valor1); imprime o valor da variável valor1.
*/