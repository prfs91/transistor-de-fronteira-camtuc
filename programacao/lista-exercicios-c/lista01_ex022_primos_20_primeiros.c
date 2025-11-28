#include <stdio.h>   // biblioteca padrão para entrada/saída: printf
#include <stdlib.h>  // biblioteca de utilitários (boa prática incluir)
#include <stdbool.h> // para usar o tipo bool (true/false)

/*
  Arquivo: lista01_ex022_primos_20_primeiros.c

  Objetivo:
    Calcular e mostrar os 20 primeiros números primos.
    Estratégia:
      - usar um laço principal que testa candidatos (2, 3, 4, ...)
      - para cada candidato, testar primalidade por tentativa de divisão (trial division)
        até a raiz inteira do candidato (implementado sem sqrt, usando i*i <= n).
      - usar apenas while (repetição) conforme pedido.
*/

 // Função que determina se um inteiro n >= 2 é primo.
 // Retorna true se n for primo, false caso contrário.
bool eh_primo(int n) {
    // Caso trivial: 2 é primo
    if (n == 2) {
        return true;
    }

    // Eliminamos pares maiores que 2 (não primos)
    if (n % 2 == 0 || n < 2) {
        // se é divisível por 2 ou menor que 2, não é primo
        return false;
    }

    // Teste de divisores ímpares a partir de 3 até sqrt(n) usando i*i <= n.
    int divisor = 3;                // começamos em 3 (o próximo ímpar após 2)
    // enquanto divisor*divisor <= n, testamos divisibilidade
    while ((long long)divisor * divisor <= (long long)n) {
        if (n % divisor == 0) {     // se n é divisível por divisor, não é primo
            return false;
        }
        divisor = divisor + 2;     // avançamos apenas nos ímpares (3,5,7,...)
    }

    // se nenhum divisor foi encontrado, n é primo
    return true;
}

int main(void) {
    const int META = 20;           // queremos os 20 primeiros primos (constante para clareza)
    int encontrados = 0;           // contador de primos encontrados até agora
    int candidato = 2;             // primeiro número a testar (2 é primeiro primo)
    
    printf("Os %d primeiros numeros primos sao:\n", META);

    // laço principal: continua até encontrarmos META primos
    while (encontrados < META) {

        // testamos se 'candidato' é primo usando a função eh_primo
        if (eh_primo(candidato)) {
            // se for primo, imprimimos e incrementamos o contador
            printf("%d", candidato);
            encontrados = encontrados + 1;

            // para formatar a saída: vírgula e espaço entre números, ponto final no final
            if (encontrados < META) {
                printf(", ");
            } else {
                printf(".\n");
            }
        }

        // avançamos para o próximo número a testar
        candidato = candidato + 1;
    }

    return 0; // finaliza o programa com sucesso
}