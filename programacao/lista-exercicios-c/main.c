#include <stdio.h>      // inclui declarações para entrada/saída (printf, scanf, FILE, fopen, etc.)
#include <stdlib.h>     // inclui declarações para system(), exit(), malloc/free (aqui usamos system)
#include <string.h>     // inclui declarações para manipulação de strings (strcat, sprintf, strcmp, etc.)

// Função que verifica se um arquivo (.c) existe e se está vazio
int arquivo_vazio(const char *nome) {
    FILE *f = fopen(nome, "r");    // abre o arquivo para leitura
    if (f == NULL) return 1;       // se fopen retornou NULL, o arquivo não existe -> tratamos como "vazio"
    fseek(f, 0, SEEK_END);         // move o cursor para o fim do arquivo
    long tam = ftell(f);           // pega a posição atual -> tamanho do arquivo em bytes
    fclose(f);                     // fecha o arquivo
    return (tam == 0);             // retorna 1 (verdadeiro) se tam==0 (vazio), caso contrário 0
}

int main() {
    int exercicio;                 // número do exercício escolhido pelo usuário
    char nome_arquivo[200];        // buffer para montar o nome do arquivo .c (ex: lista01_ex001_area_trapezio.c)
    char comando[300];             // buffer para montar o comando de compilação (gcc ...)
    
    // descricoes: parte final do nome dos arquivos .c que você já tem, na ordem de 1 a 22
    char *descricoes[] = {
        "area_trapezio",
        "litros_gasolina",
        "media_ponderada",
        "dias_para_anos_meses_dias",
        "salario_aumento_imposto",
        "sanduiche_ingredientes",
        "novo_peso",
        "entrada_prestacoes",
        "minutos_para_horas_minutos_segundos",
        "caixa_eletronico_notas",
        "conta_negativos",
        "media_areas_triangulos",
        "intervalo_10_20",
        "salario_filhos_estatisticas",
        "crescimento_chico_ze",
        "votacao_contagem",
        "media_ponderada_loop",
        "fatorial",
        "pesquisa_idade_sexo_salario",
        "acidentes_cidades",
        "pesquisa_habitantes",
        "primos_20_primeiros"
    };

    // menu: textos que descrevem o que cada exercicio faz, mostrados ao usuario
    char *menu[] = {
        "01 - Area de um trapezio",
        "02 - Litros de gasolina pelo valor pago",
        "03 - Media ponderada",
        "04 - Conversao de dias em anos/meses/dias",
        "05 - Aumento salarial com impostos",
        "06 - Ingredientes para sanduiches",
        "07 - Novo peso apos engordar/emagrecer",
        "08 - Entrada + duas prestacoes",
        "09 - Conversao de minutos em horas/minutos/segundos",
        "10 - Caixa eletronico: notas otimas",
        "11 - Conta valores negativos",
        "12 - Media das areas de triangulos",
        "13 - Intervalo [10,20]",
        "14 - Estatisticas: salarios e filhos",
        "15 - Crescimento: Chico x Ze",
        "16 - Contagem de votos",
        "17 - Media ponderada repetitiva",
        "18 - Fatorial de N",
        "19 - Pesquisa: idade/sexo/salario",
        "20 - Estatisticas de acidentes nas cidades",
        "21 - Pesquisa com 1000 habitantes",
        "22 - 20 primeiros numeros primos"
    };

    // cabeçalho visual
    printf("==============================================\n");
    printf("      EXECUTOR DE EXERCICIOS — LISTA 01       \n");
    printf("==============================================\n\n");

    // mostra o menu completo
    for (int i = 0; i < 22; i++) {
        printf("%s\n", menu[i]);
    }

    // solicita ao usuário qual exercício rodar
    printf("\nDigite o numero do exercicio (1 a 22): ");
    if (scanf("%d", &exercicio) != 1) {   // verifica se a leitura foi bem-sucedida
        printf("Entrada invalida. Encerrando.\n");
        return 1;
    }

    // valida se o número está no intervalo esperado
    if (exercicio < 1 || exercicio > 22) {
        printf("Numero invalido! Encerrando.\n");
        return 1;
    }

    // monta o nome completo do arquivo .c: por exemplo "lista01_ex001_area_trapezio.c"
    sprintf(nome_arquivo,
            "lista01_ex%03d_%s.c",
            exercicio,
            descricoes[exercicio - 1]);

    // informa ao usuário qual arquivo será verificado
    printf("\nArquivo selecionado: %s\n", nome_arquivo);

    // verifica se o arquivo .c existe e não está vazio
    if (arquivo_vazio(nome_arquivo)) {
        printf("O arquivo esta vazio ou nao existe. Encerrando...\n");
        return 0;
    }

    // se chegou aqui, o arquivo tem código — vamos compilar e executar
    printf("Arquivo valido.\n");
    printf("Compilando...\n");

    // monta comando de compilacao com gcc produzindo exec_temp
    sprintf(comando, "gcc %s -o exec_temp", nome_arquivo);
    system(comando);               // chama o sistema para executar o comando de compilacao

    printf("Executando...\n\n");
    system("./exec_temp");         // executa o binário gerado (Linux/macOS). No Windows: "exec_temp.exe"

    return 0;                      // encerra o programa principal com codigo 0 (sucesso)
}