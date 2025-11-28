#include <stdio.h>
#include <string.h> // biblioteca necessária para manipulação de string, no exemplo, a função strcpy()

char origem[25] = "Conteudo da String.";
char destino[25];

int main (void)
{

    // função strcpy(<string_destino>, <string_origem>), copia o valor de uma string para outra
    strcpy(destino, origem);

    printf("%s\n", destino);

}