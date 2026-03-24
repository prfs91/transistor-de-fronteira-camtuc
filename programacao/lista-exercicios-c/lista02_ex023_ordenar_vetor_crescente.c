/* lista02_ex023_ordenar_vetor.c
   Exercício 23 - DESAFIO (Ordenação de vetor)

   Objetivo:
     - Implementar void ordenar_vetor(double v[], int n) que ordena v[0..n-1] em ordem crescente.
     - Implementar int comparar_double(const void *a, const void *b) para uso com qsort.
*/

/* ---------- includes: trazemos declarações de funções/padrões do C ---------- */
#include <stdio.h>   /* printf, scanf — entrada/saída */
#include <stdlib.h>  /* qsort, EXIT_SUCCESS/EXIT_FAILURE, malloc/free se necessário */

/* -------------------------------------------------------------------------
   Protótipos (declarações antecipadas) das funções que definiremos abaixo.
   Declarar protótipos ajuda o compilador a checar usos antes das definições.
----------------------------------------------------------------------------- */
int comparar_double(const void *a, const void *b); /* protótipo do comparador para qsort */
void ordenar_vetor(double v[], int n);             /* protótipo da função de ordenação */

/* ========================================================================
   comparar_double
   - assinatura exigida pelo qsort (void pointers)
   - devolve:
       <0 se *a < *b
        0 se *a == *b
       >0 se *a > *b
   Explicação detalhada:
     int : tipo de retorno (inteiro)
     comparar_double : nome da função
     (const void *a, const void *b) : dois ponteiros genéricos (void*) constantes,
                                      qsort usa esse tipo para ser genérico
=========================================================================== */
int comparar_double(const void *a, const void *b) {
    /* Cada parâmetro é um ponteiro para um elemento do array passado por qsort.
       Para comparar doubles precisamos:
         1) converter (cast) de void* para double*
         2) desreferenciar (*) para obter o valor double
       Fazemos isso cuidadosamente para evitar comportamento indefinido. */

    /* converte o ponteiro genérico 'a' para ponteiro para double e obtém o valor */
    const double da = *(const double *) a;
    /* explicação palavra a palavra:
       - const : indica que a variável não será alterada aqui (boa prática)
       - double : tipo numérico real de dupla precisão
       - da : nome da variável local que conterá o valor apontado por 'a'
       - *(const double *) a : (const double *) faz cast de 'a' para ponteiro para double;
                             o * à esquerda desreferencia esse ponteiro, obtendo o valor double.
    */

    /* faz o mesmo para 'b' */
    const double db = *(const double *) b;

    /* Comparação numérica robusta:
       - Se usarmos apenas (da - db) e converter para int, em casos de diferença muito
         pequena ou valores grandes pode haver perda/erro. Por isso usamos comparações
         condicionais que devolvem -1, 0 ou +1 conforme necessidade do qsort. */

    if (da < db) {
        return -1; /* a < b -> retorna negativo */
    } else if (da > db) {
        return 1;  /* a > b -> retorna positivo */
    } else {
        return 0;  /* iguais -> retorna zero */
    }
}

/* ============================================================================
   ordenar_vetor
   - Wrapper que valida parâmetros e chama qsort da libc para ordenar o vetor.
   - assinatura:
       void : não retorna valor (modifica o vetor in-place)
       ordenar_vetor : nome da função
       (double v[], int n) : recebe vetor de double e tamanho n
============================================================================ */
void ordenar_vetor(double v[], int n) {
    /* validações básicas para segurança */
    if (v == NULL) {     /* se ponteiro inválido (NULL) não há onde ordenar */
        return;          /* retorna sem fazer nada */
    }
    if (n <= 0) {        /* tamanho inválido não faz sentido */
        return;          /* retorna sem fazer nada */
    }

    /* qsort: protótipo
       void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
       - base: ponteiro para o primeiro elemento (v)
       - nmemb: número de elementos (n)
       - size: tamanho em bytes de cada elemento (sizeof(double))
       - compar: ponteiro para função de comparação (comparar_double)
       Utilizamos qsort porque é uma função padrão e geralmente é eficiente (QuickSort/Introsort).
    */
    qsort(v, (size_t) n, sizeof(double), comparar_double);
    /* explicação: chamamos qsort para ordenar 'v' em ordem determinada por comparar_double.
       qsort modifica o array 'v' diretamente (in-place). */
}

/* ===========================
   main: demonstração
   - lê 50 valores reais, imprime antes e depois da ordenação
   - valida entrada (scanf)
   =========================== */
int main(void) {
    const int N = 50;               /* N = 50 elementos conforme enunciado */
    double A[N];                    /* declara o vetor A com N doubles */

    /* instruções para o usuário */
    printf("ORDENACAO DE VETOR (N = %d) - DEMONSTRACAO\n", N);
    printf("-------------------------------------------\n");
    printf("Digite %d numeros reais (separados por espaco ou enter):\n", N);

    /* leitura dos N valores com verificação do scanf */
    for (int i = 0; i < N; i = i + 1) {
        /* scanf("%lf", &A[i]) lê um double; %lf é o especificador para double.
           O & passa o endereço da posição onde o valor será armazenado. */
        if (scanf("%lf", &A[i]) != 1) {
            /* se scanf não leu um double (retorno != 1), tratamos como erro e encerramos */
            printf("\nLeitura invalida. Encerrando.\n");
            return EXIT_FAILURE;
        }
    }

    /* imprime o vetor antes da ordenação para comparação */
    printf("\nVetor antes da ordenacao (primeiros 10 e ultimos 10 para visualizacao):\n");
    /* imprimimos apenas uma amostra para não poluir a tela */
    for (int i = 0; i < 10 && i < N; i = i + 1) {
        printf("%.6lf ", A[i]);
    }
    printf(" ... ");
    for (int i = N - 10; i < N; i = i + 1) {
        printf("%.6lf ", A[i]);
    }
    printf("\n");

    /* chama a função que ordena o vetor em ordem crescente */
    ordenar_vetor(A, N);

    /* imprime o vetor depois da ordenação — mostramos novamente amostra */
    printf("\nVetor depois da ordenacao (primeiros 10 e ultimos 10):\n");
    for (int i = 0; i < 10 && i < N; i = i + 1) {
        printf("%.6lf ", A[i]);
    }
    printf(" ... ");
    for (int i = N - 10; i < N; i = i + 1) {
        printf("%.6lf ", A[i]);
    }
    printf("\n");

    return EXIT_SUCCESS; /* finaliza o programa com código de sucesso */
}
