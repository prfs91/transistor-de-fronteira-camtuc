#include <stdio.h>
#include <malloc.h>

void maximoMinimo (int *v, int num, int *maximo, int *minimo ){
    if (num < 1){
        printf("Não vao dar");
        return;
    }

    *maximo = *minimo = v[0];

    for (int i = 1; i < num; i++){
        if (v[i] < *minimo) *minimo = v[i];
        if (v[i] > *maximo) *maximo = v[i];
    }
}

int main(){
    int vetor [] = {1, 5, 8, 9, 3, 4};
    int N = 6;
    int max;
    int min;

    maximoMinimo (vetor, N, &max, &min);

    printf("Max: %d\nMin: %d\n", max, min);
}