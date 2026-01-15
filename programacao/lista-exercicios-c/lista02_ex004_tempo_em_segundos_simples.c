#include <stdio.h>

int tempo_em_segundos(int horas, int minutos, int segundos)
{
    const int SEGUNDOS_POR_MINUTO = 60;
    const int SEGUNDOS_POR_HORA = 3600;
    
    int total_segundos = horas * SEGUNDOS_POR_HORA + minutos * SEGUNDOS_POR_MINUTO + segundos;

    return total_segundos;
}

void main()
{
    int h, m, s, total;

    printf("Digite a(s) hora(s) (horas >= 0): ");
    scanf("%d", &h);
    printf("Digite o(s) minuto(s) (0 <= minutos < 60): ");
    scanf("%d", &m);
    printf("Digite o(s) segundo(s) (0 <= segundos < 60): ");
    scanf("%d",&s);
    
    total = tempo_em_segundos(h, m, s);

    printf("Tempo total em segundos: %d\n", total);

}

