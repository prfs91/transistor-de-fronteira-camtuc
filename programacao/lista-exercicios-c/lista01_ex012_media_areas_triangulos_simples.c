#include <stdio.h>

int main()
{
    const int TOTAL_TRIANGULOS = 2;
    int cont = 0;
    double base;
    double altura;
    double area;
    double soma_areas = 0;
    double media_areas = 0; 

    while (cont < TOTAL_TRIANGULOS) {

        printf("\nTriangulo #%d:\n", cont + 1);

        printf("  Digite a base (ex.: 3.5): ");
        scanf("%lf", &base);

        printf("  Digite a altura (ex.: 4.2): ");
        scanf("%lf", &altura);

        area = (base * altura) / 2;

        printf("  Area do triangulo #%d = %.4lf\n", cont + 1, area);

        soma_areas = soma_areas + area;

        cont = cont + 1;
    }

    media_areas = soma_areas / TOTAL_TRIANGULOS;

    printf("\nSoma das areas = %.4lf\n", soma_areas);
    printf("Media das areas = %.4lf\n", media_areas);

}