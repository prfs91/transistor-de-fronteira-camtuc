/******************************************************************************
 * IDENTIFICAÇÃO:
 * Aluna: Pamella Roberta Ferreira da Silva
 * Professor: Bruno Merlin
 * Disciplina: Estrutura de Dados
 * Assunto: Estruturas de Dados em C (Struct, Ponteiros e Alocação Dinâmica)
 ******************************************************************************
 * ATIVIDADE
 * Criar o sistema de gestão de Biblioteca com as características a seguir:
 * 
 * – A biblioteca administra livros que são caracterizados por:
 *   • Título (max. 100 caracteres)
 *   • Autor (max. 50 caracteres)
 *   • ISBN (11 caracteres)
 *   • Ano de edição
 *   • Editora (max. 50 caracteres)
 *   • Estado (emprestado ou não)
 * 
 * – A biblioteca tem uma capacidade máxima de 100 livros. Os 100 itens do 
 *   vetor são inicializados com o valor NULL.
 * 
 * – O sistema oferece as operações de:
 *   • Cadastrar um livro: O livro é inserido no primeiro espaço livre
 *   • Listar os livros disponíveis
 *   • Remover um livro (selecionado indicando o índice no vetor)
 *   • Emprestar um livro (selecionado indicando o índice no vetor)
 *   • Devolver um livro (selecionado indicando o índice no vetor)
 *   • Listar os livros emprestados
 * 
 * – Obs: Administrar os casos de erro para livros inexistentes ou removidos.
 * – As operações serão realizadas através de um menu.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_MAXIMA_ACERVO 100
#define TAMANHO_TITULO 101
#define TAMANHO_AUTOR 51
#define TAMANHO_ISBN 12
#define TAMANHO_EDITORA 51

#define ESTADO_DISPONIVEL 0
#define ESTADO_EMPRESTADO 1

typedef struct
{
    char titulo[TAMANHO_TITULO];
    char autor[TAMANHO_AUTOR];
    char isbn[TAMANHO_ISBN];
    char editora[TAMANHO_EDITORA];
    int ano_edicao;
    int situacao_emprestimo; 
} Livro;

void limparTela()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("Tela limpa!\n");
}

void limparBuffer()
{
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF);
}

void aguardar()
{
    printf("\nPressione ENTER para continuar...");
    limparBuffer();
    getchar();
}

Livro** buscarEspacoLivre(Livro** vetor)
{
    for (int i = 0; i < CAPACIDADE_MAXIMA_ACERVO; i++)
    {
        if (vetor[i] == NULL) return &vetor[i];
    }
    return NULL;
}

void cadastrarLivro(Livro** vetor)
{
    Livro** slot = buscarEspacoLivre(vetor);
    if (slot == NULL)
    {
        printf("\nERRO: Acervo lotado!\n");
    }
    else
    {
        *slot = (Livro*) malloc(sizeof(Livro));
        printf("\n--- CADASTRO DE LIVRO ---\n");
        printf("Titulo: ");  scanf(" %[^\n]s", (*slot)->titulo);
        printf("Autor: ");   scanf(" %[^\n]s", (*slot)->autor);
        printf("ISBN (11 digitos): "); scanf("%s", (*slot)->isbn);
        printf("Editora: "); scanf(" %[^\n]s", (*slot)->editora);
        printf("Ano (4 digitos): "); scanf("%d", &(*slot)->ano_edicao);
        
        (*slot)->situacao_emprestimo = ESTADO_DISPONIVEL;
        printf("\n>>> Livro cadastrado com sucesso!\n");
    }
    aguardar();
}

void listarLivros(Livro** vetor, int filtro)
{
    int encontrou = 0;
    char* status_txt = (filtro == ESTADO_DISPONIVEL) ? "DISPONIVEIS" : "EMPRESTADOS";

    printf("\n--- LISTAGEM DE LIVROS %s ---\n", status_txt);
    printf("%-4s | %-30s | %-20s | %-11s | %-4s | %-15s\n", "ID", "TITULO", "AUTOR", "ISBN", "ANO", "EDITORA");
    printf("----------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < CAPACIDADE_MAXIMA_ACERVO; i++)
    {
        if (vetor[i] != NULL && vetor[i]->situacao_emprestimo == filtro)
        {
            printf("[%02d] | %-30.30s | %-20.20s | %-11s | %04d | %-15.15s\n", 
                    i, vetor[i]->titulo, vetor[i]->autor, vetor[i]->isbn, vetor[i]->ano_edicao, vetor[i]->editora);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhum livro encontrado.\n");
    aguardar();
}

void gerenciarLivro(Livro** vetor, int opcao)
{
    int id;
    printf("\nIndice do livro: ");
    if (scanf("%d", &id) != 1)
    {
        limparBuffer();
        return;
    }

    if (id < 0 || id >= CAPACIDADE_MAXIMA_ACERVO || vetor[id] == NULL)
    {
        printf("\nERRO: Indice invalido ou livro inexistente!\n");
    }
    else
    {
        if (opcao == 6)
        { // REMOVER
            free(vetor[id]);
            vetor[id] = NULL;
            printf("\n>>> Livro removido do acervo!\n");
        } 
        else if (opcao == 4)
        { // EMPRESTAR
            if (vetor[id]->situacao_emprestimo == ESTADO_EMPRESTADO)
            {
                printf("\nAVISO: Este livro ja esta emprestado!\n");
            }
            else
            {
                vetor[id]->situacao_emprestimo = ESTADO_EMPRESTADO;
                printf("\n>>> Emprestimo registrado com sucesso!\n");
            }
        } 
        else if (opcao == 5)
        { // DEVOLVER
            if (vetor[id]->situacao_emprestimo == ESTADO_DISPONIVEL)
            {
                printf("\nAVISO: Este livro ja esta na biblioteca (disponivel)!\n");
            }
            else
            {
                vetor[id]->situacao_emprestimo = ESTADO_DISPONIVEL;
                printf("\n>>> Devolucao registrada com sucesso!\n");
            }
        }
    }
    aguardar();
}

int main()
{
    Livro* biblioteca[CAPACIDADE_MAXIMA_ACERVO] = {NULL};
    int opcao = -1;

    while (opcao != 0)
    {
        printf("\n=== GESTAO DE BIBLIOTECA ===\n");
        printf("1. Cadastrar  2. Disponiveis  3. Emprestados\n");
        printf("4. Emprestar  5. Devolver     6. Remover\n");
        printf("7. Limpar Tela                0. Sair\n");
        printf("----------------------------\nOpcao: ");
        
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }

        switch (opcao) {
            case 1: cadastrarLivro(biblioteca); break;
            case 2: listarLivros(biblioteca, ESTADO_DISPONIVEL); break;
            case 3: listarLivros(biblioteca, ESTADO_EMPRESTADO); break;
            case 4: 
            case 5: 
            case 6: gerenciarLivro(biblioteca, opcao); break;
            case 7: limparTela(); break;
            case 0: 
                for(int i=0; i<CAPACIDADE_MAXIMA_ACERVO; i++) if(biblioteca[i]) free(biblioteca[i]);
                printf("\nSaindo...\n");
                break;
            default: printf("\nOpcao invalida!\n");
        }
    }
}