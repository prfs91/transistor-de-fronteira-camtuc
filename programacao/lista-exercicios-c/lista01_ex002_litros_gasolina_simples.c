#include <stdio.h>
#include <stdlib.h>

int main(void) {

    double preco_por_litro;
    double valor_pago;
    double litros_abastecidos;

    printf("Informe o preco do litro da gasolina (R$): ");
    scanf("%lf", &preco_por_litro);

    printf("Informe o valor que sera pago (R$): ");
    scanf("%lf", &valor_pago);

    litros_abastecidos = valor_pago / preco_por_litro;

    printf("Com R$ %.2lf, ao preco de R$ %.2lf por litro, voce abastece: %.3lf litros", valor_pago, preco_por_litro, litros_abastecidos);

    return 0;
}