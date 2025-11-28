#include<stdio.h>
#include<string.h> // biblioteca necessária para manipulação de string, no exemplo, a função strcmp()

char nomecli[25] = "Fulano da Silva";
char nomefunc[25] = "Fulano da Silva";

int main (void)
{

    // função strcmp(<string1>, <string2>), compara duas strings
    if (strcmp(nomecli, nomefunc) == 0)
    {
        printf("Os conteudos sao iguais!\n");
    }
    else
    {
        printf("Os conteudos sao diferentes!\n");
    }

}