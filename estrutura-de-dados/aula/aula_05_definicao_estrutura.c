#include<stdio.h>
#include <malloc.h>

struct pessoa
{
    char *nome;
    int idade;
    char *cpf;
};

struct endereco
{
    char *logradouro;
    int numero;
    char *cidade;
    char *cep;
};
    
typedef struct pessoa Pessoa;
typedef struct endereco Endereco;

int main()
{
    Pessoa *p1 = (Pessoa *) malloc(sizeof (Pessoa));

    p1 -> nome = "P1";
    p1 -> idade = 1;
    p1 -> cpf = "000.000.000-55";
    
    Endereco *e1 = (Endereco*) malloc(sizeof(Endereco));

    e1 -> logradouro = "Rua dos Bobos";
    e1 -> numero = 0;
    e1 -> cidade= "Bobolândia";
    e1 -> cep = "00.000-000";


    
}
