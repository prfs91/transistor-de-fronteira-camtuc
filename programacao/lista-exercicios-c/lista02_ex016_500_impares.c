/* lista02_ex016_500_impares.c
   Exercício 16 - Lista 02 (Exercícios de Vetores com Funções)

   Objetivo:
     Implementar a função:
       void preencher_impares(int out[], int quantidade);
     que preenche o vetor 'out' com os primeiros 'quantidade' números ímpares:
       1, 3, 5, 7, 9, ...

   Observações:
     - A função assume que o chamador alocou espaço suficiente em 'out' (capacidade >= quantidade).
     - A função valida apenas argumentos simples (quantidade <= 0 -> nada a fazer, out == NULL -> nada).
*/

#include <stdio.h>   /* Declara printf, usado para mostrar resultados ao usuário. */
#include <stdlib.h>  /* Declara exit, malloc, free — utilitários padrão. */

/* Protótipo da função: diz ao compilador que existe essa função com essa assinatura */
void preencher_impares(int out[], int quantidade);

/* ---------------------------
   Implementação da função
   --------------------------- */
/* A função preenche out[0..quantidade-1] com os primeiros 'quantidade' números ímpares.
   Parâmetros:
     - out: vetor de inteiros onde será escrito (o chamador deve garantir capacidade suficiente)
     - quantidade: quantos números ímpares preencher (se <=0, a função não faz nada)
*/
void preencher_impares(int out[], int quantidade) {
    /* Verificação rápida: se out é NULL não temos onde escrever -> nada a fazer.
       Por segurança, tratamos esse caso e retornamos. */
    if (out == NULL) {            /* verifica se o ponteiro é inválido */
        return;                   /* retorna sem fazer nada (proteção) */
    }

    /* Se a quantidade for menor ou igual a zero, não há elementos a preencher.
       Retornamos sem fazer nada. */
    if (quantidade <= 0) {        /* verifica se a quantidade pedida é válida */
        return;                   /* nada a fazer para valores não-positivos */
    }

    /* Vamos preencher usando dois valores que controlam a geração dos ímpares:
       - atual_impar: o próximo número ímpar a armazenar (iniciamos em 1)
       - indice: posição atual no vetor onde escrever (0..quantidade-1) */

    int atual_impar = 1;          /* primeiro número ímpar (1) */
    int indice = 0;               /* começamos preenchendo out[0] */

    /* Laço while: repete até termos preenchido 'quantidade' posições */
    while (indice < quantidade) { /* enquanto não preencher todas as posições */
        out[indice] = atual_impar;    /* escreve o ímpar atual na posição 'indice' do vetor */
        indice = indice + 1;          /* passa para a próxima posição do vetor */
        atual_impar = atual_impar + 2;/* próximo ímpar = atual + 2 (pula o par seguinte) */
    }
}

/* ---------------------------
   main: demonstração
   --------------------------- */
int main(void) {
    const int CAPACIDADE = 500;      /* define a capacidade exigida no enunciado */
    int *A = NULL;                   /* ponteiro para o vetor que vamos alocar dinamicamente */

    /* aloca dinamicamente espaço para CAPACIDADE inteiros */
    A = (int *) malloc(CAPACIDADE * sizeof(int));
    if (A == NULL) {                 /* verifica se a alocação deu certo */
        printf("Erro: falha ao alocar memoria.\n");
        return 1;                    /* retorna código de erro ao sistema operacional */
    }

    /* Define quantos ímpares queremos gerar (poderia ser menor que CAPACIDADE).
       Aqui usamos exatamente 500 conforme o enunciado. */
    int quantidade = 500;

    /* chama a função que preenche o vetor A[0..quantidade-1] com os 500 primeiros ímpares */
    preencher_impares(A, quantidade);

    /* mostra uma amostra: os 10 primeiros ímpares gerados */
    printf("Primeiros 10 impares:\n");
    for (int i = 0; i < 10 && i < quantidade; i = i + 1) {
        printf("%d ", A[i]);         /* imprime A[i] seguido de espaço */
    }
    printf("\n");

    /* mostra uma amostra: os 10 últimos ímpares gerados */
    printf("Ultimos 10 impares:\n");
    for (int i = quantidade - 10; i < quantidade; i = i + 1) {
        if (i < 0) continue;        /* proteção se quantidade < 10 (não acontece aqui) */
        printf("%d ", A[i]);        /* imprime A[i] seguido de espaço */
    }
    printf("\n");

    /* liberamos a memória alocada (boa prática) */
    free(A);
    A = NULL;                       /* evita dangling pointer */

    return 0;                       /* encerra o programa com sucesso */
}
