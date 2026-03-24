#include <stdio.h>

void fatorial_vetor(const int entrada[], long long saida[], int n)
{
    int valor;
    long long produto_fat;

    for (int i = 0; i < n; i++)
    {
        valor = entrada[i];
        produto_fat = 1;

        for (int k = 1; k <= valor; k = k + 1)
        {
            produto_fat = produto_fat * (long long) k;
        }

        saida[i] = produto_fat;
    }
}


int main()
{
    const int N = 10;

    int A[N];
    long long B[N];

    printf("Digite %d numeros inteiros positivos:\n", N);

    for (int i = 0; i < N; i++)
    {
        printf("Valor [%d]: ", i + 1);
        scanf("%d", &A[i]);
    }

    fatorial_vetor(A, B, N);

    printf("\nResultados:\n");
    for (int i = 0; i < N; i = i + 1) {
        printf("A[%d]: %d | B[%d]: %lld \n", i + 1, A[i], i + 1, B[i]);
    }

}
