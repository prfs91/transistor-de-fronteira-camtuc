#include<stdio.h>
#include<malloc.h>

#define MAX 50


int tamanho (char *cadeia){
    int contador = 0;
    while (cadeia[contador != '\0']) contador ++;
    return contador;
}

char *concatenar (char *string1, char *string2){
    int tamanho1 = tamanho (string1);
    int tamanho2 = tamanho (string1);
    int tamanhoRes = tamanho1 + tamanho2;
    char resultado = (char) * malloc (tamanhoRes * sizeof(char));
    for (int i = 0; i < tamanho1; i++)
    {
        resultado[i] = string1[i];
    }

    for (int i = 0; i < tamanho1; i++)
    {
        resultado[i+tamanho] = string2[i];
    }

    return resultado;
}
int main()
{

    int quantidade;

    
    printf("Quantidade de palavras que deseja digitar: ");
    scanf("%d", & quantidade);
    
    // Alocar o espaço para as linhas da matriz
    int **matriz = (int **) malloc (sizeof (int *) * quantidade);
    
    for (int i = 0; i < quantidade; i++) {
    //Alocar o espaço das colunas para cada linha da matriz
        printf("Digite a palavra %d: ", & i + 1);
        scanf("%s*", &matriz_palavras[i]);
        
         = (char *) malloc (sizeof (char) * COLUNAS);
    }
    for (i = 0; i < LINHAS; i++) {
    for (j = 0; j < COLUNAS; j++) {
    // Acesso aos elementos da matriz e inicialização dos valores
    matriz [i][j] = i * COLUNAS + j;
    }
    }
    for (i = 0; i < LINHAS; i++) {
    free (matriz [i]);
    }
    free (matriz);

    int i, j;
    int LINHAS = 3;
    int COLUNAS = 2;
    // Alocar o espaço para as linhas da matriz
    int **matriz = (int **) malloc (sizeof (int *) * LINHAS);
    for (i = 0; i < LINHAS; i++) {
    //Alocar o espaço das colunas para cada linha da matriz
    matriz [i] = (int *) malloc (sizeof (int) * COLUNAS);
    }
    for (i = 0; i < LINHAS; i++) {
    for (j = 0; j < COLUNAS; j++) {
    // Acesso aos elementos da matriz e inicialização dos valores
    matriz [i][j] = i * COLUNAS + j;
    }
    }
    for (i = 0; i < LINHAS; i++) {
    free (matriz [i]);
    }
    free (matriz);
}