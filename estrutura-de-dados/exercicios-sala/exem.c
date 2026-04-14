#include <stdio.h>

void nosDoisVetores (int vetor1[20], int vetor2[20])
{
    for (int i = 0; i < 20; i++)
    {
        int valorDoVetor1NaPosicaoI = vetor1 [i];
        for (int j = 0; j < 20; j++){
            int valorDoVetor2NaPosicaoJ = vetor2[j];
            if (valorDoVetor1NaPosicaoI == valorDoVetor2NaPosicaoJ){
                printf("%ds", valorDoVetor1NaPosicaoI);
                break;
            }
        }
    }
}



int main()
{
    
}