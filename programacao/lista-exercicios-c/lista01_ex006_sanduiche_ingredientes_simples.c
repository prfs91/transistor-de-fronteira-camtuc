#include <stdio.h>

int main()
{

    int quantidade_sanduiches;
    double quilos_queijo;
    double quilos_presunto;
    double quilos_carne;

    printf("Informe a quantidade de sanduiches a produzir: ");
    scanf("%d", &quantidade_sanduiches);

    /* Converte para quilos (double para manter casas decimais) */
    quilos_queijo = (double)quantidade_sanduiches * 2 * 5 / 100;
    quilos_presunto = (double)quantidade_sanduiches * 5 / 100;
    quilos_carne = (double)quantidade_sanduiches / 10;

    printf("\nPara produzir %d sanduiche(s) voce precisa de:\n", quantidade_sanduiches);
    printf("- Queijo  : %.3lf kg\n", quilos_queijo);
    printf("- Presunto: %.3lf kg\n", quilos_presunto);
    printf("- Carne   : %.3lf kg\n", quilos_carne);

}