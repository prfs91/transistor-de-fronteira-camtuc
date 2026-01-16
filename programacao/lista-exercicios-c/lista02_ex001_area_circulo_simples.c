#include <stdio.h>
#include <math.h>

const double PI = 3.14159265358979323846;

double area_circulo(double raio)
{
    double area;

    area = PI * pow(raio,2);

    return area;
}

void main()
{
    double raio;
    double area;

    printf("Digite o raio do circulo (numero nao negativo): ");
    scanf("%lf", &raio);
    area = area_circulo(raio);

    printf("A area do circulo de raio %.2lf e: %.2lf\n", raio, area);
}