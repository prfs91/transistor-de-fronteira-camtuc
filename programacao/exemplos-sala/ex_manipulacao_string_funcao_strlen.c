#include<stdio.h>
#include<string.h> // biblioteca necessária para manipulação de string, no exemplo, a função strlen()

char nomecli[25] = "Fulano da Silva";
char nomefunc[25] = "Fulano da Silva";

int main (void)
{

    // função strlen(<string>), retorna o valor do tamanho de uma string
    int tamanhostring = strlen(nomecli);

    printf("%d\n", tamanhostring);

}