#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    double minutos_totais;
    int horas;
    int minutos_inteiros;
    double segundos;

    printf("Digite o tempo em minutos (ex: 145.87): ");
    scanf("%lf", &minutos_totais);

    /* converte total de minutos para horas inteiras */
    horas = (int)(minutos_totais / 60);  // somente parte inteira conta para horas

    /* descobre quantos minutos sobraram depois de tirar as horas */
    double minutos_restantes = minutos_totais - (horas * 60);

    /* separa a parte inteira dos minutos restantes */
    minutos_inteiros = (int)minutos_restantes;

    /* transforma a parte fracionária dos minutos restantes em segundos */
    double parte_fracionaria = minutos_restantes - minutos_inteiros;
    segundos = parte_fracionaria * 60;

    printf("\nTempo convertido:\n");
    printf("%d hora(s), %d minuto(s), %.2lf segundo(s)\n",
           horas, minutos_inteiros, segundos);
}