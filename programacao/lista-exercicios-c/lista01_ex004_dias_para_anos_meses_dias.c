#include <stdio.h>   // Necessário para printf e scanf
#include <stdlib.h>  // Opcional aqui, mas boa prática incluir (p.ex. exit)

int main(void) {
    /* Descrição:
       Converte um total de dias (inteiro) em anos, meses e dias.
       Assunção: cada mês tem sempre 30 dias; o ano considerado tem 365 dias.
    */

    long long total_dias;       // número total de dias fornecido pela fábrica (pode ser grande)
    int anos;                   // número de anos completos
    int meses;                  // número de meses completos após remover os anos
    int dias;                   // dias restantes após remover anos e meses

    const int DIAS_POR_ANO = 365; // constante para claridade
    const int DIAS_POR_MES = 30;  // conforme o enunciado

    // Cabeçalho informativo para o usuário
    printf("CONVERSOR DE DIAS PARA ANOS, MESES E DIAS\n");
    printf("-----------------------------------------\n");

    // Solicita o total de dias
    printf("Digite o total de dias sem acidentes (numero inteiro, sem casas decimais): ");
    if (scanf("%lld", &total_dias) != 1) { // leitura segura: verifica sucesso
        printf("Entrada invalida. Por favor digite um numero inteiro.\n");
        return 1; // encerra com código de erro
    }

    // Validação: não aceitamos valores negativos para dias
    if (total_dias < 0) {
        printf("Valor invalido: o numero de dias nao pode ser negativo.\n");
        return 1;
    }

    // Cálculo dos anos completos
    anos = (int)(total_dias / DIAS_POR_ANO);

    // Resto de dias após retirar anos completos
    long long resto_apos_anos = total_dias % DIAS_POR_ANO;

    // Cálculo dos meses completos a partir do resto
    meses = (int)(resto_apos_anos / DIAS_POR_MES);

    // Dias restantes após retirar anos e meses completos
    dias = (int)(resto_apos_anos % DIAS_POR_MES);

    // Exibe o resultado de forma amigável
    printf("\nTempo sem acidentes: %lld dias equivalem a:\n", total_dias);
    printf("%d ano(s), %d mes(es) e %d dia(s)\n", anos, meses, dias);

    return 0; // sucesso
}