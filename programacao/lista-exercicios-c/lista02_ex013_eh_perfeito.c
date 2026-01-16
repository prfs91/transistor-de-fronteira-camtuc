/*
  lista02_ex013_eh_perfeito.c
  Exercício 13 - Lista 02 (Exercícios com Funções)

  Objetivo:
    Implementar a função:
      int eh_perfeito(int n);
    que retorna 1 se n for um número perfeito (igual à soma dos seus divisores
    positivos próprios — excluindo n), ou 0 caso contrário.

  Observações / Boas práticas:
    - usamos um acumulador em tipo maior (long long) para reduzir risco de overflow
      ao somar divisores de números razoavelmente grandes;
    - testamos divisores até a raiz quadrada de n (otimização);
    - tratamos casos triviais (n <= 1) rapidamente;
    - comentários detalhados para iniciantes explicando cada linha.
*/

#include <stdio.h>   /* printf, scanf: entrada/saída */
#include <stdlib.h>  /* exit, free, etc. — utilitários (boa prática incluir) */
#include <math.h>    /* fabs, sqrt — não usamos sqrt diretamente; incluído se desejar usar */

/* Protótipo da função: declara a assinatura antes do uso */
int eh_perfeito(int n);

/* Definição da função eh_perfeito:
   recebe um inteiro n e retorna:
     - 1 se n for perfeito
     - 0 caso contrário
*/
int eh_perfeito(int n) {
    /* Linha: if (n <= 1) return 0;
       Por quê:
         - Números perfeitos são positivos e maiores que 1 (1 não é perfeito porque
           a soma dos seus divisores próprios é 0).
         - Tratar esse caso primeiro evita trabalho desnecessário. */
    if (n <= 1) return 0;

    /* Linha: long long soma = 1;
       Por quê:
         - Todo número natural n > 1 tem 1 como divisor próprio, então iniciamos a soma em 1.
         - Usamos long long para o acumulador porque a soma dos divisores pode exceder o
           limite de 'int' quando n é grande; isso reduz risco de overflow em entradas razoáveis.
         - Nota: iniciamos em 1 e não incluímos n na soma, porque divisores próprios excluem n. */
    long long soma = 1LL;

    /* Linha: int i = 2;
       Por quê:
         - vamos testar potenciais divisores começando em 2 (já lidamos com 1).
         - usar i como inteiro é suficiente para o laço. */
    int i = 2;

    /* Linha: while ((long long)i * i <= (long long)n) { ... }
       Por quê:
         - precisamos testar apenas divisores i tais que i*i <= n (i <= sqrt(n)).
         - se i divide n, então também n/i é divisor; testando até sqrt(n) encontramos os pares.
         - fazemos cast para long long antes da multiplicação para evitar overflow
           no produto i*i quando i for grande (defensivo). */
    while ((long long) i * (long long) i <= (long long) n) {

        /* Linha: if (n % i == 0) { ... }
           Por quê:
             - verifica se i divide n exatamente (resto zero).
             - se dividir, então i e n/i são ambos divisores de n.
             - devemos somar ambos na soma de divisores próprios (cuidando do caso i == n/i). */
        if (n % i == 0) {

            /* Linha: int outro = n / i;
               Por quê:
                 - 'outro' é o divisor complementar: se i * outro = n então outro também divide n.
                 - armazenamos em variável para clareza e evitar recalcular. */
            int outro = n / i;

            /* Linha: if (i == outro) { soma += i; } else { soma += i + outro; }
               Por quê:
                 - quando i == outro (isso acontece se i*i == n), o par de divisores coincide,
                   e devemos somar apenas uma vez (ex.: n=36, i=6 -> não somar 6 duas vezes).
                 - caso contrário, somamos os dois divisores distintos i e outro. */
            if (i == outro) {
                soma = soma + (long long) i;
            } else {
                soma = soma + (long long) i + (long long) outro;
            }
        }

        /* Linha: i = i + 1;
           Por quê:
             - incrementa o candidato a divisor para testar o próximo inteiro.
             - poderia incrementarmos de 1 em 1 (aqui fazemos assim por clareza).
             - para otimizar ainda mais poderíamos testar apenas ímpares (após tratar 2),
               mas manter simples é didático. */
        i = i + 1;
    } /* fim do while */

    /* Linha: if (soma == n) return 1; else return 0;
       Por quê:
         - depois de somar todos os divisores próprios, comparamos a soma a n.
         - se soma == n então n é perfeito (definição), retornamos 1 (verdadeiro).
         - caso contrário retornamos 0 (falso).
    */
    if (soma == (long long) n) {
        return 1;
    } else {
        return 0;
    }
}

/* --- main: demonstração interativa da função eh_perfeito --- */
int main(void) {
    int valor; /* variável para ler o inteiro do usuário */

    /* Mensagem inicial para orientar o usuário */
    printf("VERIFICADOR DE NUMERO PERFEITO\n");
    printf("------------------------------\n");
    printf("Digite numeros inteiros positivos (digite negativo para encerrar):\n");

    /* Loop de leitura para permitir múltiplos testes */
    while (1) {
        printf("Numero: ");

        /* Linha: if (scanf(\"%d\", &valor) != 1) { ... }
           Por quê:
             - scanf tenta ler um inteiro; retorna quantos itens foram lidos com sucesso.
             - se não leu 1, houve EOF (Ctrl+D/Ctrl+Z) ou entrada inválida; então encerramos. */
        if (scanf("%d", &valor) != 1) {
            printf("\nLeitura encerrada ou entrada invalida. Saindo.\n");
            break;
        }

        /* Linha: if (valor < 0) break;
           Por quê:
             - usamos número negativo como sinal para encerrar o programa, conforme instrução.
             - assim o usuário controla quando parar de testar valores. */
        if (valor < 0) {
            printf("Encerrando. Ate logo!\n");
            break;
        }

        /* Linha: int resp = eh_perfeito(valor);
           Por quê:
             - chama a função que determina se o número é perfeito.
             - guardamos o retorno (1 ou 0) em 'resp' para interpretar e mostrar mensagem. */
        int resp = eh_perfeito(valor);

        /* Linha: if (resp) printf("%d eh perfeito.\n", valor); else printf("%d nao eh perfeito.\n", valor);
           Por quê:
             - mostramos resultado amigável ao usuário.
             - resp é 1 (verdadeiro) se perfeito, 0 caso contrário.
        */
        if (resp) {
            printf("%d eh perfeito.\n", valor);
        } else {
            printf("%d nao eh perfeito.\n", valor);
        }
    } /* fim do loop de leitura */

    return 0; /* encerra o programa com sucesso */
}
