#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    double salario_inicial;
    double salario_com_aumento;
    double salario_final;
    const double TAXA_AUMENTO = 0.15;
    const double TAXA_IMPOSTO  = 0.08;

    printf("Digite o salario atual do funcionario (R$): ");
    scanf("%lf", &salario_inicial);

    salario_com_aumento = salario_inicial * (1 + TAXA_AUMENTO);
    salario_final = salario_com_aumento * (1 - TAXA_IMPOSTO);

    printf("Salario inicial       : R$ %.2lf\n", salario_inicial);
    printf("Salario com aumento   : R$ %.2lf  (aumento de %.0f%%)\n", salario_com_aumento, TAXA_AUMENTO * 100);
    printf("Salario final (apos imposto de %.0f%%): R$ %.2lf\n", TAXA_IMPOSTO * 100, salario_final);

    return 0;
}
