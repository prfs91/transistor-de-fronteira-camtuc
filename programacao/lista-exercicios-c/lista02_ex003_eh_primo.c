/* 
  lista02_ex003_eh_primo.c
  Exercício 3 - Lista 02 (Exercícios com Funções)

  Objetivo:
    Implementar a função:
      int eh_primo(int n);
    que recebe um valor inteiro e positivo `n` e retorna:
      1  -> se `n` for primo (verdadeiro)
      0  -> se `n` não for primo (falso)

  Observações:
    - A função usa trial division eficiente:
      * elimina casos triviais (n < 2, paridade),
      * testa apenas divisores ímpares até a raiz inteira de n,
      * faz multiplicação em 64 bits para evitar overflow quando comparando divisor*divisor <= n.
    - O `main` demonstra leitura e uso da função.
*/

/* inclui a biblioteca padrão de entrada/saída (printf, scanf)
   - #include é uma diretiva do pré-processador que "cola" o conteúdo do header
   - <stdio.h> contém declarações de printf e scanf, que usamos abaixo */
#include <stdio.h>

/* inclui biblioteca de utilitários (boa prática)
   - aqui não usamos funções específicas de stdlib, mas mantemos por padrão/consistência */
#include <stdlib.h>

/* Protótipo da função:
   - informa ao compilador que existe uma função eh_primo que recebe um int e retorna um int.
   - isso permite chamá-la no main mesmo que sua definição venha depois. */
int eh_primo(int n);

/* === Definição da função eh_primo === */

/* Cabeçalho da função:
   - int     : tipo de retorno (usamos 1/0 para verdadeiro/falso)
   - eh_primo: nome da função (descritivo; em português "é primo")
   - (int n) : parâmetro chamado n, do tipo inteiro
*/
int eh_primo(int n) {

    /* Linha: if (n < 2) return 0;
       Explicação:
       - if      : palavra-chave que inicia uma condição
       - (n < 2) : condição que verifica se n é menor que 2
                   * números menores que 2 (0 e 1) não são primos
       - return 0; : retorna 0 imediatamente indicando "falso"
       Por que é necessária?
       - evita trabalho desnecessário e cobre casos triviais. */
    if (n < 2) return 0;

    /* Linha: if (n == 2) return 1;
       Explicação:
       - testa se n é exatamente 2
       - 2 é o menor primo e o único primo par
       - retornar 1 aqui é rápido e claro */
    if (n == 2) return 1;

    /* Linha: if (n % 2 == 0) return 0;
       Explicação:
       - n % 2 calcula o resto da divisão de n por 2
       - se resto é 0, então n é par
       - todos os pares maiores que 2 não são primos
       - retornar 0 evita testar divisores desnecessários */
    if (n % 2 == 0) return 0;

    /* Preparação para o teste de divisores ímpares:
       - vamos testar apenas divisores ímpares: 3,5,7,...
       - iniciamos o divisor em 3 */
    int divisor = 3;

    /* Laço while: while ((long long) divisor * divisor <= (long long) n) { ... }
       Explicação palavra-a-palavra:
       - while : inicia um laço que repete enquanto a condição for verdadeira
       - (long long) divisor * divisor : convertendo divisor para 64 bits e multiplicando por si
         * fazemos cast para long long para evitar overflow em plataformas onde int é 32 bits
       - <= (long long) n : comparamos o quadrado do divisor com n (também em 64 bits)
       Por que usar divisor*divisor <= n?
       - se divisor*divisor > n então divisor > sqrt(n) e não há necessidade de testar além da raiz
       - testar até a raiz é suficiente para encontrar um divisor se houver
    */
    while ((long long) divisor * divisor <= (long long) n) {

        /* Linha: if (n % divisor == 0) return 0;
           Explicação:
           - n % divisor : resto da divisão de n por divisor
           - == 0        : verifica se divisor divide n exatamente
           - se for divisível, n não é primo, então retornamos 0 (falso)
           Por que aqui?
           - detectar um divisor comum prova que n não é primo */
        if (n % divisor == 0) return 0;

        /* Linha: divisor = divisor + 2;
           Explicação:
           - incrementa divisor em 2 para pular os pares (já eliminados)
           - sequência: 3,5,7,9,... (mas 9 será testado e rejeitado por condição de divisibilidade)
           Por que pular pares?
           - eficiência: metade dos candidatos a divisor são pares (já descartados) */
        divisor = divisor + 2;
    }

    /* Se chegamos até aqui sem encontrar divisor, n é primo.
       Linha: return 1; : devolve verdadeiro */
    return 1;
}

/* === Função main de demonstração / teste === */
int main(void) {
    /* declaração de variáveis locais no main */
    int valor;        /* variável para armazenar o número digitado pelo usuário */
    int resultado;    /* variável para armazenar o retorno de eh_primo */

    /* instrução para o usuário */
    printf("VERIFICADOR DE PRIMO\n");
    printf("--------------------\n");
    printf("Digite um numero inteiro e positivo (ou um valor negativo para sair): ");

    /* leitura em loop para permitir vários testes sem reiniciar o programa */
    while (1) {
        /* scanf lê um inteiro e retorna quantos itens foram lidos com sucesso */
        if (scanf("%d", &valor) != 1) {
            /* se scanf falhar (por exemplo, usuario digitou uma letra), informamos e encerramos */
            printf("Entrada invalida. Encerrando.\n");
            return 1;
        }

        /* condição de saída: se o usuário digitar valor negativo, saímos do loop */
        if (valor < 0) {
            printf("Encerrando o programa. Ate logo!\n");
            break; /* interrompe o while(1) */
        }

        /* chama a função eh_primo e armazena o retorno em `resultado` */
        resultado = eh_primo(valor);

        /* imprime resultado de forma amigável:
           - se resultado == 1 -> é primo
           - se resultado == 0 -> não é primo */
        if (resultado == 1) {
            printf("%d eh primo.\n", valor);
        } else {
            printf("%d nao eh primo.\n", valor);
        }

        /* prompt para próximo número (melhora a experiência de uso no terminal) */
        printf("Digite outro numero (ou negativo para sair): ");
    }

    return 0; /* encerra o programa com código 0 (sucesso) */
}