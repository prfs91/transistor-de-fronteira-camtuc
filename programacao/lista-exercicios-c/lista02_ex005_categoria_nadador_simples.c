#include <stdio.h>

void categoria_nadador(int idade, int *categoria)
{
    if (idade >= 5 && idade <= 7) *categoria = 1;
    else if (idade >= 8 && idade <= 10) *categoria = 2;
    else if (idade >= 11 && idade <= 13) *categoria = 3;
    else if (idade >= 14 && idade <= 17) *categoria = 4;
    else if (idade >= 18) *categoria = 5;
    else *categoria = 0;
}

void main()
{
    int idade, categoria;

    printf("Digite a idade do nadador: ");
    scanf("%d", &idade);
    
    categoria_nadador(idade, &categoria);

    if (categoria == 0)
        printf("Idade %d -> idade inválida ou sem categoria definida.\n", idade);
    else
        printf("Idade %d -> categoria %d.\n", idade, categoria);
}
