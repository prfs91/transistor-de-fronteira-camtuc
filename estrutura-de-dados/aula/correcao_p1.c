#include <stdio.h>
#include <malloc.h>

struct cliente{
    char *nome;
    char *cpf;
    int mensalidade;
};
typedef struct cliente Cliente;

typedef struct {
    Cliente *cliente;
    int ressarcimento;
} Sinistro;

Cliente *newCliente(char *nome, char **cpf, int mensalidade){
    Cliente *novo = (Cliente *) malloc (sizeof(Cliente));
    novo -> nome = nome;
    //strcpy (novo -> nome, nome);
    novo -> cpf = cpf;
    novo -> mensalidade;
    return novo;
}

Sinistro *newSinistro(Cliente *cliente, int ressarcimento){
    Sinistro * sinistro = (Sinistro *) malloc (sizeof (Sinistro));
    sinistro -> cliente;
    sinistro -> ressarcimento = ressarcimento;
    return sinistro;
}

void freeCliente(Cliente * cliente){
    free (cliente -> nome);
    free (cliente -> cpf);
    //free(cliente -> mensalidade); NÃO É PONTEIRO
    free (cliente);
}

int main (){

    Cliente **clientes = (Cliente*) malloc(5 * sizeof (Cliente *));

    for (int i = 0; i < 5; i++)
    {
        char *nome = (char*) malloc(50 * sizeof(char));
        char *cpf = (char*) malloc(50 * sizeof(char));
        int mensalidade;
        scanf("%s", nome);
        scanf("%s", cpf);
        scanf("%d", mensalidade);
        getchar();
        clientes[i] = newCliente(nome, cpf, mensalidade);
    }

    for (int i = 0; i < 5; i++)
    {
        freeCliente(clientes[i]);
    }
    

}