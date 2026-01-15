#include <stdio.h>
#include <ctype.h>

double peso_ideal(double altura, char sexo)
{
    char s = (char) toupper((unsigned char) sexo);

    if (s == 'M')
    {
        double resultado = 72.7 * altura - 58;
        return resultado;
    }
    else if (s == 'F')
    {
        double resultado = 62.1 * altura - 44.7;
        return resultado;
    }
    return -1;
}

void main()
{
    double altura, peso;
    char sexo;

    printf("Digite altura e sexo (ex: 1.70 F): ");
    scanf("%lf %c", &altura, &sexo);

    peso = peso_ideal(altura, sexo);

    if (peso == - 1)
        printf("Parametro errado!");
    else
        printf("Altura: %.2lf m, Sexo: %c -> Peso ideal: %.2lf kg.", altura, (char) toupper((unsigned char) sexo), peso);

}
