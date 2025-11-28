#include<stdio.h>
#include<math.h> // necessária para usar a função fmod()

int main(void)
{

    // para variáveis inteiras
    int resto = 10 % 3;

    printf("%d\n", resto);

    // para trabalhar com float ou double
    double valor = 152.4;
    int aux = (int)(valor/3);
    double restod = valor - ((double) aux * 3);
    printf("%lf\n", restod);
    
    // usando a função fmod() que devolve o resto da divisão
    double restof = fmod(152.4, 3);
    printf("%lf\n", restof);

}