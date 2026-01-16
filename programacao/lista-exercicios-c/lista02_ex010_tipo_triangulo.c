/*
  lista02_ex010_tipo_triangulo.c
  Exercício 10 - Lista 02 (Exercícios com Funções)

  Objetivo:
    Implementar a função:
      int tipo_triangulo(double x, double y, double z);
    - retorna 0 se os segmentos NÃO podem formar um triângulo;
    - retorna 1 se formam Triângulo Equilátero;
    - retorna 2 se formam Triângulo Isósceles;
    - retorna 3 se formam Triângulo Escaleno.

  Observações (boas práticas):
    - usamos tolerância (EPS) para comparar números reais por causa de imprecisão do ponto flutuante;
    - validamos entradas (comprimentos devem ser positivos);
    - documentamos o comportamento de retorno.
*/

#include <stdio.h>   /* printf, scanf: entrada/saída */
#include <stdlib.h>  /* exit: utilitários */
#include <math.h>    /* fabs: valor absoluto para doubles (|x|) */

/* Protótipo da função: declara a assinatura antes do uso em main */
int tipo_triangulo(double x, double y, double z);

/* Definição da função tipo_triangulo:
   - recebe três comprimentos (double)
   - retorna 0 (não triângulo), 1 (equilátero), 2 (isósceles) ou 3 (escaleno)
*/
int tipo_triangulo(double x, double y, double z) {

    /* Constante de tolerância (EPS) para comparar doubles.
       Por que usar EPS?
         - operações com ponto flutuante (double) não são exatas;
         - ao testar igualdade ou desigualdade com resultados de cálculos
           é seguro usar uma pequena margem (por exemplo 1e-9).
       Escolhemos 1e-9 que é apropriado para entradas de tamanho típico.
    */
    const double EPS = 1e-9;

    /* Validação 1: comprimentos devem ser positivos (maiores que zero).
       Se algum comprimento for <= 0.0 (ou muito próximo de zero),
       não faz sentido físico e não é um triângulo válido. */
    if (x <= 0.0 || y <= 0.0 || z <= 0.0) {
        return 0; /* sinaliza "não forma triângulo" */
    }

    /* Normalização opcional: às vezes é útil ordenar os lados para facilitar verificações.
       Aqui NÃO precisamos ordenar para aplicar a desigualdade triangular, mas
       por clareza mostramos a técnica de obter valores absolutos caso necessário.
       Não alteramos x,y,z — usamos diretamente. */

    /* Verificação da propriedade triangular (desigualdade estrita):
       condição necessária e suficiente:
         cada lado deve ser menor que a soma dos outros dois:
           x < y + z
           y < x + z
           z < x + y
       Considerando EPS, escrevemos a forma segura:
         x + EPS < y + z  (i.e., x < y+z - EPS)
       Se qualquer uma dessas falhar, NÃO é triângulo. */
    if ( (x + EPS >= y + z) || (y + EPS >= x + z) || (z + EPS >= x + y) ) {
        /* Se qualquer condição indica que um lado é maior ou igual à soma dos outros,
           então não se forma triângulo (caso degenerado ou inválido). */
        return 0;
    }

    /* Agora sabemos que os comprimentos podem formar um triângulo.
       Precisamos identificar o tipo:
         - Equilátero: os três lados são iguais (com EPS para comparar doubles)
         - Isósceles: exatamente dois lados iguais (ou pelo menos dois iguais)
         - Escaleno: todos os três diferentes

       Usamos comparações com EPS para considerar igualdade numérica aproximada.
    */

    /* Teste de igualdade com tolerância:
       fabs(a - b) <= EPS  significa "a e b são iguais dentro da tolerância EPS". */
    int ab_iguais = (fabs(x - y) <= EPS);
    int ac_iguais = (fabs(x - z) <= EPS);
    int bc_iguais = (fabs(y - z) <= EPS);

    /* Se todos os pares são iguais, é equilátero */
    if (ab_iguais && ac_iguais && bc_iguais) {
        return 1; /* Equilátero */
    }

    /* Se pelo menos um par é igual, então é isósceles.
       Observação: Em triângulos com dois lados iguais (ou seja, pelo menos um par),
       o teste acima de equilátero já falhou, então restam os casos de isósceles. */
    if (ab_iguais || ac_iguais || bc_iguais) {
        return 2; /* Isósceles */
    }

    /* Se nenhum par é igual, então é escaleno (todos os lados diferentes) */
    return 3; /* Escaleno */
}

/* --- main: demonstração interativa da função --- */
int main(void) {
    double a, b, c; /* variáveis para armazenar os três comprimentos lidos do usuário */
    int tipo;       /* armazenará o valor retornado por tipo_triangulo */

    /* Cabeçalho informativo */
    printf("TIPO DE TRIANGULO - DEMONSTRACAO\n");
    printf("--------------------------------\n");
    printf("Digite tres comprimentos reais (a b c). Use Ctrl+D (Linux/macOS) ou Ctrl+Z (Windows) para sair.\n");

    /* Loop para permitir testes repetidos */
    while (1) {
        printf("\nDigite os tres lados (ex: 3.0 4.0 5.0): ");

        /* Leitura: scanf retorna quantos itens conseguiu ler; esperamos 3 doubles */
        if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
            /* Leitura falhou (EOF ou entrada inválida) -> encerramos com mensagem */
            printf("\nLeitura encerrada ou entrada invalida. Encerrando.\n");
            break;
        }

        /* Chama a função que determina o tipo do triângulo */
        tipo = tipo_triangulo(a, b, c);

        /* Interpretação do resultado para o usuário */
        if (tipo == 0) {
            printf("Nao forma um triangulo.\n");
        } else if (tipo == 1) {
            printf("Triangulo Equilatero (todos os lados iguais).\n");
        } else if (tipo == 2) {
            printf("Triangulo Isosceles (dois lados iguais).\n");
        } else if (tipo == 3) {
            printf("Triangulo Escaleno (todos os lados diferentes).\n");
        } else {
            /* caso improvável: valor inesperado retornado */
            printf("Resultado inesperado: codigo = %d\n", tipo);
        }
    }

    return 0; /* finaliza o programa com sucesso */
}
