#include <stdio.h>
#include <stdlib.h>  // biblioteca para funções rand() e srand()
#include <time.h>    // biblioteca para função time()

#define LIN 5        // define quantidade de linhas da matriz
#define COL 7        // define quantidade de colunas da matriz

// função que preenche a matriz com valores aleatórios de 0 a 100
void inicializarMatrizAleatoria(int matriz[LIN][COL]) {
    
    for (int i = 0; i < LIN; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            matriz[i][j] = rand() % 101; // gera número entre 0 e 100
        }
    }
}

void escrever_matriz(int matriz[LIN][COL])
{
    for(int i = 0; i < LIN; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            printf("%d\t ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main()
{

    int matriz[LIN][COL];

    srand(time(NULL)); // inicializa a semente aleatória (evita repetir valores)

    inicializarMatrizAleatoria(matriz);

    //saída de dados
    escrever_matriz(matriz);

    return 0;
}