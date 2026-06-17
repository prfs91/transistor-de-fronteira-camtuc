#include <malloc.h>
#include <stdio.h>

#include <stdio.h>
#include <malloc.h>

struct endereco {
    char *logradouro;
    int numero;
    char *cidade;
    char *cep;
};
typedef struct endereco Endereco;

Endereco *newEndereco (char *logradouro, int numero, char *cidade, char *cep) {
    Endereco *novo = (Endereco *) malloc (sizeof (Endereco));
    novo -> logradouro = logradouro;
    novo -> numero = numero;
    novo -> cidade = cidade;
    novo -> cep = cep;
    return novo;
}

void printEndereco (Endereco *end) {
    printf ("%s, %d\n", end -> logradouro, end -> numero);
    printf ("%s %s\n", end -> cep, end -> cidade);
}

struct pessoa {
    char *nome;
    int idade;
    char *cpf;
    char *email;
    Endereco *endereco;
};
typedef struct pessoa Pessoa;

Pessoa *newPessoa (char *nome, int idade, char *cpf, char *email, Endereco *endereco) {
    Pessoa *nova = (Pessoa *) malloc (sizeof (Pessoa));
    nova -> nome = nome;
    nova -> idade = idade;
    nova -> cpf = cpf;
    nova -> email = email;
    nova -> endereco = endereco;
    return nova;
}

void freePessoa (Pessoa *removida){
    free(removida -> nome);
    free(removida -> idade);
    free(removida -> cpf);
    free(removida -> email);
    freeEndereco(removida);
    free(removida);
}

void freeEndereco(Endereco *removido){
    free(removido -> logradouro);
    free(removido -> numero);
    free(removido -> cidade);
    free(removido -> cep);
    free(removido);
}

int main () {
//    Pessoa *p1 = (Pessoa *) malloc (sizeof (Pessoa)); 
//    Pessoa *p2 = (Pessoa *) malloc (sizeof (Pessoa)); 
//    p1 -> nome = "P1";
//    p1 -> idade = 1;
//    p1 -> cpf = "555.555.555-55";
//    p2 -> nome = "P2";
//    p2 -> idade = 2;
//    p2 -> cpf = "666.555.555-55";
    // Dev 1
    Endereco *end1 = newEndereco ("Rua1", 1, "Cidade1", "Cep1");
    Pessoa *p1 = newPessoa ("P1", 1, "555.555.555-55", "email@gmail.com", end1);
    printf ("%s", p1 -> endereco -> logradouro);
//    Endereco *e = p1 -> endereco;
//    printf ("%s", e -> logradouro);
//
    free();
    // Dev 2
    Pessoa *p2 = newPessoa ("P2", 2, "666.555.555-55", "email2@gmail.com");
} 
