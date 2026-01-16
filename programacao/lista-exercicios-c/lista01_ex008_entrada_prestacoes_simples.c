#include <stdio.h>

int main()
{

    double valor_mercadoria;
    int total_centavos;
    int prestacao_reais;
    int prestacao_centavos;
    int entrada_centavos;

    printf("Informe o valor da mercadoria: R$ ");
    scanf("%lf", &valor_mercadoria);

    /* Converte para centavos*/
    /* multiplicamos por 100 e somamos 0.5 antes do cast para arredondar valores positivos */
    total_centavos = (int)(valor_mercadoria * 100 + 0.5);

    /* Calcula a maior prestacao inteira (em REAIS) tal que 3 * prestacao <= total */
    /* Como estamos em centavos, 3 reais = 300 centavos, dividindo por 300 o resultado em REAIS. */
    prestacao_reais = (int)(total_centavos / 300);  // divisão inteira então já é double

    /* Converte a prestacao para centavos (para somas e subtrações) */
    prestacao_centavos = (int)(prestacao_reais * 100);

    /* Calcula a entrada em centavos: resto após retirar as duas prestações */
    entrada_centavos =(int)(total_centavos - 2 * prestacao_centavos);

    /* Apresenta os resultados convertendo de centavos para reais*/
    printf("Entrada               : R$ %.2lf\n", (double) entrada_centavos / 100);
    printf("Prestacao 2 x de      : R$ %.2lf\n", (double) prestacao_reais);
    
}