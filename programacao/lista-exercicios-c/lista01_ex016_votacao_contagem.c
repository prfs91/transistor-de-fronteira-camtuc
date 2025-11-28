#include <stdio.h>   // inclui funções de entrada/saída: printf (imprime) e scanf (lê)
#include <stdlib.h>  // inclui utilitários (boa prática incluir)

/*
  Arquivo: lista01_ex016_votacao_contagem.c
  Objetivo:
    Ler códigos de votos até que seja digitado 0 (sentinela).
    Codificação:
      1 -> Candidato A
      2 -> Candidato B
      3 -> Candidato C
      4 -> voto nulo
      5 -> voto em branco
    Calcular e exibir:
      - total de votos para cada candidato (A, B, C)
      - total de votos nulos
      - total de votos em branco
  Observações/boas práticas:
    - validação da leitura (scanf)
    - nomes de variáveis claros
    - mensagens amigáveis ao usuário
*/

int main(void) {                             // início da função principal — ponto de entrada do programa

    /* Variáveis de contagem — inicializadas em zero */
    int votos_candidato_A = 0;               // contador de votos do candidato A (código 1)
    int votos_candidato_B = 0;               // contador de votos do candidato B (código 2)
    int votos_candidato_C = 0;               // contador de votos do candidato C (código 3)
    int votos_nulos = 0;                     // contador de votos nulos (código 4)
    int votos_brancos = 0;                   // contador de votos em branco (código 5)

    int codigo_voto = -1;                    // variável para armazenar o código lido (inicializo com -1 para entrar no loop)

    /* Mensagens iniciais para o usuário */
    printf("CONTAGEM DE VOTOS - ELEICAO\n");
    printf("---------------------------\n");
    printf("Digite o codigo do voto e pressione Enter.\n");
    printf("Codigos: 1=A, 2=B, 3=C, 4=Nulo, 5=Branco. Digite 0 para finalizar.\n\n");

    /* Laço de leitura: continua até o usuário digitar 0 (sentinela) */
    while (1) {                              // while(1) cria um loop infinito que será interrompido internamente
        printf("Informe o codigo do voto (0 para encerrar): ");
        if (scanf("%d", &codigo_voto) != 1) { // scanf tenta ler um inteiro; verifica se a leitura foi bem-sucedida
            // Se a leitura falhar (por exemplo, usuário digitou texto), limpamos o buffer e encerramos com erro
            printf("Entrada invalida. Por favor execute novamente e digite apenas numeros inteiros.\n");
            return 1;                        // encerra o programa com código de erro
        }

        /* Verifica se o código é o finalizador (0) */
        if (codigo_voto == 0) {              // condição de parada: usuário deseja encerrar a votação
            break;                           // interrompe o loop while
        }

        /* Distribui o voto para o contador correspondente */
        switch (codigo_voto) {
            case 1:                         // se o código lido for 1
                votos_candidato_A = votos_candidato_A + 1; // incrementa contador de A
                break;                      // sai do switch
            case 2:                         // se o código lido for 2
                votos_candidato_B = votos_candidato_B + 1; // incrementa contador de B
                break;
            case 3:                         // se o código lido for 3
                votos_candidato_C = votos_candidato_C + 1; // incrementa contador de C
                break;
            case 4:                         // se o código lido for 4
                votos_nulos = votos_nulos + 1;             // incrementa contador de nulos
                break;
            case 5:                         // se o código lido for 5
                votos_brancos = votos_brancos + 1;         // incrementa contador de brancos
                break;
            default:                        // caso o código não esteja entre 0..5
                // informa que o código não é válido, mas não encerra a execução; apenas ignora esse voto
                printf("Codigo invalido: %d. Vote ignorado. Use 1..5 ou 0 para encerrar.\n", codigo_voto);
                break;
        }
    } /* fim do while */

    /* Após encerrar as leituras (digitado 0), exibimos os resultados */
    printf("\nRESULTADO DA CONTAGEM DE VOTOS\n");
    printf("------------------------------\n");
    printf("Votos para o Candidato A (codigo 1): %d\n", votos_candidato_A);
    printf("Votos para o Candidato B (codigo 2): %d\n", votos_candidato_B);
    printf("Votos para o Candidato C (codigo 3): %d\n", votos_candidato_C);
    printf("Votos nulos (codigo 4)             : %d\n", votos_nulos);
    printf("Votos em branco (codigo 5)        : %d\n", votos_brancos);

    return 0;                               // encerra o programa indicando sucesso
}