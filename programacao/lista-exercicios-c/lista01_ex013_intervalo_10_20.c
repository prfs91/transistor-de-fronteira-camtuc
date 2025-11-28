#include <stdio.h>   // inclui funções de entrada/saída (printf, scanf)
#include <stdlib.h>  // inclui utilitários (boa prática incluir)

/*
  Arquivo: lista01_ex013_intervalo_10_20.c
  Objetivo: Ler 10 valores (um a um) e contar:
            - quantos estão no intervalo [10, 20] (inclusive)
            - quantos estão fora do intervalo
  Observações de boas práticas:
    - validar retorno de scanf
    - usar nomes de variáveis descritivos
    - usar while conforme pedido (repetição "enquanto")
*/

int main(void) {                            // função principal — ponto de entrada do programa

    const int TOTAL_LEITURAS = 10;          // número de valores a ler (constante para clareza)
    int contador = 0;                       // conta quantos valores já foram lidos
    double valor_atual;                     // armazena temporariamente cada valor lido (permitir decimais)
    int quantidade_no_intervalo = 0;        // contador de valores dentro do intervalo [10,20]
    int quantidade_fora_intervalo = 0;      // contador de valores fora do intervalo

    const double LIMITE_INFERIOR = 10.0;    // limite inferior do intervalo (inclusivo)
    const double LIMITE_SUPERIOR = 20.0;    // limite superior do intervalo (inclusivo)

    // cabeçalho informativo para o usuário
    printf("CONTADOR DE VALORES NO INTERVALO [10,20]\n");
    printf("---------------------------------------\n");
    printf("Voce devera digitar %d valores, um por vez.\n\n", TOTAL_LEITURAS);

    // laço 'enquanto' que repete TOTAL_LEITURAS vezes
    while (contador < TOTAL_LEITURAS) {

        // pede o valor atual (contador+1 para mostrar 1..10)
        printf("Digite o valor #%d: ", contador + 1);

        // lê o valor (double) e valida se a leitura foi bem-sucedida
        if (scanf("%lf", &valor_atual) != 1) {
            // se leitura inválida, informa e encerra com código de erro
            printf("Entrada invalida. Por favor execute o programa novamente e digite apenas numeros.\n");
            return 1;
        }

        // verifica se o valor está dentro do intervalo [10,20] (inclui 10 e 20)
        if (valor_atual >= LIMITE_INFERIOR && valor_atual <= LIMITE_SUPERIOR) {
            quantidade_no_intervalo = quantidade_no_intervalo + 1; // incrementa contador interno
        } else {
            quantidade_fora_intervalo = quantidade_fora_intervalo + 1; // incrementa contador fora
        }

        // incrementa o contador de leituras para avançar no laço
        contador = contador + 1;
    }

    // após o laço, exibe o resultado de forma clara e formatada
    printf("\nResultado final:\n");
    printf("Quantidade de valores dentro do intervalo [%.0lf, %.0lf]: %d\n",
           LIMITE_INFERIOR, LIMITE_SUPERIOR, quantidade_no_intervalo);
    printf("Quantidade de valores fora do intervalo: %d\n", quantidade_fora_intervalo);

    return 0; // indica ao sistema que o programa terminou com sucesso
}