#include <stdio.h>           // Biblioteca padrão para entrada/saída: printf, scanf
#include <stdlib.h>          // Biblioteca de utilitários: exit (boa prática incluir)

/* 
  lista02_ex001_area_circulo.c
  Exercício 1 - Lista 02 (Exercícios com Funções)

  Objetivo:
    Implementar a função:
      double area_circulo(double raio);
    que recebe o raio de um círculo e retorna a área calculada por:
      Area = PI * raio * raio

  Observações de boas práticas:
    - usamos `const` para PI (valor que não muda);
    - validação simples do raio (não pode ser negativo);
    - nomes de variáveis e função descritivos (facilitam leitura);
    - documentação no topo do arquivo para facilitar revisão.
*/

/* --- Declarações / constantes --- */
const double PI = 3.14159265358979323846; // Valor de PI definido como constante com precisão dupla

/* 
  Protótipo (declaração) da função:
  - informa ao compilador que existe uma função chamada area_circulo
    que recebe um double e retorna um double.
  - boa prática: declarar protótipos antes de usá-los.
*/
double area_circulo(double raio);

/* --- Função que calcula a área do círculo --- */
double area_circulo(double raio) {
    /* Validação: raio negativo não tem sentido físico aqui */
    if (raio < 0.0) {
        /* Em vez de retornar um valor "mágico", preferimos indicar erro.
           Aqui retornamos -1.0 para sinalizar que a entrada era inválida.
           Em programas maiores você poderia lançar erro diferente ou usar errno. */
        return -1.0;
    }

    /* Cálculo da área: A = PI * raio * raio
       multiplicamos raio por raio em vez de usar pow para manter
       clareza e evitar custo desnecessário. */
    double area = PI * raio * raio;

    /* Resultado: devolve a área calculada para o chamador */
    return area;
}

/* --- Função main: demonstra o uso de area_circulo --- */
int main(void) {
    double raio;       // variável que armazena o raio lido do usuário
    double resultado;  // variável que armazenará a área retornada pela função

    /* Instrução ao usuário */
    printf("CALCULO DA AREA DE UM CIRCULO\n");
    printf("-----------------------------\n");
    printf("Digite o raio do circulo (numero nao negativo): ");

    /* Lê um double do teclado e valida o scanf */
    if (scanf("%lf", &raio) != 1) {
        printf("Entrada invalida. Por favor digite um numero.\n");
        return 1; /* encerra com código de erro */
    }

    /* Chama a função que calcula a área */
    resultado = area_circulo(raio);

    /* Verifica se a função sinalizou erro (raio negativo) */
    if (resultado < 0.0) {
        printf("Erro: o raio informado e negativo. Nao e possivel calcular a area.\n");
        return 1;
    }

    /* Mostra o resultado formatado com duas casas decimais */
    printf("A area do circulo de raio %.4lf e: %.4lf\n", raio, resultado);

    return 0; /* indica término com sucesso */
}