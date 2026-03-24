#include <stdio.h>
#include <math.h>

int eh_primo(int x)
{
    if (x < 2) return 0;

    if (x == 2) return 1;

    if (x % 2 == 0) return 0;

    int limite = (int) sqrt((double) x);

    for (int d = 3; d <= limite; d += 2)
    {
        if (x % d == 0) return 0;
    }

    return 1;
}

int primeiros_primos_acima_de(int base, int qtd, int saida[])
{
    int cont_primos = 0;
    int num = base + 1;

    while (cont_primos < qtd)
    {
        if (eh_primo(num))
        {
            saida[cont_primos] = num;
            cont_primos += 1;
        }
        num += 1;
    }

    return cont_primos;
}

int main()
{
    const int MAX_PRIMOS = 10;
    const int BASE = 100;
    int X[MAX_PRIMOS];

    int qtd_primos = primeiros_primos_acima_de(BASE, MAX_PRIMOS, X);

    printf("Os %d primeiros primos acima de %d sao:\n", MAX_PRIMOS, BASE);
    for (int i = 0; i < qtd_primos; i++)
    {
        printf("%d ", X[i]);
    }
}
