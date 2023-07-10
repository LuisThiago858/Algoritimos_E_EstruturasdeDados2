#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE*arquivo;
    arquivo=fopen("tralho.txt","r");

    int x, y, z;
    while(fscanf(arquivo, "%d %d %d", &x, &y, &z)==3){
        printf("%d %d %d\n", x, y, z);
    }
    fclose(arquivo);
    return 0;
}