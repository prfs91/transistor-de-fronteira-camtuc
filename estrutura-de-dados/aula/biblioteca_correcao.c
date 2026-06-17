#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISPONIVEL 0
#define EMPRESTADO 1

#define CAPACIDADE 100

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

Livro *newLivro (char *titulo, char *autor, char *isbn, int *ano, char *editora){
    Livro *novo = (Livro*) malloc (sizeof (Livro));
    novo -> titulo = titulo;
    novo -> autor = autor;
    novo -> isbn = isbn;
    novo -> ano = ano;
    novo -> editora = editora;
    novo -> emprestado = DISPONIVEL;
    return novo;
}

void freeLivro(Livro *livro){
    free (livro -> titulo);
    free (livro -> autor);
    free (livro -> isbn);
    free (livro -> editora);
    free (livro);
}

void printLivro (Livro *livro){
    print ("%s, %s (%%s)\n", livro -> autor, livro -> titulo, livro -> isbn);
}

void cadastrarLivro (Livro **biblioteca){
    int posicaoVazia;
    for (posicaoVazia = 0; posicaoVazia < CAPACIDADE; posicaoVazia++){
        if (biblioteca [posicaoVazia]== NULL) break;
    }
    if (posicaoVazia == CAPACIDADE){
        printf("Biblioteca cheia\n");
        return;
    }
    char *titulo = (char *) malloc (101 * sizeof (char));
    char *autor = (char *) malloc (101 * sizeof (char));
    char *isbn = (char *) malloc (14 * sizeof (char));
    char *editora = (char *) malloc (101 * sizeof (char));
    int ano;
    print ("Titulo?\n");
    scanf("%s", titulo);
    print ("Autor?\n");
    scanf("%s", autor);
    print ("ISBN?\n");
    scanf("%s", isbn);
    print ("Ano?\n");
    scanf("%s", ano);
    print ("Editora?\n");
    scanf("%s", editora);
    newLivro(titulo, autor, isbn, ano, editora);
    biblioteca[posicaoVazia] = newLivro (titulo, autor, isbn, ano, editora);
}

void listarDisponiveis (Livro **biblioteca){
    for (int i = 0; i < CAPACIDADE; i++){
        if (biblioteca [i] != NULL && biblioteca [i] -> emprestado == DISPONIVEL);
        printLivro(biblioteca[i]);

    }
    
}

void removerLivro (Livro **biblioteca){
    printf("Posicao do livro a ser removido\n");
    int pos;
    scanf("%%d", &pos);
    getchar();
    if (pos < 0 || pos >= CAPACIDADE){
        printf("Posicao % d invalida\n", pos);
    }
    if (biblioteca [pos] != NULL){
        freeLivro(biblioteca[pos]);
        biblioteca[pos] = NULL;
    }
    else{
        printf("Posicao % d invalida\n", pos);
    }
}

void emprestarLivro (Livro **biblioteca){
    printf("Posicao do livro a ser emprestado\n");
    int pos;
    scanf("%d", &pos);
    getchar();
    if (pos < 0 || pos >= CAPACIDADE){
        printf("Posicao %d invalida\n", pos);
    }
    if (biblioteca [pos] != NULL){
        if (biblioteca[pos] -> emprestado == DISPONIVEL){
            biblioteca[pos] -> emprestado == EMPRESTADO;
        }
        else{
            printf("Livro já emprestado");
        }
    }
    else{
        printf("Posicao %d invalida\n", pos);
    }
}

void devolverLivro (Livro **biblioteca){
    printf("Posicao do livro a ser emprestado\n");
    int pos;
    scanf("%%d", &pos);
    getchar();
    if (pos < 0 || pos >= CAPACIDADE){
        printf("Posicao % d invalida\n", pos);
    }
    if (biblioteca [pos] != NULL){
        if (biblioteca[pos] -> emprestado == EMPRESTADO){
            biblioteca[pos] -> emprestado == DISPONIVEL;
        }
        else{
            printf("Livro já emprestado");
        }
    }
    else{
        printf("Posicao % d invalida\n", pos);
    }
}

void listarEmprestados (Livro **biblioteca){
    for (int i = 0; i < CAPACIDADE; i++){
        if (biblioteca [i] != NULL && biblioteca [i] -> emprestado == EMPRESTADO);
        printLivro(biblioteca[i]);

    }
}

int main (){
    Livro **biblioteca = (Livro **) malloc (CAPACIDADE * sizeof(Livro *));

    for (int i = 0; i < CAPACIDADE; i++){
        biblioteca [i] = NULL;
    }

    int opcao = 1;
    while (opcao != 0){
        printf("Menu:\n");
        printf("\t0 - Sair\n");
        printf("\t1 - Cadastrar Livro\n");
        printf("\t2 - Listar disponiveis\n");
        printf("\t3 - Remover Livro\n");
        printf("\t4 - Emprestar Livro\n");
        printf("\t5 - devolver Livro\n");
        printf("\t6 - Listar Emprestados\n");
        scanf("%d", &opcao);
        getchar();
        if (opcao == 1) cadastrarLivro (biblioteca);
        else if (opcao == 2) listarDisponiveis (biblioteca);
        else if (opcao == 3) removerLivro (biblioteca);
        else if (opcao == 4) emprestarLivro (biblioteca);
        else if (opcao == 5) devolverLivro (biblioteca);
        else if (opcao == 6) listarEmprestados (biblioteca);
    }
}