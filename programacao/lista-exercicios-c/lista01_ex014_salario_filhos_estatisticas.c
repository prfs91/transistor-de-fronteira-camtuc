#include <stdio.h>   // biblioteca padrão para entrada/saída: printf, scanf
#include <stdlib.h>  // biblioteca de utilidades (boa prática incluir)

/*
  Arquivo: lista01_ex014_salario_filhos_estatisticas.c
  Objetivo:
    Ler repetidamente o salário (double) e o número de filhos (int) de habitantes
    até que seja digitado um salário negativo (sentinela).
    Após a leitura, informar:
      a) média do salário da população;
      b) média do número de filhos;
      c) maior salário;
      d) percentual de pessoas com salário até R$ 100,00.
*/

int main(void) {                                         // início da função principal

    double salario;                                      // variável para ler o salário atual
    int num_filhos;                                      // variável para ler o número de filhos atual

    int total_pessoas = 0;                               // contador de pessoas lidas
    double soma_salarios = 0.0;                          // acumulador da soma dos salários
    long long soma_filhos = 0;                           // acumulador da soma dos filhos (inteiro grande)
    double maior_salario = 0.0;                          // guarda o maior salário encontrado
    int contador_ate_100 = 0;                            // conta quantas pessoas têm salário <= 100.00

    // cabeçalho amigável para o usuário
    printf("PESQUISA: SALARIO E NUMERO DE FILHOS\n");
    printf("-------------------------------------\n");
    printf("Informe o salario (valor negativo encerra a leitura).\n");

    // leitura inicial do primeiro salário (para entrar no laço)
    printf("Digite o salario: R$ ");
    if (scanf("%lf", &salario) != 1) {                   // valida se a leitura do salário foi bem-sucedida
        printf("Entrada invalida para o salario. Encerrando.\n");
        return 1;                                        // encerra com código de erro
    }

    // laço principal: continua enquanto salario for não-negativo
    while (salario >= 0.0) {

        // lê o número de filhos correspondente ao salário informado
        printf("Digite o numero de filhos: ");
        if (scanf("%d", &num_filhos) != 1) {             // valida se a leitura do número de filhos foi bem-sucedida
            printf("Entrada invalida para o numero de filhos. Encerrando.\n");
            return 1;                                    // encerra com código de erro
        }

        // validação simples: não aceitamos número de filhos negativo
        if (num_filhos < 0) {
            printf("Numero de filhos invalido (negativo). Encerrando.\n");
            return 1;
        }

        // acumula dados
        total_pessoas = total_pessoas + 1;               // incrementa o contador de pessoas
        soma_salarios = soma_salarios + salario;         // soma o salário ao acumulador
        soma_filhos = soma_filhos + (long long)num_filhos; // soma o número de filhos

        // verifica se este salário é o maior até agora
        if (total_pessoas == 1 || salario > maior_salario) {
            maior_salario = salario;                     // atualiza o maior salário
        }

        // conta se o salário é até R$ 100,00 (inclusive)
        if (salario <= 100.0) {
            contador_ate_100 = contador_ate_100 + 1;
        }

        // pede o próximo salário (sentinela: negativo encerra)
        printf("\nDigite o salario (ou um valor negativo para encerrar): R$ ");
        if (scanf("%lf", &salario) != 1) {               // valida leitura
            printf("Entrada invalida para o salario. Encerrando.\n");
            return 1;
        }
    } // fim do while

    // após a leitura, se não houver dados, informa que nada foi lido
    if (total_pessoas == 0) {
        printf("\nNenhum dado foi informado. Nada a calcular.\n");
        return 0;                                        // encerra normalmente
    }

    // calcula médias e percentual
    double media_salario = soma_salarios / (double)total_pessoas;   // média dos salários
    double media_filhos = (double)soma_filhos / (double)total_pessoas; // média do número de filhos
    double percentual_ate_100 = ((double)contador_ate_100 * 100.0) / (double)total_pessoas; // percentual

    // exibe resultados com formatação amigável
    printf("\nRESULTADOS DA PESQUISA\n");
    printf("----------------------\n");
    printf("Total de pessoas entrevistadas : %d\n", total_pessoas);
    printf("Media do salario               : R$ %.2lf\n", media_salario);
    printf("Media do numero de filhos      : %.2lf\n", media_filhos);
    printf("Maior salario                  : R$ %.2lf\n", maior_salario);
    printf("Percentual com salario ate R$100: %.2lf%%\n", percentual_ate_100);

    return 0; // finaliza o programa com sucesso
}