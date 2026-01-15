/* lista02_ex018_soma_posicoes_vetores.c
   Exercício 18 - Lista 02 (Exercícios de Vetores com Funções)

   Objetivo:
     Implementar a função:
       void soma_vetores_posicao(const double a[], const double b[], double c[], int n);
     que preenche c[i] = a[i] + b[i] para i = 0..n-1.

   Observações:
     - usamos double no protótipo (conforme assinatura dada) para permitir números reais;
     - a e b são const pois a função não deve modificá-las;
     - a função valida parâmetros simples (ponteiros e n).
*/

#include <stdio.h>   /* printf, scanf - entrada/saída */
#include <stdlib.h>  /* exit - utilitários (incluir por boa prática) */

/* Protótipo da função: declara a assinatura antes do uso em main */
void soma_vetores_posicao(const double a[], const double b[], double c[], int n);

/* === Implementação da função soma_vetores_posicao === */
void soma_vetores_posicao(const double a[], const double b[], double c[], int n) {
    /* Verificação dos parâmetros de entrada:
       - se qualquer ponteiro for NULL, não temos onde ler/gravar -> retornamos sem fazer nada
       - se n <= 0, não há elementos válidos para somar -> retornamos sem fazer nada
       Essas checagens evitam comportamento indefinido (programa "quebrar"). */
    if (a == NULL || b == NULL || c == NULL) { /* testa se algum ponteiro é inválido */
        return; /* proteção: não prossegue se receber ponteiro inválido */
    }
    if (n <= 0) { /* testa se n é positivo */
        return; /* nada a fazer para n <= 0 */
    }

    /* Laço que percorre os índices de 0 até n-1 e calcula c[i] = a[i] + b[i] */
    for (int i = 0; i < n; i = i + 1) { /* i = índice atual (inicia em 0) */
        /* acessa a[i] e b[i], soma e grava em c[i] */
        c[i] = a[i] + b[i]; /* operação element-wise; por que é aqui? Porque queremos a soma posição-a-posição */
    }

    /* fim da função - nada a retornar porque c[] foi modificado por referência */
}

/* === main: demonstração do uso da função para n = 10 === */
int main(void) {
    const int N = 10;               /* tamanho dos vetores exigido pelo enunciado (10 elementos) */
    double A[N];                    /* vetor de entrada A (double para permitir reais) */
    double B[N];                    /* vetor de entrada B */
    double C[N];                    /* vetor de saída C onde vamos armazenar as somas */

    /* instruções para o usuário */
    printf("SOMA POSICAO-A-POSICAO DE VETORES (N = %d)\n", N);
    printf("-----------------------------------------\n");
    printf("Voce deve digitar %d numeros reais para o vetor A, depois %d para o vetor B.\n", N, N);
    printf("Os elementos podem ser decimais (ex: 1.5) pois usamos double.\n\n");

    /* leitura do vetor A com validação de entrada */
    printf("Digite os %d elementos do vetor A (separados por espaco ou enter):\n", N);
    for (int i = 0; i < N; i = i + 1) {
        /* scanf tenta ler um double e armazena em A[i] */
        if (scanf("%lf", &A[i]) != 1) { /* se não leu 1 double, houve erro/EOF */
            printf("Entrada invalida durante leitura do vetor A. Encerrando.\n");
            return 1; /* termina o programa com código de erro */
        }
    }

    /* leitura do vetor B com validação de entrada */
    printf("\nDigite os %d elementos do vetor B (separados por espaco ou enter):\n", N);
    for (int i = 0; i < N; i = i + 1) {
        if (scanf("%lf", &B[i]) != 1) {
            printf("Entrada invalida durante leitura do vetor B. Encerrando.\n");
            return 1;
        }
    }

    /* chama a função que realiza as somas por posição: C[i] = A[i] + B[i] */
    soma_vetores_posicao(A, B, C, N);

    /* imprime os vetores e o resultado para o usuário poder verificar */
    printf("\nResultados (indice : A[i] , B[i] , C[i] = A[i]+B[i]):\n");
    for (int i = 0; i < N; i = i + 1) {
        /* imprime cada linha com índice e três valores com 6 casas decimais para leitura */
        printf("%2d : %10.6lf , %10.6lf , %10.6lf\n", i, A[i], B[i], C[i]);
    }

    return 0; /* fim do programa com sucesso */
}
