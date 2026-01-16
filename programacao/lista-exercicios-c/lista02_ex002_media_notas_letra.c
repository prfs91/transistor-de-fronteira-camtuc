#include <stdio.h>   // Declara printf e scanf (entrada/saída)
#include <stdlib.h>  // Declara exit e utilitários (boa prática incluir)
#include <ctype.h>   // Declara toupper para normalizar o caractere 'tipo'

/*
  lista02_ex002_media_notas_letra.c
  Exercício 2 - Lista 02 (Exercícios com Funções)

  Função principal sugerida:
    double media_ponderada_por_letra(double n1, double n2, double n3, char tipo);

  Objetivo:
    - se tipo == 'a' ou 'A' -> média aritmética: (n1 + n2 + n3) / 3
    - se tipo == 'p' ou 'P' -> média ponderada com pesos 5,3,2:
         media = (n1*5 + n2*3 + n3*2) / (5+3+2)
    - caso tipo inválido -> função retorna NaN (not a number) sinalizando erro
*/

/* Protótipo da função (boa prática declarar antes de usar) */
double media_ponderada_por_letra(double n1, double n2, double n3, char tipo);

/* Implementação da função */
double media_ponderada_por_letra(double n1, double n2, double n3, char tipo) {
    /* Normaliza o caractere para maiúscula para tratar 'a' e 'A' igualmente */
    char t = (char) toupper((unsigned char) tipo);

    /* Se for média aritmética: soma / 3 */
    if (t == 'A') {
        double soma = n1 + n2 + n3;           // soma das notas
        double media = soma / 3.0;            // divide por 3 (número de notas)
        return media;                         // devolve a média ao chamador
    }

    /* Se for média ponderada: pesos 5,3,2 (total de pesos = 10) */
    if (t == 'P') {
        const double PESO1 = 5.0;             // peso da primeira nota
        const double PESO2 = 3.0;             // peso da segunda nota
        const double PESO3 = 2.0;             // peso da terceira nota
        const double SOMA_PESOS = PESO1 + PESO2 + PESO3; // soma dos pesos = 10.0

        double soma_ponderada = n1 * PESO1 + n2 * PESO2 + n3 * PESO3; // calcula numerador
        double media = soma_ponderada / SOMA_PESOS; // divide pelo total de pesos
        return media;                         // devolve a média ponderada
    }

    /* Se chegou aqui, 'tipo' é inválido: retornamos NaN como sinal de erro.
       Em C, não existe literal padrão para NaN sem math.h, então usamos uma técnica:
       0.0/0.0 produz NaN em ponto flutuante IEEE-754 (comportamento comum).
       Outra opção seria retornar um valor negativo que não exista em contexto,
       ou usar errno. Aqui usamos NaN para ser explícito que não é um número válido. */
    return (0.0 / 0.0);
}

/* Função main para demonstrar e testar a função solicitada */
int main(void) {
    double n1, n2, n3;           // variáveis para armazenar as três notas
    char tipo;                   // variável que armazenará a letra 'a' ou 'p'
    double resultado;            // armazenará o retorno da função (a média)

    /* Mensagem inicial para o usuário */
    printf("CALCULO DE MEDIA (a = aritmetica, p = ponderada)\n");
    printf("Digite as tres notas (separadas por espaco): ");

    /* Leitura das tres notas (validação simples do scanf) */
    if (scanf("%lf %lf %lf", &n1, &n2, &n3) != 3) {
        printf("Entrada invalida para as notas. Execute novamente e digite tres numeros.\n");
        return 1; /* encerra com código de erro */
    }

    /* Lê o tipo de média desejado (caractere). O espaço antes de %c consome um newline pendente */
    printf("Digite o tipo de media ('a' para aritmetica, 'p' para ponderada): ");
    if (scanf(" %c", &tipo) != 1) {
        printf("Entrada invalida para o tipo. Execute novamente.\n");
        return 1;
    }

    /* Chama a função com as notas e o tipo */
    resultado = media_ponderada_por_letra(n1, n2, n3, tipo);

    /* Verifica se resultado é NaN (indica tipo inválido) - técnica: NaN != NaN é verdadeiro */
    if (!(resultado == resultado)) { /* se resultado != resultado então é NaN */
        printf("Tipo de media invalido. Use 'a' para aritmetica ou 'p' para ponderada.\n");
        return 1;
    }

    /* Exibe a média calculada com 4 casas decimais */
    printf("Media calculada: %.4lf\n", resultado);

    return 0; /* sucesso */
}

