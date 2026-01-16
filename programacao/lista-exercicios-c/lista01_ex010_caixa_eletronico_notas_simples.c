#include <stdio.h>

int main() {

    int valor;
    int resto;

    int n200, n100, n50, n20, n10, n5, n2, n1;

    printf("Digite o valor do saque: R$ ");
    scanf("%d", &valor);

    resto = valor;

    // ---- NOTA DE 200 REAIS ----
    if (resto >= 200)
    {          // Verifica se é possível usar ao menos uma nota de 200
        n200 = resto / 200;      // Calcula quantas notas de 200 cabem no valor restante
        resto = resto % 200;     // Atualiza o valor restante após retirar essas notas
    }
    else
    {
        n200 = 0;                // Caso não caiba nenhuma nota de 200
    }

    // ---- NOTA DE 100 REAIS ----
    if (resto >= 100)
    {          // Verifica se é possível usar ao menos uma nota de 100
        n100 = resto / 100;      // Calcula quantas notas de 100 cabem
        resto = resto % 100;     // Atualiza o restante
    }
    else
    {
        n100 = 0;                // Nenhuma nota de 100 será usada
    }

    // ---- NOTA DE 50 REAIS ----
    if (resto >= 50)
    {           // Verifica se é possível usar nota de 50
        n50 = resto / 50;        // Calcula quantas notas de 50 cabem
        resto = resto % 50;      // Atualiza o restante
    }
    else
    {
        n50 = 0;                 // Nenhuma nota de 50
    }

    // ---- NOTA DE 20 REAIS ----
    if (resto >= 20)
    {           // Verifica se é possível usar nota de 20
        n20 = resto / 20;        // Calcula quantas notas de 20 cabem
        resto = resto % 20;      // Atualiza o restante
    }
    else
    {
        n20 = 0;                 // Nenhuma nota de 20
    }

    // ---- NOTA DE 10 REAIS ----
    if (resto >= 10)
    {           // Verifica se é possível usar nota de 10
        n10 = resto / 10;        // Calcula quantas notas de 10 cabem
        resto = resto % 10;      // Atualiza o restante
    }
    else
    {
        n10 = 0;                 // Nenhuma nota de 10
    }

    // ---- NOTA DE 5 REAIS ----
    if (resto >= 5)
    {            // Verifica se é possível usar nota de 5
        n5 = resto / 5;          // Calcula quantas notas de 5 cabem
        resto = resto % 5;       // Atualiza o restante
    }
    else
    {
        n5 = 0;                  // Nenhuma nota de 5
    }

    // ---- NOTA DE 2 REAIS ----
    if (resto >= 2)
    {            // Verifica se é possível usar nota de 2
        n2 = resto / 2;          // Calcula quantas notas de 2 cabem
        resto = resto % 2;       // Atualiza o restante
    }
    else
    {
        n2 = 0;                  // Nenhuma nota de 2
    }

    // ---- NOTA DE 1 REAL ----
    if (resto >= 1)
    {            // Verifica se ainda resta algum valor
        n1 = resto / 1;          // Calcula quantas notas de 1 real são necessárias
        resto = resto % 1;       // Atualiza o restante (sempre ficará 0)
    }
    else
    {
        n1 = 0;                  // Nenhuma moeda de 1 real
    }

    // Exibe o resultado final
    printf("\nDistribuicao otima:\n");

    // Imprime apenas as notas/moedas que foram utilizadas
    if (n200 > 0) printf("%d nota(s) de R$ 200\n", n200);
    if (n100 > 0) printf("%d nota(s) de R$ 100\n", n100);
    if (n50 > 0)  printf("%d nota(s) de R$ 50\n", n50);
    if (n20 > 0)  printf("%d nota(s) de R$ 20\n", n20);
    if (n10 > 0)  printf("%d nota(s) de R$ 10\n", n10);
    if (n5 > 0)   printf("%d nota(s) de R$ 5\n", n5);
    if (n2 > 0)   printf("%d nota(s) de R$ 2\n", n2);
    if (n1 > 0)   printf("%d nota(s) de R$ 1\n", n1);

}