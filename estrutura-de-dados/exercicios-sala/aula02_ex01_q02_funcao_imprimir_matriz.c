#include <stdio.h>

#define LIN 5
#define COL 7
/*
void ler_matriz(int matriz[LIN][COL], char nome_mat)
{
    for(int i = 0; i < LIN; i++)              // percorre as linhas
    {
        for(int j = 0; j < COL; j++)          // percorre as colunas
        {
            printf("%c[%d][%d]: ", nome_mat, i + 1, j + 1); // exibe posição
            scanf("%d", &matriz[i][j]);       // lê valor e armazena
        }
    }
}
*/


// função que preenche a matriz com valores aleatórios de 0 a 100
void inicializarMatrizAleatoria(int matriz[LIN][COL]) {
    
    for (int i = 0; i < LIN; i++) {          // percorre as linhas
        for (int j = 0; j < COL; j++) {      // percorre as colunas
            matriz[i][j] = rand() % 101;     // gera número entre 0 e 100
        }
    }
}


void imprimirMatriz(int matriz[LIN][COL])
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
    inicializarMatrizAleatoria(matriz);  // chama a função para preencher a matriz


    // Saída
    imprimirMatriz(matriz);

    return 0;
}