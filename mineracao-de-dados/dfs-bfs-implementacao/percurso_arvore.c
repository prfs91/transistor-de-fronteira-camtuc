#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

// --- CONFIGURAÇÕES ESTÉTICAS ---
#define RESET           "\033[0m"
#define VERDE           "\033[1;32m"
#define AMARELO         "\033[1;33m"
#define CIANO           "\033[1;36m"
#define VERMELHO        "\033[1;31m"
#define DIVISOR         "---------------------------------------------------"

typedef struct No {
    char identificador;
    struct No** ponteiro_filhos;
    int quantidade_filhos;
} No;

typedef void (*FuncaoBusca)(No*, char, char*, int*);

// --- GESTÃO DE MEMÓRIA ---

No* criar_no(char id) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return NULL;
    novo->identificador = id;
    novo->ponteiro_filhos = NULL;
    novo->quantidade_filhos = 0;
    return novo;
}

void conectar_nos(No* pai, No* filho) {
    if (!pai || !filho) return;
    int nova_qtd = pai->quantidade_filhos + 1;
    No** temp = (No**)realloc(pai->ponteiro_filhos, nova_qtd * sizeof(No*));
    if (temp) {
        pai->ponteiro_filhos = temp;
        pai->quantidade_filhos = nova_qtd;
        pai->ponteiro_filhos[nova_qtd - 1] = filho;
    }
}

void liberar_arvore(No* no) {
    if (!no) return;
    for (int i = 0; i < no->quantidade_filhos; i++) 
        liberar_arvore(no->ponteiro_filhos[i]);
    free(no->ponteiro_filhos);
    free(no);
}

// --- ALGORITMOS DE BUSCA ---

void busca_profundidade(No* atual, char alvo, char* caminho, int* total) {
    if (!atual) return;
    caminho[(*total)++] = atual->identificador;
    if (atual->identificador == alvo) return;
    for (int i = 0; i < atual->quantidade_filhos; i++) {
        if (caminho[*total - 1] == alvo) return;
        busca_profundidade(atual->ponteiro_filhos[i], alvo, caminho, total);
    }
}

void busca_largura(No* raiz, char alvo, char* caminho, int* total) {
    No* fila[100];
    int inicio = 0, fim = 0;
    fila[fim++] = raiz;
    while (inicio < fim) {
        No* atual = fila[inicio++];
        caminho[(*total)++] = atual->identificador;
        if (atual->identificador == alvo) return;
        for (int i = 0; i < atual->quantidade_filhos; i++) 
            fila[fim++] = atual->ponteiro_filhos[i];
    }
}

// --- EXPORTAÇÃO GRÁFICA (REFATORADA) ---

void escrever_nos_dot(FILE* arq, No* no, char* caminho, int total, char alvo) {
    if (!no) return;
    char* cor = "white";
    for (int i = 0; i < total; i++) {
        if (caminho[i] == no->identificador) {
            cor = (no->identificador == alvo) ? "salmon" : "palegreen";
            break;
        }
    }
    fprintf(arq, "    %c [fillcolor=%s, style=filled, shape=circle, penwidth=2];\n", no->identificador, cor);
    for (int i = 0; i < no->quantidade_filhos; i++) {
        fprintf(arq, "    %c -> %c [penwidth=1.5];\n", no->identificador, no->ponteiro_filhos[i]->identificador);
        escrever_nos_dot(arq, no->ponteiro_filhos[i], caminho, total, alvo);
    }
}

void configurar_estilo_dot(FILE* f, char* titulo) {
    // Título e Estilo Geral
    fprintf(f, "    label=\"%s\"; labelloc=\"t\"; fontsize=26; fontname=\"Arial Bold\";\n", titulo);
    
    // Formato Quadrado e Escala
    fprintf(f, "    ratio=1.0; size=\"10,10!\";\n");
    
    // Medidas: ranksep=0.3 encurta as setas; nodesep afasta as bolas grandes; pad é a margem
    fprintf(f, "    pad=0.5; nodesep=0.6; ranksep=0.3;\n");
    
    // Configuração dos Nós (Bolas 1.2 e Letras 22)
    fprintf(f, "    node [fontname=\"Arial Bold\", shape=circle, width=1.2, height=1.2, fixedsize=true, fontsize=22];\n");
    
    // Estilo das Linhas
    fprintf(f, "    edge [arrowhead=vee, arrowsize=1.0];\n");
}


void gerar_visual(No* raiz, char* caminho, int total, char alvo, char* nome_arq, char* titulo) {
    char dot_path[100], png_path[100], cmd[250];
    sprintf(dot_path, "figures/c/dot/%s.dot", nome_arq);
    sprintf(png_path, "figures/c/png/%s.png", nome_arq);

    FILE* f = fopen(dot_path, "w");
    if (!f) return;

    fprintf(f, "digraph G {\n");
    configurar_estilo_dot(f, titulo);
    escrever_nos_dot(f, raiz, caminho, total, alvo);
    fprintf(f, "}\n");
    fclose(f);

    sprintf(cmd, "dot -Tpng %s -o %s", dot_path, png_path);
    system(cmd);
}

// --- PROCESSAMENTO E OUTPUT (REFATORADO) ---

void imprimir_resultado_no_terminal(char* rotulo, char* caminho, int total, char alvo) {
    printf("\n" VERDE "[%s]" RESET " Ordem: ", rotulo);
    for (int i = 0; i < total; i++) printf("%c ", caminho[i]);
    
    if (alvo != '\0') 
        printf("(%d nos visitados ate encontrar %c)", total, alvo);
    else 
        printf("(%d nos na varredura total)", total);
}

void processar_busca(No* raiz, char alvo, FuncaoBusca algoritmo, char* rotulo, char* nome_arquivo) {
    char caminho[100] = {0};
    int total = 0;
    char titulo_imagem[100];

    algoritmo(raiz, alvo, caminho, &total);

    // Validação de existência do nó
    bool encontrado = (alvo == '\0' || (total > 0 && caminho[total - 1] == alvo));
    if (!encontrado) {
        printf("\n" VERMELHO "[%s] ERRO: O nó '%c' não existe." RESET, rotulo, alvo);
        return;
    }

    imprimir_resultado_no_terminal(rotulo, caminho, total, alvo);
    
    // Só gera imagem se for uma busca com alvo real
    if (alvo != '\0') {
        sprintf(titulo_imagem, "Algoritmo %s", rotulo);
        gerar_visual(raiz, caminho, total, alvo, nome_arquivo, titulo_imagem);
    }
}

// --- CONSTRUÇÃO E INTERFACE ---

void desenhar_mapa_hierarquico(No* no, char* prefixo, bool ultimo) {
    if (!no) return;
    printf("%s%s" CIANO " [%c]" RESET "\n", prefixo, ultimo ? "└──" : "├──", no->identificador);
    char p[100];
    for (int i = 0; i < no->quantidade_filhos; i++) {
        snprintf(p, sizeof(p), "%s%s", prefixo, ultimo ? "    " : "│   ");
        desenhar_mapa_hierarquico(no->ponteiro_filhos[i], p, i == no->quantidade_filhos - 1);
    }
}

No* carregar_arvore_exemplo() {
    No* a=criar_no('A'); No* b=criar_no('B'); No* e=criar_no('E'); No* z=criar_no('Z');
    No* c=criar_no('C'); No* l=criar_no('L'); No* f=criar_no('F'); No* n=criar_no('N');
    No* i=criar_no('I'); No* o=criar_no('O'); No* d=criar_no('D'); No* m=criar_no('M');
    No* g=criar_no('G'); No* j=criar_no('J'); No* p=criar_no('P'); No* h=criar_no('H');
    No* k=criar_no('K'); No* q=criar_no('Q');
    conectar_nos(a,b); conectar_nos(a,e); conectar_nos(a,z);
    conectar_nos(b,c); conectar_nos(b,l); conectar_nos(c,d); conectar_nos(c,m);
    conectar_nos(e,f); conectar_nos(e,n); conectar_nos(f,g); conectar_nos(g,h);
    conectar_nos(z,i); conectar_nos(z,o); conectar_nos(i,j); conectar_nos(j,k); conectar_nos(j,q);
    conectar_nos(o,p);
    return a;
}

int main() {
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    setlocale(LC_ALL, ".65001");

    No* raiz = carregar_arvore_exemplo();
    char alvo;

    printf("\n%s\n" AMARELO "        VISUALIZADOR DE BUSCA EM ARVORES\n" RESET "%s\n", DIVISOR, DIVISOR);
    desenhar_mapa_hierarquico(raiz, "", true);

    // Estado Inicial
    gerar_visual(raiz, "", 0, '\0', "arvore_completa", "Estrutura da Arvore Original");

    // Varreduras Totais (Apenas Terminal)
    processar_busca(raiz, '\0', busca_profundidade, "DFS COMPLETO", NULL);
    processar_busca(raiz, '\0', busca_largura, "BFS COMPLETO", NULL);

    printf("\n\n" AMARELO "Digite o no que deseja encontrar: " RESET);
    if (scanf(" %c", &alvo) != 1) return 1;
    if (alvo >= 'a') alvo -= 32;

    // Buscas Específicas (Terminal + Imagens)
    processar_busca(raiz, alvo, busca_profundidade, "RESULTADO DFS", "busca_dfs_resultado");
    processar_busca(raiz, alvo, busca_largura, "RESULTADO BFS", "busca_bfs_resultado");

    printf("\n\n" VERMELHO ">>> Memoria liberada. Encerrando..." RESET "\n");
    liberar_arvore(raiz);
    return 0;
}
