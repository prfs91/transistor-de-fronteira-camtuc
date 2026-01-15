/* lista02_ex009_peso_ideal.c
   Exercício 9 - Lista 02 (Exercícios com Funções)

   Objetivo:
     Implementar a função:
       double peso_ideal(double altura, char sexo);
     - Para homens (sexo 'M'/'m'): peso ideal = 72.7 * altura - 58
     - Para mulheres (sexo 'F'/'f'): peso ideal = 62.1 * altura - 44.7

   Boas práticas aplicadas:
     - nomes claros e descritivos;
     - protótipo declarado antes do uso;
     - validação dos parâmetros (altura positiva; sexo reconhecido);
     - normalização do caractere sexo (toupper) para aceitar maiúsculas/minúsculas;
     - retorno de -1.0 para sinalizar erro, que o chamador pode detectar;
     - documentação e comentários linha-a-linha para quem está aprendendo.
*/

#include <stdio.h>    /* printf, scanf — entrada e saída */
#include <stdlib.h>   /* exit, abs, boa prática incluir (não estritamente necessário aqui) */
#include <ctype.h>    /* toupper — para normalizar letra do sexo */

/* Protótipo da função: declara sua assinatura antes do uso (boa prática) */
double peso_ideal(double altura, char sexo);

/* --- Implementação da função peso_ideal --- */
/* Recebe:
     - altura: altura da pessoa em metros (ex.: 1.75)
     - sexo: caractere 'M' ou 'F' (maiúsculo ou minúsculo)
   Retorna:
     - peso ideal calculado (double) ou
     - -1.0 se algum parâmetro for inválido (altura <= 0, sexo diferente de M/F)
*/
double peso_ideal(double altura, char sexo) {
    /* Constantes das fórmulas definidas com nomes explicativos */
    const double COEF_HOMEM = 72.7;      /* coeficiente para homens */
    const double CONST_HOMEM = 58.0;     /* constante subtraída para homens */
    const double COEF_MULHER = 62.1;     /* coeficiente para mulheres */
    const double CONST_MULHER = 44.7;    /* constante subtraída para mulheres */

    /* Validação básica: altura deve ser positiva (maior que zero) */
    if (altura <= 0.0) {
        /* Retornamos -1.0 como sinal de erro para indicar parâmetro inválido */
        return -1.0;
    }

    /* Normaliza o caractere sexo para maiúscula para aceitar 'm' e 'M' igualmente.
       (casts garantem comportamento definido ao passar char para toupper) */
    char s = (char) toupper((unsigned char) sexo);

    /* Escolhe a fórmula de acordo com o sexo */
    if (s == 'M') {
        /* aplica fórmula do homem: 72.7 * altura - 58 */
        double resultado = COEF_HOMEM * altura - CONST_HOMEM;
        return resultado; /* devolve o peso ideal calculado */
    } else if (s == 'F') {
        /* aplica fórmula da mulher: 62.1 * altura - 44.7 */
        double resultado = COEF_MULHER * altura - CONST_MULHER;
        return resultado; /* devolve o peso ideal calculado */
    } else {
        /* sexo inválido (não é 'M' nem 'F') -> sinaliza erro */
        return -1.0;
    }
}

/* --- main: demonstração interativa da função --- */
int main(void) {
    double altura;    /* armazena a altura lida do usuário (em metros) */
    char sexo;        /* armazena o sexo lido do usuário (caractere) */
    double peso;      /* armazenará o peso ideal retornado pela função */

    /* Cabeçalho informativo para o usuário */
    printf("CALCULO DE PESO IDEAL\n");
    printf("----------------------\n");
    printf("Informe a altura em metros e o sexo (M/F).\n");
    printf("Exemplo: 1.75 M  -> altura 1.75 metros, sexo masculino.\n");
    printf("Digite Ctrl+D (Linux/macOS) ou Ctrl+Z (Windows) para encerrar.\n\n");

    /* Loop de leitura para permitir múltiplos testes */
    while (1) {
        printf("Digite altura e sexo (ex: 1.70 F): ");

        /* Leitura: scanf tenta ler um double e um caractere.
           Note: o espaço antes de %c em " %c" consome qualquer whitespace pendente (como newline). */
        if (scanf("%lf %c", &altura, &sexo) != 2) {
            /* Se leitura falhar (EOF ou entrada inválida), encerra o loop educadamente */
            printf("\nLeitura encerrada ou entrada invalida. Saindo.\n");
            break;
        }

        /* Chamada da função que calcula o peso ideal */
        peso = peso_ideal(altura, sexo);

        /* Verifica se ocorreu erro (peso == -1.0 é sinal de parâmetro inválido) */
        if (peso < 0.0) {
            printf("Parametros invalidos. Verifique: altura > 0 e sexo = 'M' ou 'F'.\n\n");
            continue; /* volta a pedir nova entrada */
        }

        /* Exibe o resultado com 2 casas decimais para leitura amigável */
        printf("Altura: %.2lf m, Sexo: %c -> Peso ideal: %.2lf kg\n\n", altura, (char) toupper((unsigned char) sexo), peso);
    }

    return 0; /* encerra o programa com sucesso */
}
