#include <stdio.h>

int main()
{

    int total_dias;
    int anos;
    int meses;
    int dias;
    int resto_apos_anos;

    const int DIAS_POR_ANO = 365;
    const int DIAS_POR_MES = 30;

    printf("Digite o total de dias sem acidentes: ");
    scanf("%d", &total_dias);

    // Cálculo dos anos completos
    anos = (int)(total_dias / DIAS_POR_ANO);
    resto_apos_anos = total_dias % DIAS_POR_ANO;

    // Cálculo dos meses completos a partir do resto
    meses = (int)(resto_apos_anos / DIAS_POR_MES);

    // Dias restantes após retirar anos e meses completos
    dias = (int)(resto_apos_anos % DIAS_POR_MES);

    printf("Tempo sem acidentes: %d ano(s), %d mes(es) e %d dia(s)", anos, meses, dias);

}