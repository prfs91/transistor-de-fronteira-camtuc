#include <stdio.h>

void ordenar_vetor_crescente(double vet[], int n)
{
    double aux;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (vet[j] > vet[j + 1])
            {
                aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
        }
    }
}

int main()
{
    const int MAX = 10;
    double A[MAX];

    int i;

    printf("Digite %d valores reais:\n", MAX);
    for (i = 0; i < MAX; i++)
    {
        printf("A[%d] = ", i + 1);
        scanf("%lf", &A[i]);
    }

    ordenar_vetor_crescente(A, MAX);

    printf("\nVetor ordenado em ordem crescente:\n");

    for (i = 0; i < MAX; i++)
    {
        printf("A[%d] = %10.4f  ", i + 1, A[i]);
        if((i + 1) % 5 == 0) printf("\n");
    }

}