/*
  lista02_ex012_fatorial_func.c
  Exercício 12 - Lista 02 (Exercícios com Funções)

  Objetivo:
    - Implementar fatorial iterativo:
        unsigned long long fatorial(int n);
    - Implementar versão com verificação de overflow:
        int fatorial_com_verificacao(int n, unsigned long long *res);
      que retorna 1 se o cálculo coube em unsigned long long e escreve o resultado em *res,
      ou retorna 0 em caso de overflow ou entrada inválida.

  Observações rápidas:
    - Usamos unsigned long long porque ele oferece o maior espaço inteiro padrão em C
      para operações inteiras sem sinal (em muitos sistemas é 64 bits).
    - Para evitar overflow verificamos antes de multiplicar:
        if (acumulador > ULLONG_MAX / i) -> overflow
*/

#include <stdio.h>    /* printf, scanf: funções para escrever e ler do teclado */
#include <stdlib.h>   /* exit, útil para terminar em erro (boa prática incluir) */
#include <limits.h>   /* ULLONG_MAX: limite máximo do tipo unsigned long long */

/* --------------------------
   Protótipos das funções
   -------------------------- */
unsigned long long fatorial(int n);
int fatorial_com_verificacao(int n, unsigned long long *res);

/* -----------------------------------------
   Implementação: fatorial (versão iterativa)
   -----------------------------------------
   Calcula n! assumindo que n >= 0.
   Não faz verificação de overflow — use apenas para n pequeno/razonável.
*/
unsigned long long fatorial(int n) {
    /* Explicação do cabeçalho:
       - unsigned long long : tipo retornado (inteiro sem sinal, grande)
       - fatorial           : nome da função
       - (int n)            : parâmetro inteiro n
    */

    /* Validação: se o usuário passar n negativo, definimos comportamento:
       aqui retornamos 0 para indicar "entrada inválida" (poderíamos usar outra convenção).
       Em muitas implementações, o fatorial é definido apenas para n >= 0. */
    if (n < 0) {
        return 0ULL; /* 0ULL é literal 0 do tipo unsigned long long */
    }

    /* Caso base: 0! = 1
       Inicializamos o acumulador com 1 (produto neutro) */
    unsigned long long acumulador = 1ULL;

    /* Laço iterativo: multiplicamos 1 * 2 * 3 * ... * n */
    for (int i = 1; i <= n; i = i + 1) {
        acumulador = acumulador * (unsigned long long) i;
        /* Observação: aqui não há verificação de overflow.
           Se n for grande, este produto pode "estourar" e resultar em valor incorreto. */
    }

    /* Retornamos o valor calculado (pode ter overflow se n for grande) */
    return acumulador;
}

/* ---------------------------------------------------------
   Implementação: fatorial_com_verificacao
   ---------------------------------------------------------
   - Recebe n e ponteiro res.
   - Se n < 0 ou res == NULL, retorna 0 (erro).
   - Calcula iterativamente verificando *antes* de multiplicar se o próximo passo caberá
     em unsigned long long. Se couber, multiplica; se não couber, retorna 0 (overflow).
   - Em caso de sucesso escreve o resultado em *res e retorna 1.
*/
int fatorial_com_verificacao(int n, unsigned long long *res) {
    /* Verifica parâmetros básicos:
       - res deve apontar para uma área válida de memória onde escreveremos o resultado
       - n deve ser >= 0 (fatorial não definido para negativos neste contexto) */
    if (res == NULL) {
        /* ponteiro inválido -> erro */
        return 0;
    }
    if (n < 0) {
        /* entrada inválida -> erro */
        *res = 0ULL; /* opcional: escreve algo no local apontado para deixar consistente */
        return 0;
    }

    /* inicializa o acumulador */
    unsigned long long acc = 1ULL;

    /* laço para calcular fatorial com verificação de overflow */
    for (int i = 1; i <= n; i = i + 1) {

        /* Antes de fazer: acc = acc * i;
           verificamos se acc > ULLONG_MAX / i
           porque se acc * i > ULLONG_MAX, ocorrerá overflow.

           - ULLONG_MAX é a maior constante que o tipo unsigned long long pode guardar.
           - Se acc <= ULLONG_MAX / i então acc * i <= ULLONG_MAX (seguro).
           - Caso contrário, multiplicação excede limite e não podemos representar o valor.
        */

        if (acc > ULLONG_MAX / (unsigned long long) i) {
            /* overflow detectado: não podemos continuar com segurança */
            *res = 0ULL; /* opcional: valor de saída em caso de erro */
            return 0;    /* sinaliza falha (overflow) */
        }

        /* seguro multiplicar */
        acc = acc * (unsigned long long) i;
    }

    /* se chegamos aqui, não houve overflow; escrevemos resultado e retornamos sucesso */
    *res = acc;
    return 1;
}

/* --------------------------
   main: demonstração / testes
   --------------------------
   - Permite ao usuário digitar vários valores inteiros n e mostra:
     * o fatorial simples (uso de fatorial, sem checagem)
     * o fatorial com verificação (uso de fatorial_com_verificacao)
   - Mostra mensagens claras quando ocorrer overflow ou entrada inválida.
*/
int main(void) {
    int n; /* variável para leitura do inteiro */

    /* Mensagem inicial explicativa para o usuário */
    printf("FATORIAL - DEMONSTRACAO\n");
    printf("-----------------------\n");
    printf("Digite um numero inteiro nao-negativo para calcular o fatorial.\n");
    printf("Digite um numero negativo para encerrar.\n\n");

    /* Loop de leitura até que o usuário indique parada (valor negativo) */
    while (1) {
        printf("n: ");

        /* lê um inteiro; scanf retorna quantos itens foram lidos */
        if (scanf("%d", &n) != 1) {
            /* leitura inválida (por exemplo, EOF ou caractere não-numérico) */
            printf("\nLeitura encerrada ou entrada invalida. Saindo.\n");
            break;
        }

        /* condição de saída: n negativo */
        if (n < 0) {
            printf("Valor negativo detectado: encerrando.\n");
            break;
        }

        /* --- Uso 1: fatorial sem verificação (cuidado com overflow) --- */
        unsigned long long f1 = fatorial(n);
        printf("fatorial(%d) [sem verificacao] = %llu\n", n, f1);

        /* --- Uso 2: fatorial com verificacao de overflow --- */
        unsigned long long resultado_seguro = 0ULL;
        int ok = fatorial_com_verificacao(n, &resultado_seguro);
        if (ok) {
            printf("fatorial(%d) [com verificacao] = %llu (sem overflow)\n", n, resultado_seguro);
        } else {
            printf("fatorial(%d) [com verificacao] -> overflow ou entrada invalida; calculo nao cabe em unsigned long long\n", n);
        }

        printf("\n"); /* separador antes da próxima leitura */
    }

    return 0; /* fim do programa com sucesso */
}
