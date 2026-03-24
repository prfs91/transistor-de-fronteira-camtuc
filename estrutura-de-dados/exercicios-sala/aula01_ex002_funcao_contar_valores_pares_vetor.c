#include <stdio.h>

#define TAM 5

void ler_vetor(int vetor[], int n, char nome_vetor)
{
    for(int i = 0; i < n; i++)
    {
        printf("%c[%d]: ", nome_vetor, i + 1);
        scanf("%d", &vetor[i]);
    }
}

int contarPares(int vetor[], int n)
{
    int qtd_pares = 0;

    for (int i = 0; i < n; i++)
    {
        if (vetor[i] % 2 == 0) qtd_pares++;
    }

    return qtd_pares;
}

int main()
{
    int vetor[TAM];

    ler_vetor(vetor, TAM, 'V');

    printf("\n");
    
    //saída de dados
    printf("%d", contarPares(vetor, TAM));

    return 0;
}
