#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TRUE 1

typedef struct alarm_tag {
    int seconds;
    char message[64];
} alarm_t;

/* Função de thread */
void *alarm_thread(void *arg) {
    alarm_t *alarm = (alarm_t *)arg;
    int status;
    status = pthread_detach(pthread_self());
    if (status != 0) {
        fprintf(stderr, "Erro executando pthread_detach()\n");
        exit(EXIT_FAILURE);
    }
    sleep(alarm->seconds);
    printf("(%d) %s\n", alarm->seconds, alarm->message);
    free(alarm);
    return NULL;
}

int main(int argc, char *argv[]) {
    int status;
    char line[128];
    alarm_t *alarm;
    pthread_t thread;
    while (TRUE) {
        printf("Alarme> ");
        /* Teclou CTRL + D -> fim de arquivo e termina */
        if (fgets(line, sizeof(line), stdin) == NULL)
            exit(EXIT_SUCCESS);
        /* Só ENTER -> repete a entrada */
        if (strlen(line) <= 1)
            continue;
        alarm = (alarm_t *)malloc(sizeof(alarm_t));
        if (alarm == NULL) {
            perror("Erro executando malloc()");
            exit(EXIT_FAILURE);
        }
        if (sscanf(line, "%d %64[^\n]", &alarm->seconds, alarm->message) < 2) {
            fprintf(stderr, "Comando inválido!\n");
            free(alarm);
        } else {
            status = pthread_create(&thread, NULL, alarm_thread, alarm);
            if (status != 0) {
                fprintf(stderr, "Erro executando pthread_create()!\n");
                free(alarm);
            }
        }
    }
}