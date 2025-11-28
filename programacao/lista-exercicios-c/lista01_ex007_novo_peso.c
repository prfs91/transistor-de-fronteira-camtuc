#include <stdio.h>    // inclui funções de entrada/saída: printf, scanf
#include <stdlib.h>   // inclui utilitários; boa prática (ex: exit), não estritamente necessário aqui

/*
  Arquivo: lista01_ex007_novo_peso.c
  Objetivo: ler o peso de uma pessoa e calcular:
           a) novo peso se engordar 15%
           b) novo peso se emagrecer 20%
  Boas práticas aplicadas:
   - nomes de variáveis claros
   - validação do input (scanf)
   - uso de constantes para taxas
   - saída formatada
*/

int main(void) {                       // função principal: ponto de entrada do programa
    /* Declaração de variáveis */
    double peso_atual;                 // peso original informado (em kg)
    double peso_apos_engordar;         // peso se engordar 15%
    double peso_apos_emagrecer;        // peso se emagrecer 20%

    /* Constantes: percentuais como frações decimais */
    const double TAXA_ENGORDAR = 0.15; // 15% de aumento
    const double TAXA_EMAGRECER = 0.20; // 20% de redução

    /* Mensagem inicial para o usuário */
    printf("CALCULADORA DE NOVO PESO (ENGORDAR / EMAGRECER)\n");
    printf("------------------------------------------------\n");

    /* Solicita e lê o peso atual */
    printf("Digite o seu peso atual em kg (por exemplo 70.5): ");
    if (scanf("%lf", &peso_atual) != 1) {   // verifica se a leitura foi bem-sucedida
        printf("Entrada invalida. Por favor digite um numero (ex: 70.5).\n");
        return 1;                            // encerra com código de erro
    }

    /* Valida se o peso é um valor plausível (não negativo e não zero) */
    if (peso_atual <= 0.0) {
        printf("Peso invalido. O peso deve ser maior que zero.\n");
        return 1;
    }

    /* Calcula novo peso após engordar 15%:
       peso_apos_engordar = peso_atual * (1 + TAXA_ENGORDAR)
    */
    peso_apos_engordar = peso_atual * (1.0 + TAXA_ENGORDAR);

    /* Calcula novo peso após emagrecer 20%:
       peso_apos_emagrecer = peso_atual * (1 - TAXA_EMAGRECER)
    */
    peso_apos_emagrecer = peso_atual * (1.0 - TAXA_EMAGRECER);

    /* Mostra os resultados com 2 casas decimais para facilitar leitura */
    printf("\nPeso atual           : %.2lf kg\n", peso_atual);
    printf("Se engordar 15%%     : %.2lf kg\n", peso_apos_engordar);
    printf("Se emagrecer 20%%    : %.2lf kg\n", peso_apos_emagrecer);

    return 0; // encerra o programa com sucesso
}