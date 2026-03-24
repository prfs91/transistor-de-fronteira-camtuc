#include <stdio.h>   // biblioteca para entrada e saída (printf)
#include <stdlib.h>  // biblioteca para funções rand() e srand()
#include <time.h>    // biblioteca para função time()

#define LIN 5        // define quantidade de linhas da matriz
#define COL 7        // define quantidade de colunas da matriz

// função que preenche a matriz com valores aleatórios de 0 a 100
void inicializarMatrizAleatoria(int matriz[LIN][COL]) {
    
    for (int i = 0; i < LIN; i++) {          // percorre as linhas
        for (int j = 0; j < COL; j++) {      // percorre as colunas
            matriz[i][j] = rand() % 101;     // gera número entre 0 e 100
        }
    }
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

    int matriz[LIN][COL];  // declaração da matriz 5x7

    srand(time(NULL));     // inicializa a semente aleatória (evita repetir valores)

    inicializarMatrizAleatoria(matriz);  // chama a função para preencher a matriz

    // exibe a matriz para conferência
    escrever_matriz(matriz);

    return 0;  // indica que o programa terminou corretamente
}