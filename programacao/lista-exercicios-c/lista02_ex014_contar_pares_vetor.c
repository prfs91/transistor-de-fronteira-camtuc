/* lista02_ex014_contar_pares_vetor.c
   Exercício 14 - Lista 02 (Exercícios de Vetores com Funções)

   Objetivo:
     Implementar a função:
       int contar_pares(const int v[], int n);
     que conta quantos elementos pares existem em v[0..n-1].

   Observações de boas práticas aplicadas:
     - o parâmetro v é 'const' para deixar claro que a função NÃO modifica o vetor;
     - validamos o tamanho n (não negativo) antes de processar;
     - main demonstra leitura de vetor X[15] e chamada da função.
*/

#include <stdio.h>   /* printf e scanf: entrada/saída */
#include <stdlib.h>  /* exit, útil para sair em erro (boa prática incluir) */

/* Protótipo da função: declara a assinatura antes do uso em main */
int contar_pares(const int v[], int n);

/* -------------------------
   Implementação da função
   ------------------------- */
/* A função recebe:
     - const int v[] : vetor de inteiros (não será modificado)
     - int n         : quantidade de elementos válidos em v (v[0]..v[n-1])
   Retorna:
     - quantidade de elementos pares (int)
*/
int contar_pares(const int v[], int n) {
    /* Validação: se n <= 0 não há elementos válidos; retornamos 0 pares */
    if (n <= 0) {
        return 0;
    }

    /* contador de pares, inicia em zero */
    int contador_pares = 0;

    /* laço for para percorrer as n posições do vetor */
    for (int i = 0; i < n; i = i + 1) {
        /* explicação: v[i] acessa o i-ésimo elemento do vetor */
        /* usamos o operador módulo (%) para verificar paridade:
           se v[i] % 2 == 0 então v[i] é divisível por 2 -> é par */
        if (v[i] % 2 == 0) {
            contador_pares = contador_pares + 1; /* incrementa contador quando achar par */
        }
    }

    /* devolve a quantidade de pares encontrados */
    return contador_pares;
}

/* -------------------------
   main: demonstração / teste
   ------------------------- */
int main(void) {
    const int TAM = 15;           /* tamanho fixo do vetor exigido pelo enunciado */
    int X[TAM];                   /* declara o vetor X[15] onde serão guardados os inteiros lidos */

    /* mensagem inicial para o usuário */
    printf("CONTADOR DE PARES NO VETOR X[15]\n");
    printf("--------------------------------\n");
    printf("Digite 15 numeros inteiros (separados por espaco ou enter):\n");

    /* Leitura dos 15 inteiros com verificação simples */
    for (int i = 0; i < TAM; i = i + 1) {
        /* scanf tenta ler um inteiro e retorna quantos valores leu com sucesso */
        if (scanf("%d", &X[i]) != 1) {
            /* se a leitura falhar (por exemplo, EOF ou texto), avisamos e encerramos com erro */
            printf("Erro na leitura. Certifique-se de digitar inteiros. Encerrando.\n");
            return 1; /* código de erro não-zero */
        }
    }

    /* chama a função que conta pares, passando o vetor e o tamanho (por valor) */
    int qtde_pares = contar_pares(X, TAM);

    /* mostra o resultado para o usuário */
    printf("Quantidade de valores pares em X[15]: %d\n", qtde_pares);

    return 0; /* encerra o programa com sucesso (código 0) */
}
