#include <stdio.h>
#include<math.h> 

int main (void)
{
  int valor_saque;
  int nota_50 = 0;
  int nota_10 = 0;
  int nota_5 = 0;
  int nota_1 = 0;
  double resto;

  printf("Digite o valor de saque: ");
  scanf("%d", &valor_saque);

  if(valor_saque>=50)
  {
    resto = fmod(valor_saque, 50);
    nota_50 = (valor_saque - resto)/50;
    valor_saque = resto;
    if(nota_50>0)
    {
      printf("- %d unidade(s) de R$ 50,00\n", nota_50);
    }
  }

  if(valor_saque>=10)
  {
    resto = fmod(valor_saque, 10);
    nota_10 = (valor_saque - resto)/10;
    valor_saque = resto;
    if(nota_10>0)
    {
      printf("- %d unidade(s) de R$ 10,00\n", nota_10);
    }
  }

  if(valor_saque>=5)
  {
    resto = fmod(valor_saque, 5);
    nota_5 = (valor_saque - resto)/5;
    nota_1 = resto;
    if(nota_5>0)
    {
      printf("- %d unidade(s) de R$ 5,00\n", nota_5);
    }
    if(nota_1>0)
    {
      printf("- %d unidade(s) de R$ 1,00\n", nota_1);
    }
  }

}