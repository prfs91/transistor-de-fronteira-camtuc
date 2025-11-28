#include <stdio.h>      // biblioteca padrão: printf (imprimir) e scanf (ler)
#include <stdlib.h>     // utilitários gerais (boa prática incluir)
#include <limits.h>     // define limites de tipos inteiros (ULLONG_MAX)

 /*
  Arquivo: lista01_ex018_fatorial.c
  Objetivo:
    Ler um número inteiro e positivo N e calcular N! (fatorial de N).
    O cálculo usa um laço 'while' e faz checagem preventiva de overflow
    para evitar multiplicações que extrapolem a capacidade de
    'unsigned long long' (tipo inteiro sem sinal de 64 bits).
 */

int main(void) {
    /* declaração das variáveis usadas */
    int N;                                 // número lido (o fatorial que queremos calcular)
    unsigned long long fatorial = 1ULL;    // acumulador do fatorial (começa com 1)
    int contador = 1;                      // contador para o laço (vai de 1 a N)
    int validade_scanf;                    // armazena o retorno de scanf para validação
    int overflow_ocorreu = 0;              // flag: 0 = sem overflow, 1 = overflow detectado

    /* cabeçalho informativo */
    printf("CALCULO DO FATORIAL (N!)\n");
    printf("-------------------------\n");
    printf("Digite um numero inteiro e nao-negativo (por exemplo 5): ");

    /* leitura segura do inteiro N */
    validade_scanf = scanf("%d", &N);
    if (validade_scanf != 1) {             // verifica se scanf leu exatamente um inteiro
        printf("Entrada invalida. Por favor execute novamente e digite um numero inteiro.\n");
        return 1;                          // termina com código de erro
    }

    /* valida se N é não-negativo (exigido pelo enunciado) */
    if (N < 0) {
        printf("Valor invalido: N deve ser um numero inteiro nao-negativo.\n");
        return 1;
    }

    /* caso particular: 0! é definido como 1, tratamos naturalmente no laço (contador começa em 1) */

    /* laço while para calcular o fatorial de forma iterativa */
    while (contador <= N) {

        /* checagem preventiva de overflow:
           se fatorial > ULLONG_MAX / contador, então fatorial * contador excederia ULLONG_MAX
           e causaria overflow. */
        if (fatorial > ULLONG_MAX / (unsigned long long)contador) {
            overflow_ocorreu = 1;          // marcamos que houve overflow
            break;                         // interrompe o laço sem fazer a multiplicação perigosa
        }

        /* multiplicação segura — acumula o próximo fator */
        fatorial = fatorial * (unsigned long long)contador;

        /* incrementa o contador para o próximo passo (1, 2, 3, ..., N) */
        contador = contador + 1;
    }

    /* exibe o resultado ou informa que o valor é muito grande para caber em unsigned long long */
    if (overflow_ocorreu) {
        printf("\nNao foi possivel calcular %d! porque o resultado excede a capacidade de\n", N);
        printf("um inteiro sem sinal de 64 bits (unsigned long long). Para valores grandes, o\n");
        printf("fatorial cresce muito rapido e precisa de aritmética de precisao arbitraria.\n");
    } else {
        printf("\nResultado:\n");
        printf("%d! = %llu\n", N, fatorial);  // %llu: formato para unsigned long long
    }

    return 0; // programa terminou com sucesso
}