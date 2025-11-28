#include <stdio.h>   // Biblioteca padrão para entrada/saída: printf e scanf
#include <stdlib.h>  // Biblioteca de utilitários (boa prática incluir)
#include <ctype.h>   // para toupper() — facilita tratar 'm' e 'f' minúsculos

/*
  Arquivo: lista01_ex019_pesquisa_idade_sexo_salario.c

  Objetivo:
    Ler repetidamente dados de uma pesquisa: idade (int), sexo (char 'M'/'F') e salário (double).
    Encerrar quando for digitada uma idade negativa.
    Ao final, informar:
      a) média de salário do grupo;
      b) maior e menor idade do grupo;
      c) quantidade de mulheres com salário até R$100,00.

  Estratégia e boas práticas:
    - validar retorno de scanf para entradas básicas;
    - aceitar 'M'/'F' maiúsculo ou minúsculo (usar toupper);
    - usar variáveis descritivas e mensagens amigáveis;
    - tratar o caso sem registros (nenhuma pessoa informada).
*/

int main(void) {
    /* Variáveis para leitura */
    int idade;                    // idade lida do participante
    char sexo;                    // sexo lido do participante ('M' ou 'F')
    double salario;               // salário lido do participante

    /* Estatísticas acumuladas */
    long long total_pessoas = 0;  // contador de quantas pessoas foram registradas
    double soma_salarios = 0.0;   // soma de todos os salários (para calcular média)
    int maior_idade = 0;          // maior idade encontrada (inicializada mais tarde)
    int menor_idade = 0;          // menor idade encontrada (inicializada mais tarde)
    int contador_mulheres_ate_100 = 0; // contador de mulheres com salário <= 100.00

    int primeiro_registro = 1;    // flag para inicializar maior/menor na primeira leitura

    /* Cabeçalho amigável */
    printf("PESQUISA: IDADE, SEXO E SALARIO\n");
    printf("--------------------------------\n");
    printf("Informe dados de cada habitante. Para encerrar, digite uma IDADE negativa.\n\n");

    /* Leitura do primeiro valor de idade (permite entrar no loop ou encerrar imediatamente) */
    printf("Digite a idade (valor negativo encerra): ");
    if (scanf("%d", &idade) != 1) {
        printf("Entrada invalida para idade. Execute novamente e digite um numero inteiro.\n");
        return 1;
    }

    /* Laço principal: repete enquanto a idade lida for não-negativa */
    while (idade >= 0) {

        /* Lê o sexo: usamos " %c" para pular espaços em branco/resíduos de newline */
        printf("Digite o sexo (M/F): ");
        if (scanf(" %c", &sexo) != 1) {
            printf("Entrada invalida para sexo. Encerrando.\n");
            return 1;
        }
        /* Normaliza o caractere para maiúscula para aceitar 'm' e 'f' também */
        sexo = (char) toupper((unsigned char) sexo);

        /* Valida o valor de sexo */
        if (sexo != 'M' && sexo != 'F') {
            printf("Sexo invalido: digite apenas 'M' ou 'F'. Encerrando.\n");
            return 1;
        }

        /* Lê o salário e valida */
        printf("Digite o salario (por exemplo 1234.56): R$ ");
        if (scanf("%lf", &salario) != 1) {
            printf("Entrada invalida para salario. Encerrando.\n");
            return 1;
        }

        /* Validações simples: salário negativo não faz sentido aqui (pode adaptar se desejado) */
        if (salario < 0.0) {
            printf("Salario invalido (negativo). Encerrando.\n");
            return 1;
        }

        /* --- Atualiza estatísticas --- */

        /* Se for o primeiro registro, inicializa maior e menor idade com a primeira idade lida */
        if (primeiro_registro) {
            maior_idade = idade;
            menor_idade = idade;
            primeiro_registro = 0;  // desliga a flag de primeiro registro
        } else {
            /* Atualiza maior e menor idade conforme necessário */
            if (idade > maior_idade) maior_idade = idade;
            if (idade < menor_idade) menor_idade = idade;
        }

        /* Acumula salário e incrementa total de pessoas */
        soma_salarios += salario;
        total_pessoas++;

        /* Conta mulheres com salário até R$100,00 (inclusive) */
        if (sexo == 'F' && salario <= 100.0) {
            contador_mulheres_ate_100++;
        }

        /* Pede a próxima idade para continuar ou finalizar */
        printf("\nDigite a idade (valor negativo encerra): ");
        if (scanf("%d", &idade) != 1) {
            printf("Entrada invalida para idade. Encerrando.\n");
            return 1;
        }
    } /* fim do while */

    /* Após terminar a leitura, mostra resultados ou indica que nenhum dado foi informado */
    if (total_pessoas == 0) {
        printf("\nNenhum participante foi registrado. Nao ha dados para calcular.\n");
    } else {
        double media_salario = soma_salarios / (double) total_pessoas;
        printf("\nRESULTADOS DA PESQUISA\n");
        printf("----------------------\n");
        printf("Total de participantes         : %lld\n", total_pessoas);
        printf("Media de salario do grupo     : R$ %.2lf\n", media_salario);
        printf("Maior idade do grupo          : %d anos\n", maior_idade);
        printf("Menor idade do grupo          : %d anos\n", menor_idade);
        printf("Mulheres com salario ate R$100: %d\n", contador_mulheres_ate_100);
    }

    return 0; /* finaliza programa com sucesso */
}