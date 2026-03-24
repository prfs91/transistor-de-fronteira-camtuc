#include <stdio.h>

void preencher_impares(int vet[], int n)
{
    int impar = 1;

    for (int i = 0; i < n; i++)
    {
        vet[i] = impar;
        impar += 2;
    }
}

int main()
{
    const int QTD_MAX = 500;
    int A[QTD_MAX];

    preencher_impares(A, QTD_MAX);

    printf("Os %d primeiros numeros impares:\n", QTD_MAX);
    for (int i = 0; i < QTD_MAX; i++)
    {
        printf("%8d ", A[i]);
        if((i + 1) % 10 == 0) printf("\n");
    }

}
