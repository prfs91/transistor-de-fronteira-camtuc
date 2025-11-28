#include <stdio.h>   // Biblioteca padrão para entrada/saída: printf, scanf
#include <stdlib.h>  // Biblioteca de utilitários (boa prática incluir)

/*
  Arquivo: lista01_ex017_media_ponderada_loop.c
  Objetivo:
    Ler repetidamente o código de um aluno e suas três notas, calcular a média ponderada
    dando peso 4 para a maior nota e peso 3 para cada uma das outras duas (total de 10),
    informar o código, as notas, a média e se o aluno foi "APROVADO" (média >= 5) ou
    "REPROVADO" (média < 5). Repetir até que seja lido um código negativo.
    Ao final, exibir a média geral (média das médias dos alunos processados).
*/

int main(void) {
    /* Constantes do problema */
    const int PESO_MAIOR = 4;            // peso atribuído à maior nota
    const int PESO_RESTANTE = 3;        // peso para cada uma das outras notas
    const int SOMA_PESOS = PESO_MAIOR + 2 * PESO_RESTANTE; // soma = 10

    /* Variáveis para controle do loop e estatísticas */
    int codigo_aluno;                    // código do aluno lido (entrada)
    double nota1, nota2, nota3;          // as três notas do aluno (podem ter casas decimais)
    double media_aluno;                  // média ponderada calculada para o aluno atual

    double soma_medias = 0.0;            // soma das médias para cálculo da média geral
    int quantidade_alunos = 0;           // quantos alunos foram processados

    /* Cabeçalho informativo */
    printf("MEDIA PONDERADA (peso 4 para a maior nota, 3 para as outras)\n");
    printf("Digite o codigo do aluno (valor negativo encerra):\n");

    /* Leitura inicial do codigo do aluno */
    printf("Codigo do aluno: ");
    if (scanf("%d", &codigo_aluno) != 1) { // valida leitura do código
        printf("Entrada invalida. Encerrando.\n");
        return 1;
    }

    /* Loop principal: continua enquanto codigo_aluno >= 0 */
    while (codigo_aluno >= 0) {

        /* Lê as três notas do aluno atual, com validação simples do scanf */
        printf("Digite a nota 1: ");
        if (scanf("%lf", &nota1) != 1) {
            printf("Entrada invalida para nota 1. Encerrando.\n");
            return 1;
        }
        printf("Digite a nota 2: ");
        if (scanf("%lf", &nota2) != 1) {
            printf("Entrada invalida para nota 2. Encerrando.\n");
            return 1;
        }
        printf("Digite a nota 3: ");
        if (scanf("%lf", &nota3) != 1) {
            printf("Entrada invalida para nota 3. Encerrando.\n");
            return 1;
        }

        /* Identifica qual é a maior nota e aplica os pesos correspondentes:
           - se nota1 for a maior -> nota1*4 + nota2*3 + nota3*3
           - se nota2 for a maior -> nota2*4 + nota1*3 + nota3*3
           - se nota3 for a maior -> nota3*4 + nota1*3 + nota2*3
           Observação: se houver empate pela maior nota, o programa escolhe a primeira
           maior encontrada (isso não altera a média se notas empatadas possuem mesmo valor).
        */
        if (nota1 >= nota2 && nota1 >= nota3) {
            /* nota1 é a maior (ou empata e aparece primeiro) */
            media_aluno = (nota1 * PESO_MAIOR + nota2 * PESO_RESTANTE + nota3 * PESO_RESTANTE) / (double)SOMA_PESOS;
        } else if (nota2 >= nota1 && nota2 >= nota3) {
            /* nota2 é a maior */
            media_aluno = (nota2 * PESO_MAIOR + nota1 * PESO_RESTANTE + nota3 * PESO_RESTANTE) / (double)SOMA_PESOS;
        } else {
            /* nota3 é a maior */
            media_aluno = (nota3 * PESO_MAIOR + nota1 * PESO_RESTANTE + nota2 * PESO_RESTANTE) / (double)SOMA_PESOS;
        }

        /* Mostra informações do aluno e se foi aprovado ou reprovado (média >= 5 => APROVADO) */
        printf("\n--- Resultado do aluno (codigo %d) ---\n", codigo_aluno);
        printf("Notas: %.2lf, %.2lf, %.2lf\n", nota1, nota2, nota3);
        printf("Media ponderada: %.2lf\n", media_aluno);
        if (media_aluno >= 5.0) {
            printf("Situacao: APROVADO\n");
        } else {
            printf("Situacao: REPROVADO\n");
        }

        /* Atualiza estatísticas gerais */
        soma_medias = soma_medias + media_aluno;
        quantidade_alunos = quantidade_alunos + 1;

        /* Lê novo código para decidir se continua ou encerra */
        printf("\nDigite o codigo do proximo aluno (ou valor negativo para encerrar): ");
        if (scanf("%d", &codigo_aluno) != 1) {
            printf("Entrada invalida. Encerrando.\n");
            return 1;
        }
    } /* fim do while */

    /* Ao final, mostra a média geral (se houve ao menos um aluno processado) */
    if (quantidade_alunos == 0) {
        printf("\nNenhum aluno foi processado. Media geral nao pode ser calculada.\n");
    } else {
        double media_geral = soma_medias / (double)quantidade_alunos;
        printf("\n--- Estatisticas finais ---\n");
        printf("Quantidade de alunos processados: %d\n", quantidade_alunos);
        printf("Media geral das medias: %.2lf\n", media_geral);
    }

    return 0; /* encerra com sucesso */
}