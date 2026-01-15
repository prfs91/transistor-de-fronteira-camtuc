#include <stdio.h>   /* declara printf e scanf: necessárias para interação com o usuário */
#include <stdlib.h>  /* boa prática: utilitários (exit, etc.) - incluída por consistência */

/*
  lista02_ex004_tempo_em_segundos.c
  Exercício 4 - Lista 02 (Exercícios com Funções)

  Objetivo:
    Implementar a função:
      long tempo_em_segundos(int horas, int minutos, int segundos);
    que converte um tempo dado em horas, minutos e segundos para o total em segundos.

  Observações / boas práticas:
    - uso de constantes nominais para facilitar entendimento (SEGUNDOS_POR_MINUTO, SEGUNDOS_POR_HORA);
    - validação de entrada: horas >= 0, 0 <= minutos < 60, 0 <= segundos < 60 (opção adotada);
    - retorno de -1 para sinalizar entrada inválida (alternativa a errno ou exceptions).
*/

/* protótipo da função: informa ao compilador a assinatura antes do uso */
long tempo_em_segundos(int horas, int minutos, int segundos);

/* implementação da função que converte HH:MM:SS -> segundos */
long tempo_em_segundos(int horas, int minutos, int segundos) {
    /* constantes explicitas: deixam claro quanto equivale 1 minuto/1 hora em segundos */
    const int SEGUNDOS_POR_MINUTO = 60;         /* 60 segundos em 1 minuto */
    const int SEGUNDOS_POR_HORA = 60 * 60;      /* 3600 segundos em 1 hora */

    /* validação dos parâmetros:
       - horas deve ser >= 0 (duração não negativa)
       - minutos e segundos no intervalo [0,59] para representar tempo convencional
       Se algum valor for inválido, retornamos -1 para sinalizar erro. */
    if (horas < 0) {
        return -1L; /* sinal de erro: horas inválida */
    }
    if (minutos < 0 || minutos >= 60) {
        return -1L; /* sinal de erro: minutos fora do intervalo 0..59 */
    }
    if (segundos < 0 || segundos >= 60) {
        return -1L; /* sinal de erro: segundos fora do intervalo 0..59 */
    }

    /* cálculo: total de segundos = horas*3600 + minutos*60 + segundos
       fazemos cast explícito para long nos produtos para evitar overflow em plataformas onde int seja pequeno */
    long total_segundos = (long) horas * (long) SEGUNDOS_POR_HORA
                         + (long) minutos * (long) SEGUNDOS_POR_MINUTO
                         + (long) segundos;

    /* devolve o total calculado */
    return total_segundos;
}

/* função auxiliar opcional: converte segundos totais de volta para hh:mm:ss
   - demonstra a inversa e ajuda em testes; não era exigida, mas é didática */
void segundos_em_tempo(long total_segundos, int *horas, int *minutos, int *segundos) {
    /* validação simples: total_segundos não pode ser negativo */
    if (total_segundos < 0) {
        /* em caso de erro, definimos todos como zero para evitar lixo nas variáveis apontadas */
        *horas = 0;
        *minutos = 0;
        *segundos = 0;
        return;
    }

    /* calcula horas inteiras (divisão inteira) */
    *horas = (int)(total_segundos / 3600L);

    /* calcula o resto após remover horas e obtém minutos e segundos */
    long resto = total_segundos % 3600L;
    *minutos = (int)(resto / 60L);
    *segundos = (int)(resto % 60L);
}

/* --- main: demonstração interativa da função --- */
int main(void) {
    int h, m, s;                /* variáveis para ler horas, minutos e segundos do usuário */
    long total;                 /* armazenará o total de segundos retornado pela função */

    /* cabeçalho informativo */
    printf("CONVERSAO DE TEMPO PARA SEGUNDOS\n");
    printf("--------------------------------\n");
    printf("Digite o tempo do processo como tres inteiros: horas minutos segundos\n");
    printf("Exemplo: 1 30 15  (para 1 hora, 30 minutos e 15 segundos)\n");
    printf("Digite valores (horas >= 0, 0 <= minutos < 60, 0 <= segundos < 60).\n\n");

    /* laço de leitura para permitir testes repetidos; termina se scanf falhar (EOF) */
    while (1) {
        printf("Entre com horas minutos segundos (ou Ctrl+D/Ctrl+Z para sair): ");

        /* lemos tres inteiros de uma vez; scanf retorna a quantidade de valores lidos com sucesso */
        if (scanf("%d %d %d", &h, &m, &s) != 3) {
            /* se leitura falhar (por exemplo Ctrl+D ou entrada inválida), encerramos educadamente */
            printf("\nLeitura encerrada ou entrada invalida. Saindo.\n");
            break;
        }

        /* chamamos a função que faz a conversão */
        total = tempo_em_segundos(h, m, s);

        /* se a função retornou -1, sinalizamos que os parâmetros são inválidos */
        if (total < 0L) {
            printf("Parametros invalidos. Verifique: horas>=0, 0<=minutos<60, 0<=segundos<60.\n");
            continue; /* volta ao começo do loop pedindo nova entrada */
        }

        /* mostramos o resultado em segundos */
        printf("Total em segundos: %ld\n", total);

        /* demonstramos a inversa opcional para reforçar entendimento */
        int rh, rm, rs;
        segundos_em_tempo(total, &rh, &rm, &rs);
        printf("Isso corresponde a: %d horas, %d minutos, %d segundos\n\n", rh, rm, rs);
    }

    return 0; /* finaliza o programa com sucesso */
}

