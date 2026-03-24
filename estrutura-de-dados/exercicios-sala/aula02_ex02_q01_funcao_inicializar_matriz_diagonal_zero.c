#include <stdio.h>

#define TAM 5

void inicializarMatrizDiagonalZero(int matriz[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (i == j) {
                matriz[i][j] = 0;
            } else {
                matriz[i][j] = 1;
            }
        }
    }
}

void escrever_matriz(int matriz[TAM][TAM])
{
    for(int i = 0; i < TAM; i++)          // percorre as linhas
    {
        for(int j = 0; j < TAM; j++)      // percorre as colunas
        {
            printf("%5d ", matriz[i][j]);  // imprime valor com espaço
        }
        printf("\n");                     // quebra linha ao final da linha
    }
}

int main() {
    int matriz[TAM][TAM];

    inicializarMatrizDiagonalZero(matriz);

    // Exibir para conferência
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}