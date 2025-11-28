#include <stdio.h>
#include <stdlib.h>

int main(void) {

    double base_maior;  
    double base_menor;
    double altura;
    double area_do_trapezio;

    printf("Digite o valor da base maior: ");
    scanf("%lf", &base_maior);

    printf("Digite o valor da base menor: ");
    scanf("%lf", &base_menor);

    printf("Digite o valor da altura: ");
    scanf("%lf", &altura);

    area_do_trapezio = ((base_maior + base_menor) * altura) / 2;

    printf("A area do trapezio eh: %.2lf", area_do_trapezio); 

    return 0;
}