#include <stdio.h>   // Biblioteca padrão para entrada/saída: printf, scanf
#include <stdlib.h>  // Biblioteca de utilitários (boa prática incluir)

/*
  Arquivo: lista01_ex011_conta_negativos.c
  Objetivo: Ler 8 valores (um a um) e contar quantos são negativos.
  Requisito: usar repetição do tipo "enquanto" (while).
*/

int main(void) {                       // Função principal — início do programa

    const int TOTAL_VALORES = 8;       // Quantidade de leituras exigidas pelo enunciado
    int contador = 0;                  // Contador de quantos valores já foram lidos
    int quantidade_negativos = 0;      // Acumulador: quantos valores lidos são negativos
    double valor;                      // Variável para armazenar cada valor lido (pode ter casas decimais)

    // Cabeçalho para o usuário
    printf("CONTADOR DE VALORES NEGATIVOS\n");
    printf("-----------------------------\n");
    printf("Voce devera digitar %d valores, um por vez.\n\n", TOTAL_VALORES);

    // Laço 'enquanto' que repete TOTAL_VALORES vezes
    while (contador < TOTAL_VALORES) {

        // Solicita o valor atual
        printf("Digite o valor #%d: ", contador + 1);

        // Lê um número de ponto flutuante (double) e valida a leitura
        if (scanf("%lf", &valor) != 1) {
            // Se scanf não leu corretamente, exibimos uma mensagem e encerramos com erro
            printf("Entrada invalida. Por favor execute o programa novamente e digite numeros.\n");
            return 1; // Código de erro
        }

        // Verifica se o valor lido é negativo; se for, incrementa o contador de negativos
        if (valor < 0.0) {
            quantidade_negativos = quantidade_negativos + 1;
        }

        // Atualiza o número de leituras realizadas
        contador = contador + 1;
    }

    // Após o laço, mostramos o resultado final ao usuário
    printf("\nForam lidos %d valor(es) negativos entre os %d informados.\n",
           quantidade_negativos, TOTAL_VALORES);

    return 0; // Indica término com sucesso
}