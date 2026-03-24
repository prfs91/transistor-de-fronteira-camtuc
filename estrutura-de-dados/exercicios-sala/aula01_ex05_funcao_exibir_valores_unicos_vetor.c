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

void exibirValoresUnicos(int vetor[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int repetido = 0; // controla se o valor aparece mais de uma vez

        for (int j = 0; j < n; j++)
        {
            // verifica se existe outro índice com o mesmo valor
            if (i != j && vetor[i] == vetor[j])
            {
                repetido = 1; // marca como repetido
                break; // sai do loop
            }
        }

        // se não encontrou repetição
        if (!repetido)
        {
            printf("%d ", vetor[i]); // imprime o valor único
        }
    }
}

int main()
{
    int vetor[TAM];

    //entrada de dados
    ler_vetor(vetor, TAM, 'V');

    //saída de dados
    exibirValoresUnicos(vetor, TAM);

    return 0;
}