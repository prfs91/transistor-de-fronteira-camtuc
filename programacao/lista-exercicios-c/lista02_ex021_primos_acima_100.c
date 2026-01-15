/* lista02_ex021_primos_acima_100.c
   Exercício 21 - Lista 02 (Exercícios de Vetores com Funções)

   Objetivo:
     Implementar:
       int primeiros_primos_acima_de(int limite, int quantidade, int out[]);
     que preenche out[0..quantidade-1] com os primeiros 'quantidade' primos
     estritamente maiores que 'limite' e retorna a quantidade efetivamente escrita.
*/

#include <stdio.h>   /* traz printf e scanf — usadas para entrada/saída no programa */
#include <stdlib.h>  /* traz EXIT_SUCCESS, EXIT_FAILURE e utilitários gerais */
#include <math.h>    /* traz sqrt — usado para limitar testes de primalidade */

/* -------------------------
   Protótipos (declarações)
   -------------------------
   Declaramos as funções aqui para que o compilador saiba que elas existem
   antes de serem usadas (boa prática). */
int is_primo(int x); /* função auxiliar que verifica se x é primo */
int primeiros_primos_acima_de(int limite, int quantidade, int out[]); /* função pedida */

/* ---------------------------------------------------
   is_primo: testa se um inteiro x (>=0) é primo
   - retorna 1 se for primo, 0 caso contrário
   - usa teste até sqrt(x) e pula pares para eficiência
   --------------------------------------------------- */
int is_primo(int x) {
    /* Se x for menor que 2 não é primo (0 e 1 não são primos) */
    if (x < 2) {                /* palavra-chave if, condição (x < 2) */
        return 0;               /* return 0 -> falso (não primo) */
    }

    /* 2 é primo (caso especial e único primo par) */
    if (x == 2) {               /* testa igualdade exata com 2 */
        return 1;               /* return 1 -> verdadeiro (primo) */
    }

    /* Se x for par (divisível por 2) e maior que 2, não é primo */
    if (x % 2 == 0) {           /* operador % obtém resto; == 0 verifica divisibilidade */
        return 0;
    }

    /* Limite para verificar divisores: sqrt(x). 
       Convertendo para int garante que o laço pare num inteiro. */
    int limite = (int) sqrt((double) x);  /* cast para double em sqrt */

    /* Testamos apenas divisores ímpares a partir de 3 até 'limite' */
    for (int d = 3; d <= limite; d += 2) { /* d inicia em 3; d+=2 pula pares */
        if (x % d == 0) {        /* se encontrar divisor exato, não é primo */
            return 0;
        }
    }

    /* Se não encontrou nenhum divisor, x é primo */
    return 1;
}

/* -------------------------------------------------------------------
   primeiros_primos_acima_de
   - in: limite (geralmente 100)
   - in: quantidade: quantos primos queremos obter (por exemplo 10)
   - out: vetor onde escreveremos os primos (deve ter capacidade >= quantidade)
   - retorna: número de primos escritos em out (0 em caso de parâmetros inválidos)
   ------------------------------------------------------------------- */
int primeiros_primos_acima_de(int limite, int quantidade, int out[]) {
    /* Validação de parâmetros: checar ponteiro e tamanhos para segurança */
    if (out == NULL) {          /* se out é NULL, não temos onde escrever */
        return 0;               /* sinaliza falha retornando 0 */
    }
    if (quantidade <= 0) {      /* quantidade inválida (não faz sentido) */
        return 0;
    }

    int cont = 0;               /* contador de quantos primos já foram armazenados */
    int candidato = limite + 1; /* começamos a buscar por limite+1 (estritamente maior) */

    /* enquanto não tivermos preenchido 'quantidade' posições */
    while (cont < quantidade) {
        /* se candidato for primo, escrevemos em out[cont] e incrementamos cont */
        if (is_primo(candidato)) {
            out[cont] = candidato; /* grava primo na posição cont do vetor out */
            cont = cont + 1;       /* avança para próxima posição de escrita */
        }
        candidato = candidato + 1; /* testa o próximo número inteiro */
    }

    /* retorna quantos primos foram escritos (deve ser == quantidade em caso normal) */
    return cont;
}

/* -------------------------
   main: demonstração
   -------------------------
   - chama primeiros_primos_acima_de(100, 10, out) e imprime os 10 primos gerados
*/
int main(void) {
    const int QUANTIDADE = 10;   /* quantos primos queremos */
    const int LIMITE = 100;      /* limite base (vamos buscar primos maiores que 100) */
    int X[QUANTIDADE];           /* vetor de saída onde a função vai escrever os primos */

    /* Chama a função que preenche X com os 10 primeiros primos acima de 100 */
    int encontrados = primeiros_primos_acima_de(LIMITE, QUANTIDADE, X);

    /* Imprime resultado de forma amigável */
    if (encontrados != QUANTIDADE) { /* verificação extra — normalmente não acontece se parâmetros válidos */
        printf("Erro: foram encontrados apenas %d primos (esperado %d)\n", encontrados, QUANTIDADE);
        return EXIT_FAILURE;
    }

    printf("Os %d primeiros primos acima de %d sao:\n", QUANTIDADE, LIMITE);
    for (int i = 0; i < encontrados; i = i + 1) {
        printf("%d ", X[i]);      /* imprime cada primo seguido de espaço */
    }
    printf("\n");

    return EXIT_SUCCESS;         /* indica término sem erro ao sistema operacional */
}
