#include <stdio.h>    // biblioteca padrão para entrada/saída: printf, scanf
#include <stdlib.h>   // utilitários (boa prática incluir)
#include <limits.h>   // para INT_MAX e INT_MIN

/*
  Arquivo: lista01_ex021_pesquisa_habitantes.c

  Objetivo:
    Ler dados de 1000 habitantes: sexo (0-feminino, 1-masculino), idade (int) e altura (double).
    Calcular e mostrar:
      a) maior e menor idade do grupo;
      b) média da idade do grupo;
      c) média da altura das mulheres;
      d) média da idade dos homens;
      e) percentual de pessoas com idade entre 18 e 35 anos (inclusive).
*/

int main(void) {
    const int TOTAL_HABITANTES = 1000;     // número fixo de registros a ler (exigido pelo enunciado)

    /* variáveis de entrada (uma por habitante) */
    int sexo;               // 0 = feminino, 1 = masculino (conforme enunciado)
    int idade;              // idade do habitante (anos, inteiro)
    double altura;          // altura do habitante em metros (ex: 1.75)

    /* variáveis acumuladoras / estatísticas */
    long long soma_idades = 0LL;        // soma de todas as idades (para média geral)
    int maior_idade = INT_MIN;          // inicializa com valor mínimo possível para garantir atualização
    int menor_idade = INT_MAX;          // inicializa com valor máximo possível para garantir atualização

    long long soma_altura_mulheres_count = 0; // soma das alturas das mulheres multiplicada por 1000? (não) -> CORREÇÃO abaixo
    double soma_alturas_mulheres = 0.0; // soma das alturas das mulheres (para média)
    int contador_mulheres = 0;          // quantas mulheres foram lidas

    long long soma_idade_homens = 0LL;  // soma das idades dos homens (para média dos homens)
    int contador_homens = 0;            // quantos homens foram lidos

    int contador_entre_18_35 = 0;       // contagem de pessoas com idade entre 18 e 35 (inclusive)

    int leitura_ok;                     // variável auxiliar para checar retorno de scanf

    /* cabeçalho para o usuário */
    printf("PESQUISA: SEXO (0-F,1-M), IDADE (anos) E ALTURA (metros)\n");
    printf("Voce devera informar %d registros, um por vez.\n", TOTAL_HABITANTES);
    printf("Sexo: 0 = feminino, 1 = masculino. Idade e altura sao valores numericos.\n\n");

    /* laço while que repete exatamente TOTAL_HABITANTES vezes */
    int contador = 0;                    // controlará quantos registros já foram lidos
    while (contador < TOTAL_HABITANTES) {

        /* solicita e lê o sexo (0 ou 1) */
        printf("Registro %d/%d - Digite o sexo (0=F,1=M): ", contador + 1, TOTAL_HABITANTES);
        leitura_ok = scanf("%d", &sexo);
        if (leitura_ok != 1) {          // valida se scanf leu um inteiro
            printf("Entrada invalida para sexo. Encerrando.\n");
            return 1;                   // erro de entrada -> encerra
        }
        if (sexo != 0 && sexo != 1) {   // valida valor aceitável
            printf("Valor de sexo invalido (deve ser 0 ou 1). Encerrando.\n");
            return 1;
        }

        /* solicita e lê a idade */
        printf("Digite a idade (anos): ");
        leitura_ok = scanf("%d", &idade);
        if (leitura_ok != 1) {
            printf("Entrada invalida para idade. Encerrando.\n");
            return 1;
        }
        if (idade < 0) {                // idade negativa não faz sentido no contexto
            printf("Idade invalida (negativa). Encerrando.\n");
            return 1;
        }

        /* solicita e lê a altura */
        printf("Digite a altura (metros, ex: 1.75): ");
        leitura_ok = scanf("%lf", &altura);
        if (leitura_ok != 1) {
            printf("Entrada invalida para altura. Encerrando.\n");
            return 1;
        }
        if (altura <= 0.0) {            // altura positiva esperada
            printf("Altura invalida (deve ser positiva). Encerrando.\n");
            return 1;
        }

        /* --- Atualizacoes das estatisticas --- */

        /* soma para media geral de idades */
        soma_idades += (long long) idade;

        /* atualiza maior e menor idade */
        if (idade > maior_idade) maior_idade = idade;
        if (idade < menor_idade) menor_idade = idade;

        /* se for mulher, acumula altura e incrementa contador de mulheres */
        if (sexo == 0) {
            soma_alturas_mulheres += altura;
            contador_mulheres++;
        } else { /* se for homem, acumula idade para calcular media de idade dos homens */
            soma_idade_homens += (long long) idade;
            contador_homens++;
        }

        /* conta se a idade está no intervalo [18,35] inclusive */
        if (idade >= 18 && idade <= 35) {
            contador_entre_18_35++;
        }

        /* incrementa o contador de registros lidos e segue no laço */
        contador = contador + 1;
        printf("\n"); /* separador visual entre registros */
    } /* fim do while */

    /* --- Após leitura de 1000 registros: calculos finais e exibicao --- */

    /* a) maior e menor idade (caso a população seja >0, sempre será, pois TOTAL_HABITANTES=1000) */
    printf("\nRESULTADOS DA PESQUISA\n");
    printf("----------------------\n");
    printf("Maior idade do grupo: %d anos\n", maior_idade);
    printf("Menor idade do grupo: %d anos\n", menor_idade);

    /* b) media da idade do grupo */
    {
        double media_idade = (double) soma_idades / (double) TOTAL_HABITANTES;
        printf("Media da idade do grupo: %.2f anos\n", media_idade);
    }

    /* c) media da altura das mulheres (verifica se houve mulheres) */
    if (contador_mulheres == 0) {
        printf("Nao houve mulheres registradas; media de altura das mulheres nao pode ser calculada.\n");
    } else {
        double media_altura_mulheres = soma_alturas_mulheres / (double) contador_mulheres;
        printf("Media da altura das mulheres: %.2f m (em %d mulheres)\n",
               media_altura_mulheres, contador_mulheres);
    }

    /* d) media da idade dos homens (verifica se houve homens) */
    if (contador_homens == 0) {
        printf("Nao houve homens registrados; media de idade dos homens nao pode ser calculada.\n");
    } else {
        double media_idade_homens = (double) soma_idade_homens / (double) contador_homens;
        printf("Media da idade dos homens: %.2f anos (em %d homens)\n",
               media_idade_homens, contador_homens);
    }

    /* e) percentual de pessoas com idade entre 18 e 35 anos (inclusive) */
    {
        double percentual = ((double) contador_entre_18_35 * 100.0) / (double) TOTAL_HABITANTES;
        printf("Percentual de pessoas com idade entre 18 e 35 anos: %.2f%% ( %d pessoas )\n",
               percentual, contador_entre_18_35);
    }

    return 0; /* encerra o programa com sucesso */
}