#include <stdio.h>

int main()
{

    const int TOTAL_VALORES = 8;
    int cont = 0;
    int qtd_negativos = 0;
    double valor;
    
    while (cont < TOTAL_VALORES)
    {

        printf("Digite o valor #%d: ", cont + 1);
        scanf("%lf", &valor);

        if (valor < 0)
        {
            qtd_negativos = qtd_negativos + 1;
        }

        cont = cont + 1;
    }

    printf("\nForam lidos %d valor(es) negativos entre os %d informados.\n",
           qtd_negativos, TOTAL_VALORES);

}