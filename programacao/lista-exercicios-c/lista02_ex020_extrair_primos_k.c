/* lista02_ex020_extrair_primos_k.c
   Exercício 20 - Lista 02 (Exercícios de Vetores com Funções)

   Objetivo:
     Implementar:
       int extrair_primos(const int in[], int n, int out[], int max_out);
     - Percorre in[0..n-1], identifica números primos, escreve os primos em out[0..k-1]
       até no máximo max_out elementos, e retorna k (quantidade de primos armazenados).
     - Em caso de parâmetros inválidos (ponteiros NULL, n<=0, max_out<=0) retorna 0.
*/

#include <stdio.h>   /* printf, scanf: funções para entrada/saída */
#include <stdlib.h>  /* EXIT_SUCCESS/EXIT_FAILURE, utilitários */
#include <math.h>    /* sqrt: usado para teste eficiente de primalidade */

/* Protótipos das funções */

/* Função auxiliar: verifica se um número inteiro positivo é primo.
   - recebe um inteiro x
   - retorna 1 se x for primo, 0 caso contrário
*/
int is_primo(int x);

/* Função principal pedida:
   - in: vetor de entrada com n elementos (const porque não será modificado)
   - n: número de elementos válidos em in
   - out: vetor de saída onde escreveremos os primos
   - max_out: capacidade máxima do vetor out (para evitar overflow)
   - retorno: quantidade de primos escritos em out (0..max_out)
*/
int extrair_primos(const int in[], int n, int out[], int max_out);

/* --- Implementação de is_primo --- */
int is_primo(int x) {
    /* Verifica condições básicas: números menores que 2 não são primos */
    if (x < 2) {
        return 0; /* 0 = falso (não primo) */
    }

    /* 2 é primo */
    if (x == 2) {
        return 1; /* 1 = verdadeiro (primo) */
    }

    /* elimina pares maiores que 2 (não primos) */
    if (x % 2 == 0) {
        return 0;
    }

    /* testamos divisores ímpares a partir de 3 até sqrt(x) */
    /* usamos sqrt(x) e convertemos para int para limitar laço */
    int limite = (int) sqrt((double) x);
    for (int d = 3; d <= limite; d += 2) {
        if (x % d == 0) {
            return 0; /* achou divisor -> não primo */
        }
    }

    /* se não achou divisor, é primo */
    return 1;
}

/* --- Implementação de extrair_primos --- */
int extrair_primos(const int in[], int n, int out[], int max_out) {
    /* Validação de parâmetros para evitar acessos inválidos */
    if (in == NULL || out == NULL) { /* se algum ponteiro for NULL, não podemos operar */
        return 0;                     /* retornamos 0 (nenhum primo extraído) */
    }
    if (n <= 0) {                     /* se não há elementos em 'in' */
        return 0;
    }
    if (max_out <= 0) {               /* se 'out' não tem capacidade positiva */
        return 0;
    }

    int cont = 0; /* contador de primos encontrados e armazenados em 'out' */

    /* Percorre todos os elementos válidos do vetor 'in' */
    for (int i = 0; i < n; i++) {
        int val = in[i];           /* lê o valor atual de in[i] */

        /* Apenas números inteiros positivos >=2 podem ser primos */
        if (val >= 2) {
            /* chama is_primo para verificar primalidade */
            if (is_primo(val)) {
                /* se for primo, verificamos se ainda há espaço em out */
                if (cont < max_out) {
                    out[cont] = val; /* armazenamos o primo no próximo slot disponível */
                    cont = cont + 1; /* incrementa contador */
                } else {
                    /* se out está cheio, paramos de adicionar (mas continuamos a varredura opcionalmente) */
                    /* aqui escolhemos parar de procurar para economizar tempo */
                    break;
                }
            }
        }
        /* se val < 2, ignoramos (não é primo) e continuamos */
    }

    return cont; /* retorna quantos primos foram escritos em out[0..cont-1] */
}

/* --- main demonstrativo para ler K[15], extrair primos e imprimir --- */
int main(void) {
    const int TAM_K = 15;           /* tamanho fixo do vetor K exigido pelo enunciado */
    int K[TAM_K];                   /* vetor de entrada onde o usuário irá digitar 15 inteiros */

    /* vetor de saída com capacidade acompanhada: vamos reservar espaço suficiente.
       no pior caso (todos os 15 números são primos) precisamos de 15 posições,
       mas definimos max_out = TAM_K para segurança. */
    int P[TAM_K];                   /* vetor para armazenar primos extraídos */
    int max_out = TAM_K;            /* capacidade máxima de P */

    /* instruções ao usuário */
    printf("EXTRACAO DE PRIMOS DE K[15]\n");
    printf("---------------------------\n");
    printf("Digite %d numeros inteiros (podem ser positivos, negativos, zero):\n", TAM_K);

    /* leitura dos 15 valores com validação simples */
    for (int i = 0; i < TAM_K; i++) {
        if (scanf("%d", &K[i]) != 1) {
            /* se scanf falhar (EOF ou entrada inválida), avisamos e encerramos com erro */
            printf("Entrada invalida durante leitura. Encerrando.\n");
            return EXIT_FAILURE;
        }
    }

    /* chama a função que extrai primos; recebe quantidade retornada */
    int encontrados = extrair_primos(K, TAM_K, P, max_out);

    /* mostra resultado para o usuário */
    if (encontrados == 0) {
        printf("\nNenhum primo encontrado em K (ou parametros invalidos / P sem capacidade).\n");
    } else {
        printf("\nForam encontrados %d primos em K. Vetor P:\n", encontrados);
        for (int i = 0; i < encontrados; i++) {
            printf("%d ", P[i]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
