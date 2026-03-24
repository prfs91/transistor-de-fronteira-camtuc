#include <stdio.h>

void leitura_vetor(int vetor[], int n, char nome_vet)
{
    printf("Digite os %d elementos do vetor %c:\n", n, nome_vet);
    for (int i = 0; i < n; i++)
    {
        printf("%c[%d]: ", nome_vet, i + 1);
        scanf("%d", &vetor[i]);
    }
}

void soma_vetores_por_posicao(const int vet1[], const int vet2[], int vet3[], int n)
{
    for (int i = 0; i < n; i++)
    {
        vet3[i] = vet1[i] + vet2[i];
    }
}

int main()
{
    const int TAM = 3;
    int A[TAM];
    int B[TAM];
    int C[TAM];

    leitura_vetor(A, TAM, 'A');
    leitura_vetor(B, TAM, 'B');

    soma_vetores_por_posicao(A, B, C, TAM);

    printf("\nResultados (C = A + B):\n");
    for (int i = 0; i < TAM; i++)
    {
        printf("A[%d]: %d, B[%d]: %d, C[%d]: %d \n", i + 1, A[i], i + 1, B[i], i + 1, C[i]);
    }

}
