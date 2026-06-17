#ifndef LIVRO_H
#define LIVRO_H

#define DISPONIVEL 0
#define EMPRESTADO 1

struct livro
{
    char *titulo;
    char *autor;
    char *isbn;
    char *editora;
    int ano;
    int *emprestado; 
};

typedef struct livro Livro;

Livro *newLivro (char *titulo, char *autor, char *isbn, int *ano, char *editora);

void freeLivro(Livro *livro);

void printLivro (Livro *livro);

#endif