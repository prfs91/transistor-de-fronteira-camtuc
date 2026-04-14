#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIN 5
#define COL 7

void inicializaMatriz(int matriz [LIN][COL])
{
    for (int i = 0; i < LIN; i++)
    {
        for (int j = 0; i < LIN; i++)
        {
            srand(time(NULL));
            matriz[i][j] = rand() %101;
        }
    }
}