/* lista02_ex007_eh_par.c
   Exercício 7 - Lista 02 (Exercícios com Funções)

   Objetivo:
     Implementar a função bool eh_par(int x) que verifica se um número inteiro é par.
     Retorna true se for par, false se for ímpar.

   Boas práticas aplicadas:
     - uso de <stdbool.h> para clareza (true/false)
     - tratamento consistente de números negativos usando abs()
     - validação de leitura com scanf
     - função pequena e reutilizável com responsabilidade única
*/

#include <stdio.h>    /* printf, scanf — entrada e saída */
#include <stdlib.h>   /* abs, exit — utilitários (abs para tratar negativos) */
#include <stdbool.h>  /* bool, true, false — tipos booleanos legíveis */

/* Protótipo da função: declaração antecipada para o compilador */
bool eh_par(int x);

/* === Definição da função eh_par === */
/* A função retorna true quando x é par, false caso contrário.
   Observação: usamos abs(x) para que -4 também seja considerado par (consistente com a definição).
*/
bool eh_par(int x) {
    /* calcula o valor absoluto de x para lidar com negativos */
    int valor_abs = abs(x);            /* abs(x) devolve o valor absoluto de x (int) */

    /* verifica o resto da divisão de valor_abs por 2 */
    if (valor_abs % 2 == 0) {          /* se resto é zero, o número é divisível por 2 -> par */
        return true;                   /* retorna verdadeiro (é par) */
    }

    /* caso contrário (resto != 0), não é par */
    return false;                      /* retorna falso (ímpar) */
}

/* === Função main: demonstração e testes interativos === */
int main(void) {
    int numero;            /* armazena o inteiro lido do usuário */
    bool resultado;        /* armazenará o retorno de eh_par */

    /* cabeçalho informativo para o usuário */
    printf("VERIFICADOR DE PAR/IMPAR\n");                   /* imprime título */
    printf("------------------------\n");                   /* linha separadora */
    printf("Digite numeros inteiros (Ctrl+D/Ctrl+Z para encerrar):\n"); /* instrução */

    /* loop interativo: permite testar vários números sem reiniciar o programa */
    while (1) {
        printf("Numero: ");                             /* prompt para o usuário */

        /* tenta ler um inteiro; scanf retorna quantos valores foram lidos com sucesso */
        if (scanf("%d", &numero) != 1) {                /* se não leu 1 inteiro (EOF/erro) */
            printf("\nLeitura encerrada ou entrada invalida. Saindo.\n"); /* avisa */
            break;                                     /* sai do loop e termina o programa */
        }

        /* chama a função que testa paridade */
        resultado = eh_par(numero);                     /* guarda true/false em resultado */

        /* imprime resultado de forma amigável ao usuário */
        if (resultado) {                                /* se resultado == true */
            printf("%d eh PAR.\n\n", numero);           /* imprime que é par */
        } else {                                        /* caso resultado == false */
            printf("%d eh IMPAR.\n\n", numero);         /* imprime que é ímpar */
        }
    }

    return 0; /* encerra o programa com código 0 (sucesso) */
}
