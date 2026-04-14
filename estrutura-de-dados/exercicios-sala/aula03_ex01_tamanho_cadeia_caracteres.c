#include <stdio.h>
#include<malloc.h>

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
    char *s1 = (char *) malloc (51 * sizeof(char));
    char *s2 = (char *) malloc (51 * sizeof(char));

    scanf("%s", s1);
    scanf("%s", s2);
    scanf("%s", concatenar(s1,s2));
}