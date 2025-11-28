#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int quantidade_sanduiches;
    double quilos_queijo;
    double quilos_presunto;
    double quilos_carne;

    printf("Informe a quantidade de sanduiches a produzir: ");
    scanf("%d", &quantidade_sanduiches);

    /* Converte para quilos (double para manter casas decimais) */
    quilos_queijo = (double)quantidade_sanduiches * 2 * 50 / 1000;
    quilos_presunto = (double)quantidade_sanduiches * 1 * 50 / 1000;
    quilos_carne = (double)quantidade_sanduiches * 1 * 100 / 1000;

    printf("\nPara produzir %d sanduiche(s) voce precisa de:\n", quantidade_sanduiches);
    printf("- Queijo  : %.3f kg\n", quilos_queijo);
    printf("- Presunto: %.3f kg\n", quilos_presunto);
    printf("- Carne   : %.3f kg\n", quilos_carne);

    return 0;
}