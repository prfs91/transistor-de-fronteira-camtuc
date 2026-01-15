/*
  lista02_ex017_fatorial_vetor.c
  Exercício 17 - Lista 02 (Exercícios de Vetores com Funções)

  Objetivo:
    - Implementar funções que, dado um vetor de inteiros `in[0..n-1]`, preencham
      `out[0..n-1]` com o fatorial de cada elemento:
        out[i] = in[i]!
    - Duas versões:
        1) fatorial_vetor : cálculo direto (sem checagem de overflow)
        2) fatorial_vetor_seguro : cálculo com verificação de overflow (retorna 1 se ok, 0 se overflow em algum)
*/

#include <stdio.h>        /* printf, scanf: leitura e escrita no terminal */
#include <stdlib.h>       /* exit, NULL, boa prática incluir utilitários */
#include <limits.h>       /* ULLONG_MAX: maior valor representável por unsigned long long */

/* -------------------------
   Protótipos das funções
   ------------------------- */

/* Versão 1: calcula fatoriais sem checagem de overflow.
   - parâmetros:
       const int in[] : vetor de entrada com inteiros (não será modificado)
       unsigned long long out[] : vetor de saída onde serão colocados os fatoriais
       int n : quantidade de elementos válidos (tamanho dos vetores)
   - comportamento especial:
       * 0! = 1
       * se in[i] < 0, definimos out[i] = 0 (convenção para "entrada inválida")
*/
void fatorial_vetor(const int in[], unsigned long long out[], int n);

/* Versão 2: calcula fatoriais com verificação de overflow.
   - retorna 1 se todos os fatoriais couberam em unsigned long long;
     retorna 0 se algum elemento causou overflow ou se parâmetros inválidos.
   - em caso de overflow para um elemento específico, escrevemos out[i] = 0 para sinalizar problema naquele índice.
*/
int fatorial_vetor_seguro(const int in[], unsigned long long out[], int n);

/* -------------------------
   Implementação: fatorial_vetor
   ------------------------- */
void fatorial_vetor(const int in[], unsigned long long out[], int n) {
    /* 1) validação simples dos parâmetros:
         - se in ou out for NULL ou n <= 0, não há o que fazer — retornamos.
         - essa verificação evita que tentemos acessar memória inválida. */
    if (in == NULL || out == NULL || n <= 0) {
        return; /* nada a fazer com parâmetros inválidos */
    }

    /* 2) para cada posição i do vetor (0..n-1) calculamos o fatorial de in[i] */
    for (int i = 0; i < n; i = i + 1) {
        int valor = in[i]; /* pega o valor inteiro de entrada no índice i */

        /* Cada fatorial:
           - se valor < 0: definimos out[i] = 0 (convenção: fatorial indefinido para negativos)
           - se valor == 0: 0! = 1
           - para valor > 0: multiplicamos 1 * 2 * ... * valor (iterativo)
           Observação: NÃO checamos overflow aqui — essa versão é didática e simples. */
        if (valor < 0) {
            out[i] = 0ULL; /* sinaliza entrada inválida com 0 no vetor de saída */
            continue;     /* passa para o próximo índice */
        }

        /* acumulador do produto (fatorial) inicia em 1 */
        unsigned long long acc = 1ULL;

        /* multiplicação iterativa de 1 até valor */
        for (int k = 1; k <= valor; k = k + 1) {
            acc = acc * (unsigned long long) k;
            /* se valor for grande, aqui poderá ocorrer overflow sem aviso;
               o valor resultante ficará truncado conforme o tipo; é por isso que
               existe a versão segura abaixo. */
        }

        /* armazena o fatorial calculado no vetor de saída */
        out[i] = acc;
    }
}

/* -------------------------
   Implementação: fatorial_vetor_seguro
   ------------------------- */
int fatorial_vetor_seguro(const int in[], unsigned long long out[], int n) {
    /* Validação básica dos parâmetros:
       - in e out não podem ser NULL, n deve ser positivo.
       - se inválido, retornamos 0 (falha). */
    if (in == NULL || out == NULL || n <= 0) {
        return 0; /* parâmetro inválido */
    }

    /* Para detectar overflow usamos a propriedade:
       antes de fazer acc * k verificamos se acc <= ULLONG_MAX / k.
       Se acc > ULLONG_MAX / k, a multiplicação ultrapassaria o limite e
       causaria overflow. */

    /* Variável que indica se todos os cálculos caberam no tipo */
    int todos_ok = 1; /* assumimos ok até encontrar overflow */

    /* Percorre os elementos do vetor */
    for (int i = 0; i < n; i = i + 1) {
        int valor = in[i]; /* valor cujo fatorial vamos calcular */

        if (valor < 0) {
            /* fatorial indefinido para negativos: sinalizamos com out[i] = 0 e marcamos falha */
            out[i] = 0ULL;
            todos_ok = 0; /* entrada inválida conta como problema */
            continue;
        }

        /* 0! = 1 (inicializa acumulador) */
        unsigned long long acc = 1ULL;
        int overflow_ocorreu = 0; /* flag local para este elemento */

        /* multiplica de 1 a valor, verificando antes se a próxima multiplicação cabe */
        for (int k = 1; k <= valor; k = k + 1) {

            /* verifica: se acc > ULLONG_MAX / k então acc * k > ULLONG_MAX (overflow) */
            if (acc > ULLONG_MAX / (unsigned long long) k) {
                /* overflow detectado: não podemos representar acc * k em unsigned long long */
                overflow_ocorreu = 1;
                break; /* sai do laço de multiplicação para este valor */
            }

            /* operação segura: realiza a multiplicação */
            acc = acc * (unsigned long long) k;
        }

        if (overflow_ocorreu) {
            /* marcamos saída deste índice como 0 para indicar problema e anotamos falha geral */
            out[i] = 0ULL;
            todos_ok = 0;
        } else {
            /* cálculos Ok: gravamos resultado no vetor de saída */
            out[i] = acc;
        }
    }

    /* retorna 1 se todos os elementos foram calculados sem overflow, 0 caso contrário */
    return todos_ok;
}

/* -------------------------
   main: demonstração / teste
   ------------------------- */
int main(void) {
    /* definimos n = 10 (tamanho pedido no enunciado) */
    const int N = 10;

    /* vetores de entrada e saída */
    int A[N];                          /* vetor de inteiros (entrada) */
    unsigned long long B[N];           /* vetor de saída (fatoriais) - versão direta */
    unsigned long long B_seguro[N];    /* vetor de saída (fatoriais) - versão segura */

    /* instruções para o usuário */
    printf("FATORIAL VETOR - DEMONSTRACAO\n");
    printf("------------------------------\n");
    printf("Digite %d numeros inteiros (valores negativos serao tratados como invalidos):\n", N);

    /* leitura de N inteiros para o vetor A */
    for (int i = 0; i < N; i = i + 1) {
        /* solicitamos um valor e lemos com scanf */
        if (scanf("%d", &A[i]) != 1) {
            /* leitura falhou (EOF ou entrada invalida) -> encerra com mensagem */
            printf("\nLeitura encerrada ou invalida. Encerrando.\n");
            return 1;
        }
    }

    /* chama a versão sem verificacao (didática) */
    fatorial_vetor(A, B, N);

    /* chama a versão segura que detecta overflow */
    int ok = fatorial_vetor_seguro(A, B_seguro, N);

    /* mostra os resultados: índice, A[i], B[i] (direto), B_seguro[i] (seguro) */
    printf("\nResultados:\n");
    printf("indice | A[i] (entrada) | B[i] (sem verificacao) | B_seguro[i] (com verificacao)\n");
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < N; i = i + 1) {
        /* imprime linha formatada:
           - %2d : indice
           - %12d : valor A[i]
           - %22llu : valor B[i] (unsigned long long)
           - %22llu : valor B_seguro[i]
           Observação: B_seguro[i] == 0 pode indicar overflow ou entrada inválida (negativo). */
        printf("%5d  | %13d | %22llu | %22llu\n", i, A[i], B[i], B_seguro[i]);
    }

    /* interpretaçao final para o usuário sobre overflow */
    if (ok) {
        printf("\nTodos os fatoriais couberam em unsigned long long.\n");
    } else {
        printf("\nAo menos um fatorial NAO coube em unsigned long long ou havia entradas invalidas.\n");
        printf("Nos indices com valor 0 em B_seguro ocorreu overflow ou entrada invalida.\n");
    }

    return 0; /* sucesso */
}
