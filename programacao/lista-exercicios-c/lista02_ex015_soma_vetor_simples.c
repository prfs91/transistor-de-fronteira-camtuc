#include <stdio.h>
#include <stdlib.h>

double soma_vetor(const double v[], int n);
double media_vetor(const double v[], int n);

double soma_vetor(const double v[], int n) {
    
    double soma = 0.0;

    for (int i = 0; i < n; i = i + 1) {
        /* adiciona o elemento atual v[i] à soma acumulada */
        soma = soma + v[i];
    }

    /* devolve a soma calculada */
    return soma;
}

/* -----------------------------
   Implementação: media_vetor
   -----------------------------
   - Reutiliza soma_vetor para evitar duplicação de código.
   - Se n == 0 (sem elementos), devolve 0.0 e o chamador pode tratar como "sem média".
*/
double media_vetor(const double v[], int n) {
    /* se não há elementos, evitamos divisão por zero retornando 0.0 */
    if (n <= 0) {
        return 0.0;
    }

    /* chama a função soma_vetor para obter a soma dos n elementos */
    double soma = soma_vetor(v, n);

    /* calcula a média: soma / n ; convertemos n para double por clareza */
    double media = soma / (double) n;

    /* devolve a média calculada */
    return media;
}

/* -----------------------------
   main: demonstração e testes
   -----------------------------
   - lê X[20] de entrada padrão (teclado), valida leitura, chama as funções e imprime resultados.
*/
int main(void) {
    /* definimos o tamanho fixo do vetor conforme enunciado */
    const int TAM = 20;

    /* declara o vetor X com TAM elementos do tipo double (reais) */
    double X[TAM];

    /* aviso / instrução ao usuário sobre o que digitar */
    printf("SOMA E MEDIA DE VETOR X[20]\n");
    printf("---------------------------\n");
    printf("Digite 20 numeros reais (separados por espaco ou enter):\n");

    /* laço para ler os 20 valores do usuário, um por posição do vetor */
    for (int i = 0; i < TAM; i = i + 1) {
        /* scanf tenta ler um double e armazena em X[i]; retorna quantos itens leu com sucesso */
        if (scanf("%lf", &X[i]) != 1) {
            /* se a leitura falhar (por exemplo, EOF ou valor não-numérico), avisamos e encerramos */
            printf("Erro na leitura. Certifique-se de digitar numeros reais. Encerrando.\n");
            return 1; /* código de erro não-zero */
        }
    }

    /* chamamos soma_vetor passando o vetor X e o tamanho TAM */
    double soma = soma_vetor(X, TAM);

    /* chamamos media_vetor que por sua vez usa soma_vetor */
    double media = media_vetor(X, TAM);

    /* mostramos os resultados formatados: soma com 6 casas decimais, média com 6 casas */
    printf("\nResultado:\n");
    printf("Soma dos elementos: %.6lf\n", soma);
    printf("Media dos elementos: %.6lf\n", media);

    return 0; /* fim do programa bem-sucedido */
}
