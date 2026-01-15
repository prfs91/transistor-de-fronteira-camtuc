#include <stdio.h>
#include <stdbool.h>

bool eh_par(int x)
{
    if (x % 2 == 0) return true;
    return false;
}

void main()
{
    int valor;
    bool resultado;

    printf("Digite um numero inteiro: ");
    scanf("%d", &valor);

    resultado = eh_par(valor);   

    if (resultado)
        printf("%d eh PAR.\n", valor);
    else
        printf("%d eh IMPAR.\n", valor);
}
