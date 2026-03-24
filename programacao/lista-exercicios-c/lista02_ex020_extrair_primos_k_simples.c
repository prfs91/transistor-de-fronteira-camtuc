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

int extrair_primos(const int entrada[], int saida[], int n)
{
    int cont_primos = 0;
    for (int i = 0; i < n; i++)
    {
        if (eh_primo(entrada[i]))
        {
            saida[cont_primos] = entrada[i];
            cont_primos = cont_primos + 1;
        }
    }

    return cont_primos;
}

int main()
{
    const int TAM_MAX = 15;
    int K[TAM_MAX];
    int P[TAM_MAX];
    int qtd_primos;

    printf("Digite %d numeros inteiros positivos:\n", TAM_MAX);

    for (int i = 0; i < TAM_MAX; i++)
    {
        printf("K[%d]: ", i + 1);
        scanf("%d", &K[i]);
    }

    qtd_primos = extrair_primos(K, P, TAM_MAX);

    if (qtd_primos == 0)
    {
        printf("\nNenhum primo encontrado em K.\n");
    }
    else
    {
        printf("\nEncontramos %d primo(s) em K.\n\nVetor P gerado:\n", qtd_primos);
        for (int i = 0; i < qtd_primos; i++)
        {
            printf("P[%d]: %d ", i + 1, P[i]);
        }
    }
}
