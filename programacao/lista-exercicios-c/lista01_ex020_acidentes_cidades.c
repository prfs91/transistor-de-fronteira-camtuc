#include <stdio.h>    // biblioteca padrão para entrada/saída (printf, scanf)
#include <stdlib.h>   // biblioteca de utilitários (boa prática incluir)
#include <string.h>   // para manipulação de strings (strcmp, strcpy)
#include <ctype.h>    // para toupper, limpeza de input opcional

/*
  Arquivo: lista01_ex020_acidentes_cidades.c

  Objetivo:
    Ler dados de 200 cidades (código, estado, nº veículos, nº acidentes) e informar:
      a) maior e menor índice de acidentes e as cidades correspondentes;
      b) média de veículos nas 200 cidades;
      c) média de acidentes entre as cidades do Rio Grande do Sul (estado "RS").

  Observações sobre "índice de acidentes":
    - Aqui adotamos como índice: (número de acidentes) / (número de veículos) * 1000
      Isto fornece acidentes por 1000 veículos, uma unidade fácil de interpretar.
    - Caso uma cidade tenha 0 veículos informados, evitamos divisão por zero e tratamos
      o índice como indefinido; nestes casos, pulamos a comparação de índice e avisamos.
*/

int main(void) {
    /* ----- Constantes e parâmetros ----- */
    const int TOTAL_CIDADES = 200;            // quantidade de cidades a processar conforme enunciado
    const int ESTADO_MAX_LEN = 3;             // tamanho do vetor para armazenar o código do estado (ex: "RS" + '\0')

    /* ----- Variáveis para leitura de cada cidade ----- */
    int codigo_cidade;                         // código da cidade lido do usuário
    char estado[ESTADO_MAX_LEN];               // código do estado (ex: "RS", "SP")
    long long num_veiculos;                    // número de veículos de passeio (inteiro, pode ser grande)
    long long num_acidentes;                   // número de acidentes com vítimas (inteiro)

    /* ----- Variáveis para calcular resultados solicitados ----- */
    double maior_indice = -1.0;                // guarda o maior índice encontrado (inicia -1 para marcar inexistente)
    int codigo_maior_indice = -1;              // código da cidade com maior índice
    char estado_maior_indice[ESTADO_MAX_LEN];  // estado da cidade com maior índice

    double menor_indice = 1e308;               // guarda o menor índice (iniciamos com valor muito grande)
    int codigo_menor_indice = -1;              // código da cidade com menor índice
    char estado_menor_indice[ESTADO_MAX_LEN];  // estado da cidade com menor índice

    long long soma_veiculos = 0LL;             // soma acumulada de veículos (para média total)
    long long soma_acidentes_rs = 0LL;         // soma acumulada de acidentes nas cidades do RS
    int contador_cidades_rs = 0;               // contador de quantas cidades são do RS

    int leitura_ok;                            // variável auxiliar para checar retorno de scanf

    /* ----- Cabeçalho e instruções ao usuário ----- */
    printf("ESTATISTICA DE ACIDENTES - %d CIDADES\n", TOTAL_CIDADES);
    printf("Voce devera informar para cada cidade: codigo, estado (ex: RS),\n");
    printf("numero de veiculos e numero de acidentes com vitimas (todos inteiros).\n");
    printf("Se alguma entrada estiver invalida, o programa encerrara com mensagem.\n\n");

    /* ----- Loop principal: ler dados de TOTAL_CIDADES cidades ----- */
    for (int i = 0; i < TOTAL_CIDADES; i++) {   // repete exatamente TOTAL_CIDADES vezes
        printf("Cidade %d de %d\n", i+1, TOTAL_CIDADES);

        /* Leitura do codigo da cidade */
        printf("  Codigo da cidade (inteiro): ");
        leitura_ok = scanf("%d", &codigo_cidade);
        if (leitura_ok != 1) {                  // valida se scanf leu um inteiro
            printf("  ERRO: entrada invalida para codigo. Encerrando.\n");
            return 1;
        }

        /* Leitura do estado (string curta) */
        printf("  Estado (ex: RS, SP) : ");
        leitura_ok = scanf("%2s", estado);      // %2s limita leitura a 2 caracteres, deixando espaco para '\0'
        if (leitura_ok != 1) {
            printf("  ERRO: entrada invalida para estado. Encerrando.\n");
            return 1;
        }
        /* Normaliza para maiusculas por segurança (aceita 'rs' ou 'Rs') */
        estado[0] = (char) toupper((unsigned char) estado[0]);
        estado[1] = (char) toupper((unsigned char) estado[1]);

        /* Leitura do numero de veiculos */
        printf("  Numero de veiculos (inteiro): ");
        leitura_ok = scanf("%lld", &num_veiculos);
        if (leitura_ok != 1 || num_veiculos < 0LL) { // valida e impede numeros negativos
            printf("  ERRO: entrada invalida para numero de veiculos. Encerrando.\n");
            return 1;
        }

        /* Leitura do numero de acidentes */
        printf("  Numero de acidentes (inteiro): ");
        leitura_ok = scanf("%lld", &num_acidentes);
        if (leitura_ok != 1 || num_acidentes < 0LL) { // valida e impede numeros negativos
            printf("  ERRO: entrada invalida para numero de acidentes. Encerrando.\n");
            return 1;
        }

        /* ----- Acumula soma de veiculos para a média nacional ----- */
        soma_veiculos += num_veiculos;

        /* ----- Acumula dados para RS ----- */
        if (estado[0] == 'R' && estado[1] == 'S') {  // verifica se o estado informado é "RS"
            soma_acidentes_rs += num_acidentes;
            contador_cidades_rs++;
        }

        /* ----- Calcula o indice de acidentes para esta cidade (evita divisao por zero) ----- */
        if (num_veiculos == 0LL) {
            /* Se não há veículos informados, o índice seria indefinido; avisamos e não comparamos */
            printf("  Aviso: numero de veiculos = 0 -> indice de acidentes indefinido; pulando comparacao.\n");
        } else {
            /* índice em acidentes por 1000 veículos = (acidentes / veiculos) * 1000.0 */
            double indice = ((double) num_acidentes / (double) num_veiculos) * 1000.0;

            /* atualiza o maior índice se aplicável */
            if (indice > maior_indice) {
                maior_indice = indice;
                codigo_maior_indice = codigo_cidade;
                strcpy(estado_maior_indice, estado);  // guarda o estado correspondente
            }

            /* atualiza o menor índice se aplicável */
            if (indice < menor_indice) {
                menor_indice = indice;
                codigo_menor_indice = codigo_cidade;
                strcpy(estado_menor_indice, estado);
            }
        }

        printf("\n"); /* linha em branco para separar entradas */
    } /* fim do for */

    /* ----- Calculos finais e exibicao ----- */

    /* a) maior e menor indice (verifica se alguma comparacao foi possível) */
    printf("RESULTADOS GERAIS\n");
    printf("-----------------\n");

    if (codigo_maior_indice == -1) {   // nenhum índice válido foi calculado (todas cidades tiveram 0 veículos)
        printf("Nao foi possivel determinar maior/menor indice: todas as cidades tinham num_veiculos = 0.\n");
    } else {
        printf("Maior indice de acidentes: %.4f (acidentes por 1000 veiculos) - Cidade codigo %d, Estado %s\n",
               maior_indice, codigo_maior_indice, estado_maior_indice);
        printf("Menor  indice de acidentes: %.4f (acidentes por 1000 veiculos) - Cidade codigo %d, Estado %s\n",
               menor_indice, codigo_menor_indice, estado_menor_indice);
    }

    /* b) media de veículos nas 200 cidades */
    {
        double media_veiculos = (double) soma_veiculos / (double) TOTAL_CIDADES;
        printf("\nMedia de veiculos nas %d cidades: %.2f veiculos\n", TOTAL_CIDADES, media_veiculos);
    }

    /* c) media de acidentes entre as cidades do RS (verifica se existiram cidades RS) */
    if (contador_cidades_rs == 0) {
        printf("\nNao houve cidades do RS registradas; media de acidentes para RS nao pode ser calculada.\n");
    } else {
        double media_acidentes_rs = (double) soma_acidentes_rs / (double) contador_cidades_rs;
        printf("\nMedia de acidentes (com vitimas) entre as cidades do RS: %.2f acidentes por cidade (media de %d cidades)\n",
               media_acidentes_rs, contador_cidades_rs);
    }

    return 0; /* encerra o programa com sucesso */
}