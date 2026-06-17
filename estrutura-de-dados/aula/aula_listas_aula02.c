#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TOTAL 256

struct lista_vetor
{
    int tamanho_total;
    int comprimento;
    int *vetor;

};

typedef struct lista_vetor ListaVetor;

ListaVetor *newListaVetor (){
    ListaVetor *novaLista = (ListaVetor**) malloc (sizeof(ListaVetor));
    novaLista -> tamanho_total = TAMANHO_TOTAL;
    novaLista -> comprimento = 0;
    novaLista -> vetor = (int*) malloc (TAMANHO_TOTAL * sizeof(int));
    return novaLista;
}

void freeLista(ListaVetor *lista){
    free (lista -> vetor);
    free (lista);
}

void inserir (ListaVetor *lista, int posicao, int valor){

    // verificar se eu tenho um cadastro reserva
    if (lista -> tamanho_total == lista -> comprimento){
        // caso não tiver criar
        int *novoVetor = (int *) malloc (2 * lista -> tamanho_total * sizeof(int));
        for (int i = 0; i < lista -> tamanho_total; i++){
            novoVetor [i] = lista -> vetor[i]; 
        }
        free(lista -> vetor);
        lista -> tamanho_total *=2;
        lista -> vetor = novoVetor;
    }
    
    
    // deslocar para baixo todos os elementos depois de posição
    for (int i = lista -> comprimento; i < posicao; i++){
        lista -> vetor [i] = lista -> vetor [i - 1];
    }
    // inserir elemento em posição
    lista -> vetor[posicao] =  valor;
    lista -> comprimento ++;
}

/**
void inserir(ListaVetor *lista, int posicao, int valor) {
    // 1. Verificar se a posição é válida e se há espaço
    if (posicao < 0 || posicao > lista->comprimento || lista->comprimento >= lista->tamanho_total) {
        printf("Erro: Posição inválida ou lista cheia.\n");
        return;
    }

    // 2. Deslocar elementos para a direita (de trás para frente)
    for (int i = lista->comprimento; i > posicao; i--) {
        lista->vetor[i] = lista->vetor[i - 1];
    }

    // 3. Inserir o novo valor
    lista->vetor[posicao] = valor;
    lista->comprimento++;
}
**/

void inserirFinal (ListaVetor *lista, int valor){
    inserir (lista, lista -> comprimento, valor);
}

/**
void inserirFinal (ListaVetor *lista, int valor){
    // 1. Verificar se ainda há espaço no vetor
    if (lista->comprimento < lista->tamanho_total) {
        
        // 2. O comprimento atual aponta exatamente para a próxima vaga livre
        lista->vetor[lista->comprimento] = valor;
        
        // 3. Incrementa o comprimento para a próxima inserção
        lista->comprimento++;
    } else {
        printf("Erro: A lista está cheia!\n");
    }
}
**/

int acessar(ListaVetor *lista, int posicao) {
    return lista->vetor[posicao];
}

/**
int acessar(ListaVetor *lista, int posicao) {
    if (posicao < 0 || posicao >= lista->comprimento) {
        return -1; // Ou outro valor de erro
    }
    return lista->vetor[posicao];
}
**/

void remover (ListaVetor *lista, int posicao){
    for (int i = lista -> comprimento; i < posicao; i++){
        lista -> vetor [i] = lista -> vetor [i + 1];
    }
    lista -> comprimento --;
}

/**
void remover (ListaVetor *lista, int posicao){
    // 1. Verificar se a posição existe na lista
    if (posicao < 0 || posicao >= lista->comprimento) {
        printf("Erro: Posição inválida para remoção.\n");
        return;
    }

    // 2. Deslocar os elementos da direita para a esquerda
    // Começamos na posição que queremos remover e trazemos o próximo elemento para ela
    for (int i = posicao; i < lista->comprimento - 1; i++) {
        lista->vetor[i] = lista->vetor[i + 1];
    }

    // 3. Diminuir o comprimento da lista
    lista->comprimento--;
}
**/

void removerFinal (ListaVetor *lista){
    remover(lista, lista -> comprimento - 1);
}

/**
void removerFinal (ListaVetor *lista){
    // 1. Verificar se a lista não está vazia
    if (lista->comprimento > 0) {
        // 2. Apenas decrementamos o comprimento
        lista->comprimento--;
    } else {
        printf("Erro: A lista já está vazia!\n");
    }
}
**/

int main(){
    /**
    int comprimento;
    int **lista = (int**) malloc(256 * sizeof(int));
    **/
    ListaVetor *lista = newListaVetor();
    for(int i = 0; i<10; i++){
        inserirFinal(lista, i);
    }
    remover(lista, 3);
    inserir(lista, 3,50);
    for (int i = 0; i < lista -> comprimento; i++){

    }
    

    
}