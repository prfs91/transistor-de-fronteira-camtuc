#include <stdio.h>   // biblioteca padrão para entrada/saída (printf, scanf)
#include <stdlib.h>  // biblioteca de utilitários (boa prática incluir)

/*
  Arquivo: lista01_ex008_entrada_prestacoes.c
  Objetivo: dado o valor da mercadoria, calcular:
    - duas prestacoes iguais, inteiras (em reais) e as maiores possiveis,
    - e a entrada (valor restante), obedecendo que entrada >= prestacao.
  Estratégia:
    - trabalhar em centavos (inteiro) para evitar problemas de ponto flutuante,
    - calcular p = floor(total_em_centavos / 300) -> p em REAIS (pois 300 centavos = 3 reais)
      mas para garantir a unidade em reais fazemos: prestacao_reais = total_centavos / 300
    - prestacao_em_centavos = prestacao_reais * 100
    - entrada_em_centavos = total_centavos - 2 * prestacao_em_centavos
*/

int main(void) {
    /* Variáveis */
    double valor_mercadoria;           // valor informado pelo usuário (ex: 302.75)
    long long total_centavos;          // valor em centavos (inteiro) para cálculos exatos
    long long prestacao_reais;         // valor da prestação em REAIS (inteiro)
    long long prestacao_centavos;      // valor da prestação em centavos
    long long entrada_centavos;        // valor da entrada em centavos

    /* Mensagem inicial */
    printf("CALCULO DE ENTRADA E DUAS PRESTACOES\n");
    printf("------------------------------------\n");

    /* Leitura segura do valor da mercadoria */
    printf("Informe o valor da mercadoria (ex: 302.75): R$ ");
    if (scanf("%lf", &valor_mercadoria) != 1) {
        printf("Entrada invalida. Encerrando.\n");
        return 1;
    }

    /* Validação básica: valor não pode ser negativo */
    if (valor_mercadoria < 0.0) {
        printf("Valor invalido: nao pode ser negativo.\n");
        return 1;
    }

    /* Converte para centavos (arredonda corretamente) */
    /* multiplicamos por 100 e somamos 0.5 antes do cast para arredondar valores positivos */
    total_centavos = (long long)(valor_mercadoria * 100.0 + 0.5);

    /* Calcula a maior prestacao inteira (em REAIS) tal que 3 * prestacao <= total */
    /* Como estamos em centavos, 3 reais = 300 centavos.
       prestacao_reais = floor(total_centavos / 300)  (resultado em REAIS) */
    prestacao_reais = total_centavos / 300;  // divisão inteira -> já é floor

    /* Converte a prestacao para centavos (para somas e subtrações) */
    prestacao_centavos = prestacao_reais * 100;

    /* Calcula a entrada em centavos: resto após retirar as duas prestações */
    entrada_centavos = total_centavos - 2 * prestacao_centavos;

    /* Apresenta os resultados convertendo de centavos para reais com 2 casas decimais */
    printf("\nValor da mercadoria: R$ %.2lf\n", (double)total_centavos / 100.0);
    printf("Prestacao (cada uma): R$ %lld,00\n", prestacao_reais);
    printf("Entrada               : R$ %.2lf\n", (double)entrada_centavos / 100.0);

    /* Observação: a prestacao é mostrada como valor inteiro em reais conforme o enunciado */
    return 0;
}