/*
  lista02_ex005_categoria_nadador.c
  Exercício 5 - Lista 02 (Exercícios com Funções)

  Objetivo:
    - Determinar a categoria de um nadador a partir da sua idade, segundo a tabela:
        5 a 7 anos   -> categoria 1
        8 a 10 anos  -> categoria 2
       11 a 13 anos  -> categoria 3
       14 a 17 anos  -> categoria 4
       18 anos ou mais -> categoria 5

    - Implementamos:
        int categoria_nadador(int idade);
          -> retorna a categoria (1..5) diretamente

        void categoria_nadador_por_parametro(int idade, int *categoria);
          -> escreve a categoria na variável apontada por 'categoria' (retorno por parâmetro),
             que é exatamente o formato pedido no enunciado.

  Boas práticas aplicadas:
    - nomes claros e descritivos;
    - validação de parâmetros (idade e ponteiro);
    - uso de constantes e comentários explicativos;
    - funções pequenas e reutilizáveis.
*/

#include <stdio.h>   /* para printf e scanf */
#include <stdlib.h>  /* para exit (boa prática incluir) */

/* Protótipos das funções (declarações antes do uso) */
int categoria_nadador(int idade);
void categoria_nadador_por_parametro(int idade, int *categoria);

/* ---------------------------
   Implementação: categoria_nadador
   ---------------------------
   - Recebe: idade (int)
   - Retorna: categoria (int) conforme a tabela descrita acima.
   - Estratégia: validar a idade e usar testes encadeados (if/else) para mapear faixa -> categoria.
*/
int categoria_nadador(int idade) {
    /* Validação básica: idade não pode ser negativa.
       Se for negativa, devolvemos 0 como código de erro (nenhuma categoria válida é 0). */
    if (idade < 0) {
        return 0; /* 0 = erro/idade inválida */
    }

    /* Checamos faixa por faixa, do menor para o maior (ou poderia ser qualquer ordem clara).
       Para cada condição verdadeira retornamos a categoria correspondente. */

    if (idade >= 5 && idade <= 7) {
        /* se idade está entre 5 e 7 (inclusive), categoria 1 */
        return 1;
    } else if (idade >= 8 && idade <= 10) {
        /* se idade está entre 8 e 10 (inclusive), categoria 2 */
        return 2;
    } else if (idade >= 11 && idade <= 13) {
        /* 11 a 13 -> categoria 3 */
        return 3;
    } else if (idade >= 14 && idade <= 17) {
        /* 14 a 17 -> categoria 4 */
        return 4;
    } else if (idade >= 18) {
        /* 18 ou mais -> categoria 5 */
        return 5;
    } else {
        /* Se chegou aqui, significa que a idade é menor que 5 (por exemplo 0..4) — 
           não há categoria definida no enunciado para menores de 5 anos.
           Decidimos também sinalizar isso com 0 (erro / sem categoria). */
        return 0;
    }
}

/* ---------------------------
   Implementação: categoria_nadador_por_parametro
   ---------------------------
   - Recebe: idade (int) e ponteiro para int (int *categoria)
   - Escreve na posição apontada por 'categoria' o valor retornado por categoria_nadador.
   - Por que usar essa função?
     - O enunciado pediu "retorna, também por parâmetro, a categoria" — esta função exemplifica esse padrão:
       recebe um ponteiro e escreve o resultado nele (padrão comum em C para "retornar por referência").
*/
void categoria_nadador_por_parametro(int idade, int *categoria) {
    /* Verificamos que o ponteiro passado não é NULL (proteção contra uso inválido).
       Se for NULL, não temos onde escrever; imprimimos mensagem de erro e saímos com exit(1).
       Em código de produção você poderia retornar um código de erro em vez de exit. */
    if (categoria == NULL) {
        printf("Erro interno: ponteiro nulo passado para categoria_nadador_por_parametro.\n");
        exit(1);
    }

    /* Chamamos a função que retorna a categoria e escrevemos o resultado no local apontado. */
    *categoria = categoria_nadador(idade);
}

/* ---------------------------
   main: demonstração / testes interativos
   ---------------------------
   - Lê idades repetidamente e mostra a categoria usando as duas formas:
     * retornando diretamente (categoria_nadador)
     * retornando via parâmetro (categoria_nadador_por_parametro)
*/
int main(void) {
    int idade_input;      /* armazena a idade lida do usuário */
    int cat_direct;       /* armazenará categoria retornada diretamente */
    int cat_by_param;     /* armazenará categoria recebida por parâmetro */

    /* Cabeçalho para o usuário */
    printf("CATEGORIA DE NADADOR - DEMONSTRACAO\n");
    printf("-----------------------------------\n");
    printf("Digite uma idade (valor negativo para encerrar):\n");

    /* Loop de leitura: continua até o usuário digitar idade negativa */
    while (1) {
        printf("Idade: ");

        /* scanf retorna quantos itens foram lidos com sucesso; verificamos se foi 1 */
        if (scanf("%d", &idade_input) != 1) {
            /* leitura inválida (por exemplo, usuário digitou texto): limpamos e encerramos */
            printf("Entrada invalida. Encerrando.\n");
            return 1;
        }

        /* condição de saída: idade negativa encerra o programa */
        if (idade_input < 0) {
            printf("Encerrando. Ate logo!\n");
            break; /* sai do while */
        }

        /* --- Uso 1: chamada direta que retorna int --- */
        cat_direct = categoria_nadador(idade_input);
        /* interpretamos o valor 0 como "idade inválida / sem categoria definida" */
        if (cat_direct == 0) {
            printf("Usando retorno direto: idade %d -> sem categoria definida (idade fora do intervalo 5+).\n",
                   idade_input);
        } else {
            printf("Usando retorno direto: idade %d -> categoria %d.\n", idade_input, cat_direct);
        }

        /* --- Uso 2: chamada que retorna por parâmetro --- */
        categoria_nadador_por_parametro(idade_input, &cat_by_param);
        if (cat_by_param == 0) {
            printf("Usando retorno por parametro: idade %d -> sem categoria definida.\n", idade_input);
        } else {
            printf("Usando retorno por parametro: idade %d -> categoria %d.\n", idade_input, cat_by_param);
        }

        printf("\n"); /* linha em branco antes da próxima leitura para organização visual */
    }

    return 0; /* sucesso */
}
