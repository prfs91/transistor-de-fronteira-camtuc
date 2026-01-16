#include <stdio.h>

void conceito_por_media(double media, char *conceito)
{
    if (media >= 9) *conceito = 'A';
    else if (media >= 7) *conceito = 'B';
    else if (media >= 5) *conceito = 'C';
    else *conceito = 'D';
}

void main()
{
    double media;
    char conceito;

    printf("Digite a media (de 0.0 a 10.0): ");
    scanf("%lf", &media);

    conceito_por_media(media, &conceito);

    printf("Media: %.1lf -> Conceito: %c\n", media, conceito);
}
