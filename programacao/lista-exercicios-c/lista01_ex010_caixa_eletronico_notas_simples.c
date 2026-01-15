#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int valor_saque;

    // Lista das notas e valores, da maior para a menor (fundamental para o método guloso).
    int valores_cedulas[] = {200, 100, 50, 20, 10, 5, 2, 1};

    // Vetor que armazenará quantas notas/moedas de cada valor serão usadas.
    int quantidade[8] = {0};

    int total_tipos = 8;  // Quantidade de tipos de cédulas/moedas existentes.

    // ---- MENSAGENS INICIAIS ----
    printf("CAIXA ELETRONICO - DISTRIBUICAO OTIMA DE NOTAS E MOEDAS\n");
    printf("Cédulas utilizadas: 200, 100, 50, 20, 10, 5, 2 reais\n");
    printf("Moeda utilizada : 1 real\n");
    printf("-----------------------------------------------\n");

    // ---- LEITURA DO VALOR ----
    printf("Digite o valor do saque (somente reais, inteiro): R$ ");
    if (scanf("%d", &valor_saque) != 1) {     // Se scanf não ler exatamente 1 valor, houve erro.
        printf("Erro: entrada invalida. Digite um numero inteiro.\n");
        return 1;  // Retorna 1 porque o programa terminou com erro.
    }

    // ---- VALIDAÇÃO DO VALOR ----
    if (valor_saque < 0) {          // Não existe saque negativo.
        printf("Erro: o valor nao pode ser negativo.\n");
        return 1;
    }

    // ---- PROCESSO DE SEPARAR NOTAS/MOEDAS ----
    int restante = valor_saque;     // "restante" é quanto ainda falta distribuir.

    // Percorre cada tipo de nota/moeda começando da maior.
    for (int i = 0; i < total_tipos; i++) {

        int valor_da_cedula = valores_cedulas[i];  // Valor da cédula atual (ex.: 200, depois 100...)

        // Se cabe ao menos uma dessa cédula:
        if (restante >= valor_da_cedula) {

            // Quantas cabem? Divisão inteira responde.
            quantidade[i] = restante / valor_da_cedula;

            // Atualiza quanto ainda falta distribuir (resto da divisão).
            restante = restante % valor_da_cedula;

        } else {
            quantidade[i] = 0;   // Não cabe nenhuma unidade dessa nota.
        }
    }

    // ---- EXIBIÇÃO DO RESULTADO ----
    printf("\nValor solicitado: R$ %d\n", valor_saque);
    printf("Distribuicao otima:\n");

    for (int i = 0; i < total_tipos; i++) {

        // Só imprime se existir ao menos uma nota/moeda daquele tipo.
        if (quantidade[i] > 0) {
            printf("- %d unidade(s) de R$ %d\n",
                   quantidade[i], valores_cedulas[i]);
        }
    }

    // Teoricamente, nunca sobra resto porque temos moeda de 1 real.
    if (restante != 0) {
        printf("\nAviso: sobrou R$ %d nao distribuido. (Isso nao deve ocorrer.)\n",
               restante);
    }

    return 0;  // Termina o programa com sucesso.
}