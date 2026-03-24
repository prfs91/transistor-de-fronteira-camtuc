#include <stdio.h>

#define TAM 5

void ler_vetor(int vet[], int n, char nome_vet[])
{
    for(int i = 0; i < n; i++)
    {
        printf("%s[%d]: ", nome_vet, i + 1);
        scanf("%d", &vet[i]);
    }
}

void exibirValoresComuns(int vetor1[], int vetor2[], int n)
{
    // percorre o vetor1
    for (int i = 0; i < n; i++)
    {
        int jaImpresso = 0;

        // evita imprimir repetidos do vetor1
        for (int k = 0; k < i; k++) // percorre posições anteriores
        {
            // verifica se já apareceu antes
            if (vetor1[i] == vetor1[k])
            {
                jaImpresso = 1; // marca como repetido
                break; // sai do loop
            }
        }

        // se já apareceu, pula para o próximo i, não executa o resto
        if (jaImpresso) continue;

        // verifica se existe no vetor2
        for (int j = 0; j < n; j++) // percorre o vetor2
        {
            if (vetor1[i] == vetor2[j])
            {
                printf("%d ", vetor1[i]); // imprime valor comum
                break; // evita repetir impressão
            }
        }
    }
}

int main()
{
    int vetor1[TAM], vetor2[TAM];

    //entrada de dados
    ler_vetor(vetor1, TAM, "V1");
    ler_vetor(vetor2, TAM, "V2");

    //saída de dados
    exibirValoresComuns(vetor1, vetor2, TAM);

    return 0;
}