#include <stdio.h>

#define TAM 5

void ler_vetor(int vet[], int n, char nome_vet)
{
    for(int i = 0; i < n; i++)
    {
        printf("%c[%d]: ", nome_vet, i + 1);
        scanf("%d", &vet[i]);
    }
}

void inverterVetor(int vetor[], int n)
{
    for (int i = 0; i < TAM / 2; i++)
    {
        int temp = vetor[i];
        vetor[i] = vetor[n - 1 - i];
        vetor[n - 1 - i] = temp;
    }
}

void escrever_vetor(int vet[], int n, char nome_vet)
{
    for(int i = 0; i < n; i++)
    {
        printf("%c[%d]: %d\n", nome_vet, i + 1, vet[i]);
    }
}

int main()
{
    int vetor[TAM];

    //entrada de dados
    ler_vetor(vetor, TAM, 'V');

    inverterVetor(vetor, TAM);

    //saída de dados
    escrever_vetor(vetor, TAM, 'V');
    return 0;
}