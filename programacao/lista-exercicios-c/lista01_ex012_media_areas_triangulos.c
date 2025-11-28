#include <stdio.h>   // biblioteca padrão para entrada/saída: printf, scanf
#include <stdlib.h>  // biblioteca de utilitários (boa prática incluir)

/*
  Arquivo: lista01_ex012_media_areas_triangulos.c
  Objetivo:
    Ler base e altura de 5 triângulos (um por vez), calcular cada área usando
    Área = (base * altura) / 2 e ao final exibir a média das 5 áreas.
  Estratégia:
    - usar while para repetir 5 vezes (conforme o enunciado)
    - validar leitura (scanf) para evitar entradas inválidas
    - usar double para suportar medidas com casas decimais
*/

int main(void) {                         // início da função principal (onde o programa começa)

    const int TOTAL_TRIANGULOS = 5;      // número de triângulos que vamos ler — constante por clareza
    int contador = 0;                    // contador de quantos triângulos já processamos
    double base;                         // armazena a base do triângulo lida do usuário
    double altura;                       // armazena a altura do triângulo lida do usuário
    double area;                         // área calculada para o triângulo atual
    double soma_areas = 0.0;             // acumula a soma das áreas para calcular a média

    // mensagem inicial para o usuário
    printf("CALCULO DA AREA DE %d TRIANGULOS E MEDIA DAS AREAS\n", TOTAL_TRIANGULOS);
    printf("---------------------------------------------------\n");

    // laço "enquanto" que repete até processar TOTAL_TRIANGULOS triângulos
    while (contador < TOTAL_TRIANGULOS) {

        // informa qual triângulo estamos pedindo (1..5)
        printf("\nTriangulo #%d:\n", contador + 1);

        // solicita e lê a base
        printf("  Digite a base (por exemplo 3.5): ");
        if (scanf("%lf", &base) != 1) {  // valida se a leitura foi bem-sucedida
            printf("  Entrada invalida para a base. Encerrando.\n");
            return 1;                    // encerra com código de erro
        }

        // solicita e lê a altura
        printf("  Digite a altura (por exemplo 4.2): ");
        if (scanf("%lf", &altura) != 1) { // valida se a leitura foi bem-sucedida
            printf("  Entrada invalida para a altura. Encerrando.\n");
            return 1;                    // encerra com código de erro
        }

        // validações simples: base e altura não podem ser negativas
        if (base < 0.0 || altura < 0.0) {
            printf("  Valores invalidos: base e altura devem ser nao-negativos. Encerrando.\n");
            return 1;
        }

        // calcula a área do triângulo atual pela fórmula A = (base * altura) / 2
        area = (base * altura) / 2.0;

        // mostra a área calculada para esse triângulo
        printf("  Area do triangulo #%d = %.4lf\n", contador + 1, area);

        // acumula a área para o cálculo da média posteriormente
        soma_areas = soma_areas + area;

        // incrementa o contador para avançar ao próximo triângulo
        contador = contador + 1;
    }

    // após o laço, calcula a média das áreas
    double media_areas = soma_areas / (double)TOTAL_TRIANGULOS;

    // exibe a soma e a média com formatação amigável
    printf("\nSoma das areas = %.4lf\n", soma_areas);
    printf("Media das areas = %.4lf\n", media_areas);

    return 0; // finaliza o programa indicando sucesso
}