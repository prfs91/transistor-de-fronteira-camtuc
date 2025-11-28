#include <stdio.h>   // biblioteca padrão para entrada e saida (printf, scanf)
#include <stdlib.h>  // biblioteca padrão de utilitarios (boa pratica incluir)

/*
  Arquivo: lista01_ex006_sanduiche_ingredientes.c
  Objetivo: calcular a quantidade em quilos de queijo, presunto e carne
            necessaria para produzir N sanduiches.
  Recheio por sanduiche:
    - 2 fatias de queijo, cada fatia = 50 g  -> 2 * 50 = 100 g queijo por sanduiche
    - 1 fatia de presunto, cada fatia = 50 g -> 1 * 50 = 50 g presunto por sanduiche
    - 1 rodela de hamburguer = 100 g         -> 100 g carne por sanduiche
*/

int main(void) {
    /* Variaveis:
       - quantidade_sanduiches: numero de sanduiches que o dono quer fazer (inteiro)
       - gramas_queijo_total, gramas_presunto_total, gramas_carne_total: totais em gramas (inteiros)
       - quilos_queijo, quilos_presunto, quilos_carne: conversao para quilos (double)
    */

    int quantidade_sanduiches;            // quantos sanduiches produzir
    long long gramas_queijo_total;        // total de queijo em gramas
    long long gramas_presunto_total;      // total de presunto em gramas
    long long gramas_carne_total;         // total de carne em gramas

    double quilos_queijo;                 // total de queijo em quilos (para mostrar)
    double quilos_presunto;               // total de presunto em quilos
    double quilos_carne;                  // total de carne em quilos

    /* Constantes que descrevem o recheio */
    const int FATIAS_QUEIJO_POR_SANDUICHE = 2; // 2 fatias de queijo por sanduiche
    const int FATIAS_PRESUNTO_POR_SANDUICHE = 1; // 1 fatia de presunto por sanduiche
    const int GRAMAS_POR_FATIA_QUEIJO = 50;  // cada fatia de queijo pesa 50 g
    const int GRAMAS_POR_FATIA_PRESUNTO = 50; // cada fatia de presunto pesa 50 g
    const int GRAMAS_POR_RODELA_HAMBURGUER = 100; // cada rodela de hamburguer pesa 100 g
    const int GRAMAS_POR_KILO = 1000; // 1000 gramas = 1 quilo

    /* Cabecalho para o usuario */
    printf("CALCULO DE INGREDIENTES PARA SANDUICHE\n");
    printf("-------------------------------------\n");

    /* Pergunta ao dono quantos sanduiches quer produzir */
    printf("Informe a quantidade de sanduiches a produzir (numero inteiro): ");
    if (scanf("%d", &quantidade_sanduiches) != 1) { // valida se leitura foi um inteiro
        printf("Entrada invalida. Por favor digite um numero inteiro.\n");
        return 1; // encerra com codigo de erro
    }

    /* Validacao: nao permitimos quantidade negativa */
    if (quantidade_sanduiches < 0) {
        printf("Quantidade invalida: nao pode ser negativa.\n");
        return 1;
    }

    /* Calcula as quantidades em gramas */
    gramas_queijo_total = (long long)quantidade_sanduiches
                         * FATIAS_QUEIJO_POR_SANDUICHE
                         * GRAMAS_POR_FATIA_QUEIJO;
    gramas_presunto_total = (long long)quantidade_sanduiches
                           * FATIAS_PRESUNTO_POR_SANDUICHE
                           * GRAMAS_POR_FATIA_PRESUNTO;
    gramas_carne_total = (long long)quantidade_sanduiches
                        * GRAMAS_POR_RODELA_HAMBURGUER;

    /* Converte para quilos (double para manter casas decimais) */
    quilos_queijo = (double)gramas_queijo_total / GRAMAS_POR_KILO;
    quilos_presunto = (double)gramas_presunto_total / GRAMAS_POR_KILO;
    quilos_carne = (double)gramas_carne_total / GRAMAS_POR_KILO;

    /* Mostra o resultado de forma clara */
    printf("\nPara produzir %d sanduiche(s) voce precisa de:\n", quantidade_sanduiches);
    printf("- Queijo  : %lld g  -> %.3f kg\n", gramas_queijo_total, quilos_queijo);
    printf("- Presunto: %lld g  -> %.3f kg\n", gramas_presunto_total, quilos_presunto);
    printf("- Carne   : %lld g  -> %.3f kg\n", gramas_carne_total, quilos_carne);

    return 0; // finaliza com sucesso
}