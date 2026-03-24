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

void exibirPrimeiraOcorrencia(int vetor[], int n)
{
    // percorre todo o vetor
    for (int i = 0; i < n; i++)
    {
        int jaImpresso = 0;

        // verifica apenas posições anteriores
        for (int j = 0; j < i; j++)
        {
            if (vetor[i] == vetor[j])
            {
                jaImpresso = 1; // marca como já existente
                break; // sai do loop
            }
        }

        // se ainda não apareceu
        if (!jaImpresso)
        {
            // imprime o valor
            printf("%d ", vetor[i]);
        }
    }
}

int main()
{
    int vetor[TAM];

    //entrada de dados
    ler_vetor(vetor, TAM, 'V');


    //saída de dados
    exibirPrimeiraOcorrencia(vetor, TAM);

    return 0;
}