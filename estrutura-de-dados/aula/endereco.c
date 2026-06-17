#include <stdio.h>
#include <malloc.h>

//typedef struct endereco {
//    char *logradouro;
//    int numero;
//    char *cidade;
//    char *cep;
//} Endereco;

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

int main () {
//    Endereco *end1 = (Endereco *) malloc (sizeof (Endereco));
//    end1 -> logradouro = (char *) malloc (101 * sizeof (char));
//    end1 -> cidade = (char *) malloc (101 * sizeof (char));
//    end1 -> cep = (char *) malloc (10 * sizeof (char));
//    printf ("Logradouro?\n");
//    scanf ("%s", end1 -> logradouro);
//    printf ("Numero?\n");
//    scanf ("%d", &(end1 -> numero));
//    getchar ();
//    printf ("Cidade?\n");
//    scanf ("%s", end1 -> cidade);
//    printf ("cep?\n");
//    scanf ("%s", end1 -> cep);
//    printEndereco (end1);

    int N;
    printf ("Quantos enderecos?\n");
    scanf ("%d", &N);
    getchar ();
    Endereco **vEnd = (Endereco **) malloc (N * sizeof (Endereco *));
    for (int i = 0; i < N; i ++) {
        char *logradouro = (char *) malloc (101 * sizeof (char));
        char *cidade = (char *) malloc (101 * sizeof (char));
        char *cep = (char *) malloc (10 * sizeof (char));
        int numero;
        printf ("Logradouro?\n");
        scanf ("%s", logradouro);
        printf ("Numero?\n");
        scanf ("%d", &numero);
        printf ("Cidade?\n");
        scanf ("%s", cidade);
        printf ("Cidade?\n");
        scanf ("%s", cep);
        vEnd [i] = newEndereco (logradouro, numero, cidade, cep);
    }
    
}







