#include<stdio.h>
#include<malloc.h>

void permutar (int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int main()
{
    int a = 5, b = 2;

    permutar(&a, &b);

    printf("a = %d e b = %d", a, b);

    
}