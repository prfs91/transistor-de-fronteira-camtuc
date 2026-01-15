#include <stdio.h>

int eh_primo(int n)
{
   if (n < 2) return 0;
   if (n == 2) return 1;
   if (n % 2 == 0) return 0;
   int divisor = 3;

   while (divisor * divisor <= n)
   {
      if (n % divisor == 0) return 0;
      divisor = divisor + 2; //elimina os pares
   }

   return 1;
}

void main ()
{
   int valor;
   int resultado;

   printf("Digite um numero inteiro e positivo: ");
   scanf("%d", &valor);

   resultado = eh_primo(valor);

   if (resultado == 1) printf("%d eh primo.\n", valor);
   else printf("%d nao eh primo.\n", valor);

}