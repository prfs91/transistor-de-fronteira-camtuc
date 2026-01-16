/* lista02_ex011_media_indeterminada.c
   Exercício 11 - Lista 02 (Exercícios com Funções)

   Objetivo:
     Ler um número indeterminado de valores positivos (termina quando for digitado um valor negativo)
     e retornar a média aritmética usando a função:
       double media_de_n_numeros(const double valores[], int n);

   Estratégia:
     - usamos memória dinâmica (malloc/realloc) para armazenar os valores enquanto o usuário digita;
     - chamamos media_de_n_numeros para calcular a média a partir do vetor e do tamanho.
     - validações de leitura e de alocação são feitas para evitar crashes e comportamentos indefinidos.
*/

#include <stdio.h>   /* declara printf e scanf — funções de entrada/saída */
#include <stdlib.h>  /* declara malloc, realloc, free, exit — utilitários de memória e controle */

/* Protótipo da função — informa ao compilador a assinatura antes do uso */
double media_de_n_numeros(const double valores[], int n);

/* Implementação da função media_de_n_numeros
   - "const double valores[]" : vetor de doubles de onde vamos ler os valores (não modificamos o vetor)
   - "int n" : quantidade de elementos válidos dentro do vetor
   - retorna: média aritmética como double
*/
double media_de_n_numeros(const double valores[], int n) {
    /* Se não houver elementos (n == 0), não podemos dividir por zero.
       Decidimos devolver 0.0 como sinal de "sem média" — poderia ser NaN ou outro mecanismo,
       mas 0.0 é simples de tratar no main. */
    if (n == 0) {
        return 0.0;
    }

    /* soma acumuladora: usamos double para somar valores reais com casas decimais */
    double soma = 0.0;

    /* laço for para percorrer os n elementos do vetor e acumular a soma */
    for (int i = 0; i < n; i = i + 1) {
        soma = soma + valores[i]; /* soma += valores[i]; mas escrito de forma explícita para leigos */
    }

    /* calcula a média: soma / n */
    double media = soma / (double) n; /* cast para double por clareza, embora soma já seja double */

    /* devolve a média calculada ao chamador */
    return media;
}

/* --- Função main: interface com o usuário, leitura dinâmica e chamada da função --- */
int main(void) {
    /* ponteiro para o bloco de memória que conterá os valores digitados */
    double *valores = NULL;

    /* capacidade atual do buffer alocado (quantos doubles cabem neste bloco)
       começamos com zero e aumentamos conforme necessário com realloc */
    size_t capacidade = 0;

    /* contador de quantos valores válidos já lemos */
    int contador = 0;

    /* variável temporária para leitura do próximo valor do usuário */
    double entrada;

    /* instruções iniciais para o usuário */
    printf("MEDIA DE NUMEROS (LEITURA INDETERMINADA)\n");
    printf("----------------------------------------\n");
    printf("Digite valores positivos um por vez.\n");
    printf("Para encerrar a leitura, digite um valor negativo (por exemplo: -1).\n\n");

    /* laço de leitura: continua até o usuário digitar um número negativo ou ocorrer EOF/erro */
    while (1) {
        printf("Digite um valor (negativo encerra): ");

        /* scanf retorna o número de itens lidos com sucesso; aqui esperamos 1 double */
        if (scanf("%lf", &entrada) != 1) {
            /* leitura inválida (por exemplo, usuário digitou texto) ou EOF */
            printf("\nEntrada invalida ou fim de arquivo. Encerrando leitura.\n");
            break; /* sai do loop de leitura */
        }

        /* condição de término: valor negativo encerra a leitura conforme enunciado */
        if (entrada < 0.0) {
            printf("Valor negativo detectado: finalizando a entrada de dados.\n");
            break; /* sai do loop sem armazenar o valor negativo */
        }

        /* Se chegamos aqui, 'entrada' é um valor positivo — vamos armazená-lo.
           Checamos se temos capacidade suficiente no buffer alocado; se não, aumentamos. */

        /* se contador == capacidade, precisamos aumentar o buffer */
        if ((size_t)contador >= capacidade) {
            /* definimos nova capacidade: se capacidade==0, iniciamos com 4; senão dobramos */
            size_t nova_capacidade = (capacidade == 0) ? 4 : capacidade * 2;

            /* realloc: ajusta o tamanho do bloco apontado por 'valores' para nova_capacidade * sizeof(double).
               Se valores==NULL, realloc se comporta como malloc. */
            double *tmp = (double *) realloc(valores, nova_capacidade * sizeof(double));

            /* verificamos se realloc retornou NULL => falha de alocação */
            if (tmp == NULL) {
                /* se não conseguimos alocar, liberamos o que já foi alocado e saímos com erro */
                free(valores); /* libera memória previamente alocada (se houver) */
                printf("Erro: falha ao alocar memoria. Encerrando.\n");
                return 1; /* código de erro não-zero */
            }

            /* se deu certo, atualizamos o ponteiro e a capacidade */
            valores = tmp;
            capacidade = nova_capacidade;
        }

        /* armazena o valor lido no vetor na posição 'contador' e incrementa o contador */
        valores[contador] = entrada;
        contador = contador + 1;
    } /* fim do while de leitura */

    /* Após a leitura, 'contador' contém quantos valores positivos foram lidos e armazenados.
       Chamamos a função que calcula a média, passando o vetor e o número de elementos. */

    double media = media_de_n_numeros(valores, contador);

    /* Exibimos o resultado — tratamos o caso sem valores lidos (contador == 0) */
    if (contador == 0) {
        printf("\nNenhum valor positivo foi informado. Nao ha media para calcular.\n");
    } else {
        printf("\nForam lidos %d valores.\n", contador);
        printf("Media aritmetica: %.6lf\n", media); /* mostra com 6 casas decimais por precisão */
    }

    /* Liberamos a memória alocada dinamicamente antes de encerrar (boa prática) */
    free(valores);
    valores = NULL; /* evita dangling pointer */

    return 0; /* encerra o programa com sucesso */
}
