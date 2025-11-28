#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída, necessária para usar printf e scanf.

/*
    Este programa calcula a área de um trapézio.
    Fórmula: A = ((base_maior + base_menor) * altura) / 2
*/

int main() {   // Início da função principal. Todo programa em C começa por aqui.
    
    // Declaração das variáveis com nomes claros.
    // "double" permite números com casas decimais, ideal para medidas reais.
    double base_maior;  
    double base_menor;
    double altura;
    double area_do_trapezio;

    // Explica ao usuário o que o programa faz.
    printf("CALCULADORA DE AREA DE UM TRAPEZIO\n");
    printf("----------------------------------\n");

    // Solicita ao usuário que informe os valores necessários.
    printf("Digite o valor da base maior: ");
    scanf("%lf", &base_maior);   // %lf lê um número decimal do tipo double.
                                 // &base_maior é o endereço da variável onde o valor será armazenado.

    printf("Digite o valor da base menor: ");
    scanf("%lf", &base_menor);

    printf("Digite o valor da altura: ");
    scanf("%lf", &altura);

    // Aplica a fórmula da área do trapézio.
    // Parênteses são importantes para garantir a ordem correta da operação.
    area_do_trapezio = ((base_maior + base_menor) * altura) / 2;

    // Mostra o resultado final.
    printf("A area do trapezio eh: %.2lf", area_do_trapezio); 
    // %.2lf exibe o número com 2 casas decimais, deixando a saída mais bonita.

    return 0;   // Retorna 0 indicando que o programa terminou sem erros.
}