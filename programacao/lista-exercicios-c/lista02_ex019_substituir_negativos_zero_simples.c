#include <stdio.h>

void leitura_vetor(int vet[], int n, char nome_vet)
{
    for(int i = 0; i < n; i++)
    {
        printf("%c[%d]: ", nome_vet, i + 1);
        scanf("%d", &vet[i]);
    }
}

void substituir_negativos_por_zero(int vet[], int n)
{
    for(int i = 0; i < n; i++)
    {
        if (vet[i] < 0)
        {
            vet[i] = 0;
        }
    }
}

void escreve_vetor(int vet[], int n, char nome_vet)
{
    for(int i = 0; i < n; i++)
    {
        printf("%c[%d]: %d\n", nome_vet, i + 1, vet[i]);
    }
}

int main()
{
    const int TAM = 25;
    int A[TAM];

    leitura_vetor(A, TAM, 'A');

    substituir_negativos_por_zero(A, TAM);

    printf("\n");
    escreve_vetor(A, TAM, 'A');

}


