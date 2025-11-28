#include <stdio.h>
#include <stdlib.h>

int main(void) {

    double peso_atual;
    double peso_apos_engordar;
    double peso_apos_emagrecer;

    const double TAXA_ENGORDAR = 0.15;
    const double TAXA_EMAGRECER = 0.20;

    printf("Digite o seu peso atual em kg (por exemplo 70.5): ");
    scanf("%lf", &peso_atual);

    peso_apos_engordar = peso_atual * (1 + TAXA_ENGORDAR);
    peso_apos_emagrecer = peso_atual * (1 - TAXA_EMAGRECER);

    printf("\nPeso atual           : %.2lf kg\n", peso_atual);
    printf("Se engordar 15%%     : %.2lf kg\n", peso_apos_engordar);
    printf("Se emagrecer 20%%    : %.2lf kg\n", peso_apos_emagrecer);

    return 0;
}