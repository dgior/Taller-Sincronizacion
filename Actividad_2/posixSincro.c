/******************************************************************
*            Pontificia Universidad Javeriana                     *
*                         ---=---                                 *
*                                                                 *
* Autores: Danna Rojas, María Fernanda Velandia,                  * 
*	Cristian Becerra, Giovanny Duran                          *
* Fecha: 13 Noviembre 2025                                        *
* Docente:  J. Corredor                                           *
* Archivo:  posixSincro.c                                       * 
* Objetivo:                  * 
* Descripción:                                                 *
******************************************************************/


#include "posixSincro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* === VARIABLES GLOBALES DEFINIDAS === */
char buf[MAX_BUFFERS][100];
int buffer_index = 0;
int buffer_print_index = 0;

pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buf_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t spool_cond = PTHREAD_COND_INITIALIZER;

int buffers_available = MAX_BUFFERS;
int lines_to_print = 0;

/* ====================================================== */
/* PRODUCTOR */
void *producer(void *arg) {
    int r;
    int my_id = *((int *)arg);
    int count = 0;

    for (int i = 0; i < 10; i++) {

        /* Bloqueo */
        if ((r = pthread_mutex_lock(&buf_mutex)) != 0) {
            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }

        /* Esperar buffer libre */
        while (!buffers_available)
            pthread_cond_wait(&buf_cond, &buf_mutex);

        /* Seleccionar buffer */
        int j = buffer_index;
        buffer_index = (buffer_index + 1) % MAX_BUFFERS;
        buffers_available--;

        /* Guardar mensaje */
        snprintf(buf[j], sizeof(buf[j]), "Thread %d: %d\n", my_id, ++count);

        lines_to_print++;

        /* Avisar al spooler */
        pthread_cond_signal(&spool_cond);

        /* Desbloqueo */
        if ((r = pthread_mutex_unlock(&buf_mutex)) != 0) {
            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }

        sleep(1);
    }

    return NULL;
}

/* ====================================================== */
/* SPOOLER (CONSUMIDOR) */
void *spooler(void *arg) {
    int r;
    (void)arg;

    while (1) {

        if ((r = pthread_mutex_lock(&buf_mutex)) != 0) {
            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }

        while (!lines_to_print)
            pthread_cond_wait(&spool_cond, &buf_mutex);

        /* Imprimir */
        printf("%s", buf[buffer_print_index]);

        lines_to_print--;
        buffer_print_index = (buffer_print_index + 1) % MAX_BUFFERS;
        buffers_available++;

        pthread_cond_signal(&buf_cond);

        if ((r = pthread_mutex_unlock(&buf_mutex)) != 0) {
            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }
    }

    return NULL;
}

/* ====================================================== */
/* MAIN */
int main() {
    pthread_t prod[3];
    pthread_t sp;

    int ids[3] = {1, 2, 3};

    /* Crear spooler */
    pthread_create(&sp, NULL, spooler, NULL);

    /* Crear 3 productores */
    for (int i = 0; i < 3; i++)
        pthread_create(&prod[i], NULL, producer, &ids[i]);

    /* Esperar productores */
    for (int i = 0; i < 3; i++)
        pthread_join(prod[i], NULL);

    /* No se cancela el spooler en este ejemplo */

    pthread_mutex_destroy(&buf_mutex);
    pthread_cond_destroy(&buf_cond);
    pthread_cond_destroy(&spool_cond);

    return 0;
}

