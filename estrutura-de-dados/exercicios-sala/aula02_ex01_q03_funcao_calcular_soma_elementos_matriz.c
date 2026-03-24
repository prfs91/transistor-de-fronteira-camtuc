#include <stdio.h>

#define LIN 5
#define COL 7

int calcularSomaMatriz(int matriz[LIN][COL]) {
    int soma = 0;

    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            soma += matriz[i][j];
        }
    }

    return soma;
}

void escrever_matriz(int matriz[LIN][COL])
{
    for(int i = 0; i < LIN; i++)          // percorre as linhas
    {
        for(int j = 0; j < COL; j++)      // percorre as colunas
        {
            printf("%5d ", matriz[i][j]);  // imprime valor com espaço
        }
        printf("\n");                     // quebra linha ao final da linha
    }
}

int main() {
    int matriz[LIN][COL];

    // Entrada
    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    // Saída
    printf("%d", calcularSomaMatriz(matriz));

    return 0;
}