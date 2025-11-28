#include <stdio.h>   // Biblioteca padrão para entrada e saída (printf, scanf)
#include <stdlib.h>  // Biblioteca padrão para utilitários (por exemplo exit), boa prática incluir

/*
  Arquivo: lista01_ex003_media_ponderada.c
  Objetivo: Ler três notas de um aluno e imprimir a média ponderada.
  Pesos: nota1 -> peso 2, nota2 -> peso 3, nota3 -> peso 5.
  Fórmula: media_ponderada = (nota1*2 + nota2*3 + nota3*5) / (2 + 3 + 5)
*/

int main(void) {
    /* Declaração de variáveis com nomes claros (boas práticas) */
    double nota1;               // primeira nota do aluno
    double nota2;               // segunda nota do aluno
    double nota3;               // terceira nota do aluno
    const int peso1 = 2;        // peso da primeira nota (const porque não vai mudar)
    const int peso2 = 3;        // peso da segunda nota
    const int peso3 = 5;        // peso da terceira nota
    const int soma_pesos = peso1 + peso2 + peso3; // soma dos pesos (2+3+5 = 10)
    double soma_ponderada;      // soma das notas multiplicadas pelos respectivos pesos
    double media_ponderada;     // resultado final: média ponderada

    /* Cabeçalho informativo */
    printf("CALCULADORA DE MEDIA PONDERADA\n");
    printf("--------------------------------\n");

    /* Leitura e validação da primeira nota */
    printf("Digite a primeira nota (peso %d): ", peso1);
    if (scanf("%lf", &nota1) != 1) {    // verifica se leitura foi bem-sucedida
        printf("Entrada invalida para a primeira nota. Encerrando.\n");
        return 1;                       // código de erro
    }

    /* Leitura e validação da segunda nota */
    printf("Digite a segunda nota (peso %d): ", peso2);
    if (scanf("%lf", &nota2) != 1) {
        printf("Entrada invalida para a segunda nota. Encerrando.\n");
        return 1;
    }

    /* Leitura e validação da terceira nota */
    printf("Digite a terceira nota (peso %d): ", peso3);
    if (scanf("%lf", &nota3) != 1) {
        printf("Entrada invalida para a terceira nota. Encerrando.\n");
        return 1;
    }

    /* Observação opcional: você pode validar intervalo das notas (ex.: 0 a 10).
       Não é obrigatório no enunciado, mas é boa prática. Aqui mostramos um exemplo simples: */
    if (nota1 < 0.0 || nota2 < 0.0 || nota3 < 0.0) {
        printf("Notas invalidas: nao sao permitidos valores negativos. Encerrando.\n");
        return 1;
    }

    /* Calcula a soma ponderada: cada nota multiplicada pelo seu peso */
    soma_ponderada = (nota1 * peso1) + (nota2 * peso2) + (nota3 * peso3);

    /* Calcula a média ponderada dividindo a soma ponderada pela soma dos pesos */
    media_ponderada = soma_ponderada / (double)soma_pesos;

    /* Exibe o resultado com formatação amigável (2 casas decimais) */
    printf("\nResultados:\n");
    printf("Nota1 = %.2lf (peso %d)\n", nota1, peso1);
    printf("Nota2 = %.2lf (peso %d)\n", nota2, peso2);
    printf("Nota3 = %.2lf (peso %d)\n", nota3, peso3);
    printf("Media ponderada = %.2lf\n", media_ponderada);

    return 0;  // indica que o programa terminou com sucesso
}