#include <stdio.h>   // biblioteca padrão para entrada/saida: printf e scanf
#include <stdlib.h>  // biblioteca de utilitarios: usada por boas praticas (ex: exit), nao obrigatoria aqui

/*
  Arquivo: lista01_ex005_salario_aumento_imposto.c
  Objetivo: ler o salario de um funcionario, aplicar aumento de 15%,
            depois descontar 8% de imposto sobre o salario ja aumentado,
            e imprimir salario inicial, salario apos aumento e salario final.
*/

int main(void) {                                   // inicio da funcao principal
    /* Declaracao de variaveis com nomes autoexplicativos */
    double salario_inicial;                        // salario original informado pelo usuario (reais)
    double salario_com_aumento;                     // salario apos aplicar aumento de 15%
    double salario_final;                           // salario apos descontar 8% de imposto
    const double TAXA_AUMENTO = 0.15;               // 15% de aumento (constante)
    const double TAXA_IMPOSTO  = 0.08;              // 8% de imposto (constante)

    /* Mensagem inicial para o usuario */
    printf("CALCULO DE SALARIO COM AUMENTO E IMPOSTO\n");
    printf("----------------------------------------\n");

    /* Leitura do salario inicial com validacao basica */
    printf("Digite o salario atual do funcionario (R$): ");
    if (scanf("%lf", &salario_inicial) != 1) {     // scanf retorna quantos itens leu com sucesso
        printf("Entrada invalida. Por favor digite um numero valido.\n");
        return 1;                                  // encerra com codigo de erro
    }

    /* Valida que o salario nao seja negativo */
    if (salario_inicial < 0.0) {
        printf("Salario invalido: nao pode ser negativo.\n");
        return 1;
    }

    /* Calcula o salario apos aumento de 15%:
       salario_com_aumento = salario_inicial + (salario_inicial * 0.15)
       ou simplificado: salario_inicial * 1.15
    */
    salario_com_aumento = salario_inicial * (1.0 + TAXA_AUMENTO);

    /* Aplica o desconto de 8% sobre o valor ja aumentado:
       salario_final = salario_com_aumento - (salario_com_aumento * 0.08)
       ou simplificado: salario_com_aumento * (1 - 0.08)
    */
    salario_final = salario_com_aumento * (1.0 - TAXA_IMPOSTO);

    /* Exibe os resultados de forma amigavel e formatada */
    printf("\nResultados:\n");
    printf("Salario inicial       : R$ %.2lf\n", salario_inicial);
    printf("Salario com aumento   : R$ %.2lf  (aumento de %.0f%%)\n", salario_com_aumento, TAXA_AUMENTO * 100);
    printf("Salario final (apos imposto de %.0f%%): R$ %.2lf\n", TAXA_IMPOSTO * 100, salario_final);

    return 0;   // encerra o programa com codigo 0 indicando sucesso
}
