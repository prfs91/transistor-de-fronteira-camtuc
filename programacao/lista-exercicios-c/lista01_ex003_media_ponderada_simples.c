#include <stdio.h>

int main()
{

    double nota1;
    double nota2;
    double nota3;
    const int peso1 = 2;
    const int peso2 = 3;
    const int peso3 = 5;
    const int soma_pesos = peso1 + peso2 + peso3;
    double soma_ponderada;
    double media_ponderada;

    printf("Digite a primeira nota: ");
    scanf("%lf", &nota1);
    printf("Digite a segunda nota: ");
    scanf("%lf", &nota2);
    printf("Digite a terceira nota: ");
    scanf("%lf", &nota3);

    soma_ponderada = (nota1 * peso1) + (nota2 * peso2) + (nota3 * peso3);
    media_ponderada = soma_ponderada / soma_pesos;

    printf("Media ponderada = %.2lf\n", media_ponderada);

}