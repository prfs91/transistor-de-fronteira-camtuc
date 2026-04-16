#include <stdio.h>
#include <malloc.h>

struct livro
{
    char *titulo;
    char *autor;
    char *isbn;
    int ano;
    char *editora;
};
    
typedef struct livro Livro;

