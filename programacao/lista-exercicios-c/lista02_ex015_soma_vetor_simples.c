#include <stdio.h>

double soma_vetor(const double v[], int n)
{
    double soma = 0;

    for (int i = 0; i < n; i++)
    {
        soma = soma + v[i];
    }

    return soma;
}

int main()
{
    const int TAM = 5;
    double X[TAM];

    for (int i = 0; i < TAM; i++)
    {
        printf("Valor %d: ", i+1);
        scanf("%lf", &X[i]);
    }

    double soma = soma_vetor(X, TAM);

    printf("Soma dos elementos: %.2lf\n", soma);
}
