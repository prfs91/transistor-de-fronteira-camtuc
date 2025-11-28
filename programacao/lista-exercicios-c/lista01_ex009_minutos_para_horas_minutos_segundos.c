#include <stdio.h>    // Biblioteca padrão para entrada e saída (printf, scanf)
#include <stdlib.h>   // Biblioteca com utilitários (boa prática incluir)

/*
  Arquivo: lista01_ex009_minutos_para_horas_minutos_segundos.c

  Objetivo:
    Converter um tempo dado em minutos (com casas decimais) para:
      - horas (parte inteira)
      - minutos (parte inteira remanescente)
      - segundos (obtidos a partir da parte fracionária dos minutos restantes)

  Exemplo:
    Entrada: 145.87 minutos
    Saída:   2 horas, 25 minutos, 52.2 segundos

  Estratégia:
    - 1 hora tem 60 minutos
    - 1 minuto tem 60 segundos
    - Converter minutos inteiros para horas
    - Sobrarão minutos fracionários → separar parte inteira e parte decimal
    - Parte inteira vira "minutos"
    - Parte decimal (ex.: 0.87 min) * 60 = segundos
*/

int main(void) {

    double minutos_totais;           // valor informado pelo usuário (com casas decimais)
    int horas;                       // parte inteira convertida para horas
    int minutos_inteiros;            // parte inteira de minutos após remover horas
    double segundos;                 // segundos derivados da parte fracionária do minuto

    /* Mensagem inicial para o usuário */
    printf("CONVERSAO DE MINUTOS PARA HORAS, MINUTOS E SEGUNDOS\n");
    printf("----------------------------------------------------\n");

    /* Solicita o valor em minutos */
    printf("Digite o tempo em minutos (ex: 145.87): ");
    if (scanf("%lf", &minutos_totais) != 1) {   // valida leitura
        printf("Entrada invalida. Digite um numero.\n");
        return 1;
    }

    /* Validação simples: tempo não pode ser negativo */
    if (minutos_totais < 0.0) {
        printf("Valor invalido: tempo nao pode ser negativo.\n");
        return 1;
    }

    /* 1º passo: converter total de minutos para horas inteiras */
    horas = (int)(minutos_totais / 60.0);  // divisão; somente parte inteira conta para horas

    /* 2º passo: descobrir quantos minutos sobraram depois de tirar as horas */
    double minutos_restantes = minutos_totais - (horas * 60.0);

    /* 3º passo: separar a parte inteira dos minutos restantes */
    minutos_inteiros = (int)minutos_restantes;

    /* 4º passo: transformar a parte fracionária dos minutos restantes em segundos */
    double parte_fracionaria = minutos_restantes - minutos_inteiros;
    segundos = parte_fracionaria * 60.0;

    /* Exibe o resultado com formato adequado */
    printf("\nTempo convertido:\n");
    printf("%d hora(s), %d minuto(s), %.2lf segundo(s)\n",
           horas, minutos_inteiros, segundos);

    return 0;  // finaliza com sucesso
}