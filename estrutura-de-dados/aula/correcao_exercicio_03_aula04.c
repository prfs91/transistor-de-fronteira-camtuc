#include <stdio.h>
#include <malloc.h>
#include <string.h>

computarTamanhos(char **vetorCadeias, int N, int *vetorTamanhos){
    for (int i = 0; i < N; i++)
    {
        
    }
    
}


int main (){

    char **vetorCadeias;
    int N;
    printf("Quantas cadeias?\n");
    scanf("%d", &N);
    getchar(); // remove o \n

    vetorCadeias = (char **) malloc (N* sizeof (char *));
/*
    for (int i = 0; i < N; i++)
    {
        vetorCadeias[i] = (char*) malloc (51 * sizeof (char));
        scanf("%s", vetorCadeias[i]);
    }
*/
    char aux[51];
    for (int i = 0; i < N; i++)
    {
        scanf("%s", aux);
        vetorCadeias[i] = (char*) malloc ((strlen(aux)+1) * sizeof(char));
        strcpy(vetorCadeias[i], aux);
    }
    

    

    int *vetorTamanhos = (int *) malloc (N * sizeof(int));
    computarTamanhos(vetorCadeias, N, vetorTamanhos);
    
    printf("\n");

    for (int i = 0; i < N; i++)
    {
        printf("%s (%d) \n", vetorCadeias[i], vetorTamanhos[i]);
    }

}