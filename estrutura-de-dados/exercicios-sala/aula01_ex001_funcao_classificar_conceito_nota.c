#include <stdio.h>

char classificarConceito(float media)
{
    if (media < 5.0) return 'I';
    if (media < 7.0) return 'R';
    if (media < 9.0) return 'B';
    return 'E';
}

int main()
{
    float media;

    scanf("%f", &media);
    printf("%c", classificarConceito(media));

    return 0;
}