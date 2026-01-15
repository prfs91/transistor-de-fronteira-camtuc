/*
  lista02_ex022_normalizar_por_maior.c

  Exercício 22 - Lista 02 (Exercícios de Vetores com Funções)

  Objetivo:
    - Implementar `void normalizar_por_maior(double v[], int n)` que:
        1) encontra o maior valor em v[0..n-1];
        2) divide cada elemento de v pelo maior (se maior != 0);
       O vetor `v` é modificado "in-place" (ou seja, o próprio vetor é alterado).

    - Implementar helper opcional:
        int indice_maior(const double v[], int n);
      que retorna o índice do maior elemento (ou -1 se parâmetros inválidos).

  Observações de boas práticas aplicadas:
    - validação de ponteiros e tamanhos para evitar comportamento indefinido;
    - uso de `const` em parâmetros de leitura (`indice_maior`);
    - funções pequenas e com responsabilidade única (SRP).
*/

/* inclusão das bibliotecas padrão necessárias */
#include <stdio.h>   /* declara printf e scanf — usadas para entrada/saída */
#include <stdlib.h>  /* declara EXIT_SUCCESS/EXIT_FAILURE e utilitários */
#include <math.h>    /* opcional: aqui não usamos funções de math, mas incluí por hábito */

void normalizar_por_maior(double v[], int n);

int indice_maior(const double v[], int n) {
    /* linha: if (v == NULL) return -1;
       - if : palavra-chave que inicia uma condição.
       - (v == NULL) : verifica se o ponteiro v é nulo; NULL significa "nenhum endereço".
       - return -1 : devolvemos -1 para sinalizar que o parâmetro é inválido.
       por que: tentar acessar v[i] quando v == NULL causaria crash; checar evita isso. */
    if (v == NULL) {
        return -1;
    }

    /* linha: if (n <= 0) return -1;
       - valida que n (quantidade de elementos) é positiva.
       por que: não faz sentido procurar maior em zero elementos; evitar loop com limite inválido. */
    if (n <= 0) {
        return -1;
    }

    /* linha: int idx_maior = 0;
       - declaramos idx_maior que guardará o índice do maior encontrado até agora.
       - inicializamos com 0 assumindo que há ao menos um elemento (já validamos n > 0).
       por que: precisamos de uma posição inicial para comparar com as demais. */
    int idx_maior = 0;

    /* linha: double maior = v[0];
       - declaramos 'maior' e atribuímos o primeiro elemento do vetor.
       por que: usamos o valor atual como referência inicial para comparações subsequentes. */
    double maior = v[0];

    /* linha: for (int i = 1; i < n; i = i + 1) { ... }
       - for : laço que itera pelos índices do vetor.
       - iniciamos em 1 porque já usamos v[0] como referência inicial.
       - i < n : garantimos que acessamos apenas índices válidos.
       - i = i + 1 : incrementa i de forma explícita (didática para iniciantes). */
    for (int i = 1; i < n; i = i + 1) {
        /* linha: if (v[i] > maior) { maior = v[i]; idx_maior = i; }
           - comparamos o elemento atual v[i] com o maior conhecido.
           - se v[i] for maior, atualizamos 'maior' e 'idx_maior'.
           por que: assim ao final do laço teremos o maior valor e seu índice. */
        if (v[i] > maior) {
            maior = v[i];
            idx_maior = i;
        }
    }

    /* linha: return idx_maior;
       - devolvemos o índice do maior elemento encontrado.
       por que: o chamador pode querer tanto o índice quanto usar esse índice para acessar o maior. */
    return idx_maior;
}

/* ======================================
   Implementação: normalizar_por_maior
   ======================================
   - recebe o vetor v[] e seu tamanho n;
   - encontra o maior valor usando indice_maior;
   - se maior != 0, divide cada v[i] por maior (modificando v in-place).
   - se maior == 0, NÃO realiza divisão para evitar divisão por zero.
*/
void normalizar_por_maior(double v[], int n) {
    /* validação inicial: se v é NULL ou n <= 0 não há trabalho a fazer */
    if (v == NULL) {            /* se v for ponteiro inválido */
        return;                 /* retorna sem alterar nada */
    }
    if (n <= 0) {               /* se n é inválido (0 ou negativo) */
        return;                 /* retorna sem alterar nada */
    }

    /* encontra o índice do maior elemento chamando helper */
    int idx = indice_maior(v, n); /* chama a função que já valida v e n */

    /* se indice_maior retornou -1, há um problema (parâmetros inválidos) */
    if (idx == -1) {
        return;                 /* segurança extra: não prossegue */
    }

    /* captura o valor do maior elemento para usar na normalização */
    double maior = v[idx];

    /* Se o maior for zero, divisão causaria erro ou resultado indefinido (divisão por zero).
       Decidimos não normalizar quando maior == 0 — preferimos manter o vetor como está
       e evitar gerar NaN/Inf. Aqui documentamos essa escolha e apenas retornamos. */
    if (maior == 0.0) {
        /* poderia avisar o usuário; como função utilitária não imprime nada — apenas retorna */
        return;
    }

    /* Agora percorremos todo o vetor e dividimos cada elemento pelo maior.
       Isso modifica v in-place, conforme pedido. */
    for (int i = 0; i < n; i = i + 1) {
        v[i] = v[i] / maior;     /* operação de normalização posição-a-posicao */
    }

    /* fim da função: o vetor v foi modificado no chamador */
}

/* =========================
   main: demonstração
   =========================
   - lê 50 valores reais do usuário para ilustrar a função;
   - imprime vetor antes e depois da normalização;
   - valida leitura e mostra mensagens claras.
*/
int main(void) {
    /* definimos o tamanho conforme o enunciado */
    const int N = 50;           /* N = 50 elementos no vetor B */

    /* declaramos o vetor B com N elementos do tipo double (reais) */
    double B[N];

    /* instruções iniciais ao usuário para orientar a entrada */
    printf("NORMALIZACAO POR MAIOR - DEMONSTRACAO\n");
    printf("------------------------------------\n");
    printf("Voce deve digitar %d valores reais (podem ser positivos, negativos ou zero).\n", N);
    printf("Apos a leitura o programa mostrara o vetor antes e depois da normalizacao.\n\n");

    /* leitura dos N valores com verificacao do retorno de scanf */
    for (int i = 0; i < N; i = i + 1) {
        printf("B[%d] = ", i);              /* prompt para maior clareza ao digitar */
        /* scanf tenta ler um double e retorna quantos itens foram lidos com sucesso */
        if (scanf("%lf", &B[i]) != 1) {     /* %lf é o especificador para double */
            printf("\nEntrada invalida. Encerrando.\n");
            return EXIT_FAILURE;            /* encerra com codigo de erro */
        }
    }

    /* imprime o vetor antes da normalizacao para comparar */
    printf("\nVetor antes da normalizacao:\n");
    for (int i = 0; i < N; i = i + 1) {
        /* %.6lf imprime double com 6 casas decimais (legivel) */
        printf("%10.6lf ", B[i]);
        if ((i + 1) % 5 == 0) printf("\n"); /* quebra de linha a cada 5 valores para legibilidade */
    }

    /* chama a funcao que normaliza o vetor pelo maior elemento */
    normalizar_por_maior(B, N);

    /* imprime o vetor apos a normalizacao */
    printf("\nVetor depois da normalizacao (cada elemento dividido pelo maior):\n");
    for (int i = 0; i < N; i = i + 1) {
        printf("%10.6lf ", B[i]);
        if ((i + 1) % 5 == 0) printf("\n");
    }

    /* fim do programa com codigo de sucesso */
    return EXIT_SUCCESS;
}
