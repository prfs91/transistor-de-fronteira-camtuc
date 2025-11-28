#include<stdio.h>

int main(void)
{
    
    int valor;
    
    printf("Informe o valor: ");
    scanf("%d", &valor);

    // estrutura de controle de fluxo while()
    while (valor!=0)
    {
        printf("O valor lido foi %d\n", valor);
        printf("Informe novamente o valor: ");
        scanf("%d", &valor);
    }

}