#include <stdio.h>

int indice_maior(const double v[], int n)
{
    int idx_maior = 0;
    double maior = v[0];

    for (int i = 1; i < n; i++)
    {
        if (v[i] > maior)
        {
            maior = v[i];
            idx_maior = i;
        }
    }

    return idx_maior;
}

void divide_por_maior(double v[], int n)
{
    int idx = indice_maior(v, n);

    double maior = v[idx];

    if (maior == 0)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        v[i] /= maior;
    }
}

int main()
{
    const int N = 10;
    double B[N];

    printf("Voce deve digitar %d valores reais.\n", N);

    for (int i = 0; i < N; i = i + 1)
    {
        printf("B[%d] = ", i);
        scanf("%lf", &B[i]);
    }

    printf("\nVetor antes da divisao:\n");
    for (int i = 0; i < N; i = i + 1)
    {
        printf("%10.6lf ", B[i]);
        if ((i + 1) % 5 == 0) printf("\n");
    }

    divide_por_maior(B, N);

    printf("\nVetor depois da divisao:\n");
    for (int i = 0; i < N; i = i + 1)
    {
        printf("%10.6lf ", B[i]);
        if ((i + 1) % 5 == 0) printf("\n");
    }

}
