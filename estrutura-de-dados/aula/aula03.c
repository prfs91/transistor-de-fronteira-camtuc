#include <stdio.h>
#include <malloc.h>

int main()
{
    printf("Tamanho de inteiro: %d\n", sizeof(int));
    printf("Tamanho de char: %d\n", sizeof(char));
    printf("Tamanho de double: %d\n", sizeof(double));
    printf("Tamanho de long: %d\n", sizeof(long));
    printf("Tamanho de void*: %d\n", sizeof(void*));
    printf("Tamanho de inteiro*: %d\n", sizeof(int*));
    printf("Tamanho de char*: %d\n", sizeof(char*));
    printf("Tamanho de double*: %d\n", sizeof(double*));
    printf("Tamanho de long*: %d\n", sizeof(long*));
}