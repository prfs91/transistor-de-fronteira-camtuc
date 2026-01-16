
#include <stdio.h>
#include <stdbool.h>

bool eh_positivo(int x)
{
    if (x >= 0) return true;
    return false;
}

void main()
{
    int valor;
    bool resultado;

    printf("Digite um numero inteiro: ");
    scanf("%d", &valor);

    resultado = eh_positivo(valor);

    if (resultado)
        printf("%d EH positivo.\n", valor);
    else
        printf("%d EH negativo.\n", valor);
}
