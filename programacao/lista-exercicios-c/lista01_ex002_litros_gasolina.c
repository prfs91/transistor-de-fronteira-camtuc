#include <stdio.h>   // biblioteca para entrada e saída (printf, scanf)
#include <stdlib.h>  // biblioteca para funções utilitárias (por exemplo exit)

/*
  Programa: lista01_ex002_litros_gasolina.c
  Objetivo: ler o preco do litro da gasolina e o valor pago pelo motorista
            e calcular quantos litros foram abastecidos.
  Formula: litros = valor_pago / preco_litro
  Observações de boas práticas:
   - nomes claros para variáveis
   - validação de entrada (preco do litro deve ser maior que zero)
   - tratamento de leitura inválida (scanf)
*/

int main(void) {                       // função principal: ponto de entrada do programa

    /* Declaração de variáveis com nomes autoexplicativos */
    double preco_por_litro;            // preço de 1 litro de gasolina (em reais)
    double valor_pago;                 // quanto o motorista entregou (em reais)
    double litros_abastecidos;         // quantos litros foram comprados com o valor pago

    /* Cabeçalho informativo para o usuário */
    printf("CALCULO DE LITROS DE GASOLINA\n");
    printf("--------------------------------\n");

    /* Solicita e lê o preço por litro */
    printf("Informe o preco do litro da gasolina (R$): ");
    if (scanf("%lf", &preco_por_litro) != 1) {   // verifica se a leitura foi bem-sucedida
        printf("Entrada invalida para o preco. Encerrando.\n");
        return 1;                                // encerra com código de erro
    }

    /* Valida o preco lido: nao pode ser zero ou negativo */
    if (preco_por_litro <= 0.0) {
        printf("Preco invalido. O preco do litro deve ser maior que zero.\n");
        return 1;
    }

    /* Solicita e lê o valor que o motorista deseja pagar */
    printf("Informe o valor que sera pago (R$): ");
    if (scanf("%lf", &valor_pago) != 1) {        // verifica leitura
        printf("Entrada invalida para o valor pago. Encerrando.\n");
        return 1;
    }

    /* Calcula quantos litros cabem no valor informado */
    litros_abastecidos = valor_pago / preco_por_litro;

    /* Mostra o resultado ao usuario com formatacao amigavel */
    printf("\nCom R$ %.2lf, ao preco de R$ %.2lf por litro,\n", valor_pago, preco_por_litro);
    printf("voce abastece: %.3lf litros\n", litros_abastecidos);
    // usei 3 casas decimais para litros por ser um valor que pode precisar de maior precisao

    return 0;   // sucesso
}