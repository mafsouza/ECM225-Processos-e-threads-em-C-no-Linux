/* Cabeçalhos necessários ‐> não precisa adicionar mais nada */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1

int main(int argc, char *argv[]) {
    /* para armazenar os segundos do alarme */
    int seconds;
    
    /* para ler uma linha de entrada */
    char line[128];
    
    /* para armazenar a mensagem do usuário */
    char message[64];
    
    /* para obter o resultado de fork() */
    pid_t pid;
    
    while (TRUE) {
        printf("Alarme> ");
        /* Se teclou CTRL + D -> fim de arquivo e termina */
        if (fgets(line, sizeof(line), stdin) == NULL)
            exit(EXIT_SUCCESS);
        /* Só ENTER -> repete a entrada */
        if (strlen(line) <= 1)
            continue;
        /* Senão, usar sccanf() para decompor a linha em número e mensagem
           o especificador 64[^\n] representa "aceite até 64 caracteres que
           não sejam '\n'". Retorna o número de argumentos analisados. */
        if (sscanf(line, "%d %64[^\n]", &seconds , message) < 2)
            fprintf(stderr, "Comando inválido!\n");
        else {
            /* É APENAS ESTE ELSE QUE PRECISA SER TERMINADO */
            /* Executar fork(), obtendo seu resultado na variável pid*/
            /* SE o resultado de fork() for negativo , exibir uma mensagem
               de erro e terminar com falha*/
            /* SE o resultado de fork() for ZERO, escrever o código do
               PROCESSO-FILHO assim:
                 * Dormir a quantidade de segundos especificada
                 * Exibir os segundos passados e a mensagem associada
                 * Terminar normalmente
               SENÃO escrever o código do PROCESSO-PAI asssim:
                 * FAÇA (do)
                    * Aguarde o PID de um processo filho
                    * SE este PID tiver valor ‐1,
                       * Apresentar uma mensagem indicando erro na espera
                         de processo-filho
                       * Terminar o processo com falha
                   ENQUANTO (while) o PID obtido seja diferente de ZERO
            */
        }
    }
}
