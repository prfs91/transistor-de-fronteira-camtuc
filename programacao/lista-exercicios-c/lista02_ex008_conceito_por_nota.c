/* lista02_ex008_conceito_por_nota.c
   Exercício 8 - Lista 02 (Exercícios com Funções)

   Objetivo:
     Implementar a função:
       char conceito_por_media(double media);
     Que recebe a média final (double) e retorna o conceito:
       0.0 - 4.9 -> 'D'
       5.0 - 6.9 -> 'C'
       7.0 - 8.9 -> 'B'
       9.0 -10.0 -> 'A'

   Boas práticas aplicadas:
     - protótipo da função antes do uso;
     - validação do parâmetro (faixa 0.0 .. 10.0);
     - nome de função descritivo e simples;
     - comentário explicando intenção.
*/

#include <stdio.h>    /* printf e scanf: entrada e saída */
#include <stdlib.h>   /* exit, atof, boa prática incluir */
#include <ctype.h>    /* não estritamente necessário aqui, mas incluído por hábito */

 /* Protótipo: declara a função antes de usá-la em main */
char conceito_por_media(double media);

/* === Implementação da função conceito_por_media === */
/* A função recebe um valor "media" e devolve um caractere 'A'..'D' conforme tabela.
   Se a média estiver fora do intervalo 0.0..10.0, a função devolve 'X' (sinal de erro). */
char conceito_por_media(double media) {
    /* Validação: mídias negativas ou maiores que 10 não fazem sentido no contexto */
    if (media < 0.0 || media > 10.0) {
        /* Retornamos 'X' para indicar entrada inválida; chamador pode detectar isso. */
        return 'X';
    }

    /* Verificamos as faixas de forma ordeira, do menor para o maior ou do maior para o menor.
       Aqui escolhemos do maior para o menor para evitar muitos testes compostos. */

    if (media >= 9.0) {
        /* Média maior ou igual a 9.0 -> conceito A */
        return 'A';
    } else if (media >= 7.0) {
        /* Média entre 7.0 (inclusive) e 9.0 (exclusive) -> conceito B */
        return 'B';
    } else if (media >= 5.0) {
        /* Média entre 5.0 (inclusive) e 7.0 (exclusive) -> conceito C */
        return 'C';
    } else {
        /* Qualquer média menor que 5.0 (e >= 0.0 por validação prévia) -> D */
        return 'D';
    }
}

/* === Função main: demonstração interativa do uso da função === */
int main(void) {
    double media;      /* variável que armazenará a média lida do usuário */
    char conceito;     /* variável que armazenará o conceito retornado pela função */

    /* Mensagem inicial para orientar o usuário */
    printf("CONCEITO POR MEDIA - DEMONSTRACAO\n");
    printf("---------------------------------\n");
    printf("Digite medias de 0.0 a 10.0 (ou Ctrl+D/Ctrl+Z para encerrar):\n");

    /* Loop para permitir várias leituras até o usuário encerrar */
    while (1) {
        printf("Media: ");                              /* pede ao usuário que digite uma média */

        /* Lê um double da entrada; scanf retorna o número de itens lidos com sucesso */
        if (scanf("%lf", &media) != 1) {               /* se não conseguiu ler 1 double, encerra */
            printf("\nLeitura encerrada ou entrada invalida. Saindo.\n");
            break;                                    /* sai do loop */
        }

        /* Chama a função que traduz a média em conceito */
        conceito = conceito_por_media(media);

        /* Se a função retornou 'X', significa entrada inválida (fora de 0.0..10.0) */
        if (conceito == 'X') {
            printf("Media invalida: %.2lf. Informe valor entre 0.0 e 10.0.\n\n", media);
            continue; /* volta ao começo do loop pedindo nova entrada */
        }

        /* Mostra o conceito associado */
        printf("Media: %.2lf -> Conceito: %c\n\n", media, conceito);
    }

    return 0; /* finaliza o programa indicando sucesso */
}
