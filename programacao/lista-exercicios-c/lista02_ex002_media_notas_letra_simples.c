#include <stdio.h>
#include <ctype.h>   // Declara toupper para normalizar o caractere 'tipo'

double media_aritmetica_ou_ponderada(double n1, double n2, double n3, char letra)
{
    
    /* Para tratar 'a' e 'A' igualmente */
    char tipo = (char) toupper((unsigned char) letra);

    if (tipo == 'A')
    {
        double soma = n1 + n2 + n3;
        double media = soma / 3;

        return media;
    }

    if (tipo == 'P')
    {
        const double PESO1 = 5;
        const double PESO2 = 3;
        const double PESO3 = 2;
        const double SOMA_PESOS = PESO1 + PESO2 + PESO3;
        
        double soma_ponderada = n1 * PESO1 + n2 * PESO2 + n3 * PESO3;
        double media_ponderada = soma_ponderada / SOMA_PESOS;

        return media_ponderada;
    }

    return (-1);
}

void main()
{
    double n1, n2, n3;
    char letra;
    double resultado;

    printf("Digite a primeira nota: ");
    scanf("%lf", &n1);
    printf("Digite a segunda nota: ");
    scanf("%lf", &n2);
    printf("Digite a terceira nota: ");
    scanf("%lf", &n3);

    printf("Digite o tipo de media ('a' para aritmetica, 'p' para ponderada): ");
    scanf(" %c", &letra);

    resultado = media_aritmetica_ou_ponderada(n1, n2, n3, letra);

    printf("Media calculada: %.2lf\n", resultado);

}

