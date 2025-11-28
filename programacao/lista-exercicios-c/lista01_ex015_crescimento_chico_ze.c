#include <stdio.h>   // inclui funções de entrada/saída: printf e scanf (necessário para mostrar resultados)
#include <stdlib.h>  // inclui utilitários (boa prática incluir; não estritamente necessário aqui)

/*
  Arquivo: lista01_ex015_crescimento_chico_ze.c
  Objetivo:
    Calcular quantos anos serão necessários para que Zé (crescendo mais rápido)
    ultrapasse (se torne maior que) Chico.
  Observações de implementação / boas práticas:
    - Trabalhamos em centímetros (inteiros) para evitar imprecisão de ponto flutuante.
    - Usamos constantes para alturas iniciais e taxas de crescimento.
    - Usamos um laço while para contar anos até que Zé seja maior que Chico.
*/

int main(void) {                                   // início da função principal

    /* --- Constantes (valores fixos do problema) --- */
    const int CHICO_ALTURA_INICIAL_CM = 150;       // 1,50 m = 150 cm (valor inicial de Chico)
    const int ZE_ALTURA_INICIAL_CM    = 110;       // 1,10 m = 110 cm (valor inicial de Zé)
    const int CHICO_CRESCIMENTO_CM    = 2;         // Chico cresce 2 cm por ano
    const int ZE_CRESCIMENTO_CM       = 3;         // Zé cresce 3 cm por ano

    /* --- Variáveis mutáveis (serão atualizadas no loop) --- */
    int altura_chico_cm = CHICO_ALTURA_INICIAL_CM; // altura atual de Chico em centímetros
    int altura_ze_cm    = ZE_ALTURA_INICIAL_CM;    // altura atual de Zé em centímetros
    int anos = 0;                                  // contador de anos necessários

    /* Cabeçalho informativo para o usuário */
    printf("CRESCIMENTO: CHICO (1.50m, +2cm/ano) vs ZÉ (1.10m, +3cm/ano)\n");
    printf("Calculando quantos anos até Zé ser maior que Chico...\n\n");

    /* 
       Loop 'enquanto' (while):
       Repetimos os anos até que Zé seja maior que Chico.
       Condição de parada: enquanto (altura_ze_cm <= altura_chico_cm) continuamos.
       Observação: queremos o primeiro ano em que Zé é STRICTLY greater (>).
    */
    while (altura_ze_cm <= altura_chico_cm) {

        /* Avança um ano no tempo */
        anos = anos + 1;

        /* Ambos crescem: somamos seus crescimentos anuais */
        altura_chico_cm = altura_chico_cm + CHICO_CRESCIMENTO_CM;
        altura_ze_cm    = altura_ze_cm + ZE_CRESCIMENTO_CM;

        /* 
           Nota didática: a ordem de atualização (primeiro anos++, depois somar crescimentos)
           não altera o resultado, contanto que a verificação da condição permaneça no while.
        */
    }

    /* Exibe o resultado final: anos necessários e alturas finais (convertidas para metros) */
    printf("Serao necessarios %d ano(s) para que Ze seja maior que Chico.\n", anos);
    printf("Altura final de Chico: %.2f m\n", (double)altura_chico_cm / 100.0);
    printf("Altura final de Ze   : %.2f m\n", (double)altura_ze_cm    / 100.0);

    return 0; // sinaliza ao sistema que o programa terminou com sucesso
}