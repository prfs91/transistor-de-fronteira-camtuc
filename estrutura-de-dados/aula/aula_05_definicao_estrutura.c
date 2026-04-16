#include<stdio.h>
#include <malloc.h>

struct endereco
{
    char *logradouro;
    int numero;
    char *cidade;
    char *cep;
};
    
typedef struct endereco Endereco;

struct pessoa
{
    char *nome;
    int idade;
    char *cpf;
    char *email;
    Endereco *endereco;
};

typedef struct pessoa Pessoa;

Pessoa *newPessoa (char *nome, int idade, char *cpf, char *email, Endereco *endereco){

    Pessoa *nova = (Pessoa *) malloc(sizeof(Pessoa));

    nova -> nome = nome;
    nova -> idade = idade;
    nova -> cpf = cpf;
    nova -> email = email;
    nova -> endereco = endereco;

    return nova;

}

void printPessoa (Pessoa *pes){
    printf("Nome: %s\n", pes -> nome);
    printf("Idade: %d\n", pes -> idade);
    printf("CPF: %s\n", pes -> cpf);
    printf("Email: %s\n", pes -> email);
}



Endereco *newEndereco (char *logradouro, int numero, char *cidade, char *cep){

    Endereco *novo = (Endereco *) malloc(sizeof(Endereco));

    novo -> logradouro = logradouro;
    novo -> numero = numero;
    novo -> cidade = cidade;
    novo -> cep = cep;

    return novo;

}

void printEndereco (Endereco *end){
    printf("%s, %d\n", end -> logradouro, end -> numero);
    printf("%s, %s\n", end -> cidade, end -> cep);
}






int main()
{

    Endereco *e1 = newEndereco("Rua Y", 34, "Cidade 2", "14789-789");

    Pessoa *p1 = newPessoa("Roberta", 34, "000.000.000-0", "ret@hotmail.com", e1);

    printf("%s", p1 -> endereco -> logradouro);

    printf("Digite a quantidades de endereco que deseja armazenar: ");
    int qtd = scanf("%d", &qtd);

    
    Pessoa ** pessoas = (Pessoa **) malloc (qtd * sizeof (Pessoa *));

    
}
