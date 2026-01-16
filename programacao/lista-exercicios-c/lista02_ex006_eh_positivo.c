/* lista02_ex006_eh_positivo.c
   Exercício 6 - Lista 02 (Exercícios com Funções)

   Objetivo:
     Implementar a função bool eh_positivo(int x) que verifica se um inteiro é positivo.
     A função retorna `true` se o valor for maior que zero, e `false` caso contrário.
*/

#include <stdio.h>    // Necessário para printf e scanf (entrada/saída)
#include <stdlib.h>   // Utilitários (boa prática incluir; aqui não é estritamente necessário)
#include <stdbool.h>  // Define o tipo booleano `bool` e literais `true`/`false`

/* Protótipo da função - declara a assinatura antes do uso */
bool eh_positivo(int x);

/* === Definição da função eh_positivo === */
bool eh_positivo(int x) {
    /* Comentário: a função recebe um inteiro x e precisa dizer se é positivo.
       Critério de positividade adotado: "positivo" significa maior que zero.
       Valores zero e negativos são considerados não-positivos (a função retorna false). */

    /* if (x > 0) return true; */
    if (x > 0) {
        return true;   /* Se x for maior que 0, devolvemos true (é positivo) */
    }

    /* return false; */
    return false;      /* Caso contrário (x == 0 ou x < 0), devolvemos false (não é positivo) */
}

/* === Função main para demonstrar e testar eh_positivo === */
int main(void) {
    int valor;            // variável que guarda o número digitado pelo usuário
    bool resultado;       // variável que guarda o retorno de eh_positivo

    /* Mensagem inicial para o usuário */
    printf("VERIFICADOR DE POSITIVO/NEGATIVO\n");
    printf("--------------------------------\n");
    printf("Digite um numero inteiro (ou um valor nao inteiro para encerrar):\n");

    /* Leitura em loop: permite vários testes até o usuário interromper (entrada inválida / EOF) */
    while (1) {
        printf("Numero: ");

        /* scanf tenta ler um inteiro e retorna quantos itens foram lidos com sucesso */
        if (scanf("%d", &valor) != 1) {
            /* Se não leu um inteiro (por exemplo, o usuário digitou letra ou Ctrl+D),
               informamos e encerramos educadamente. */
            printf("\nEntrada encerrada ou invalida. Saindo.\n");
            break;
        }

        /* Chamamos a função que verifica positividade */
        resultado = eh_positivo(valor);

        /* Interpretamos o retorno e mostramos mensagem amigável */
        if (resultado) {
            /* resultado == true: valor maior que zero */
            printf("%d é POSITIVO (eh_positivo -> true).\n", valor);
        } else {
            /* resultado == false: valor é zero ou negativo */
            printf("%d NAO eh positivo (eh_positivo -> false).\n", valor);
        }

        /* pequena separação visual antes da próxima leitura */
        printf("\n");
    }

    return 0; /* terminar o programa com código 0 (sucesso) */
}
