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
***********************************************************************/



#include "concurrenciaPosix.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

/* ====================================================== */
/* HILO: buscar máximo parcial */
void *buscarMax(void *parametro) {
    param_H *argumentos = (param_H *)parametro;
    int inicio = argumentos->inicio;
    int fin = argumentos->fin;
    int *v = argumentos->vector;

    if (inicio >= fin) {
        argumentos->maxparcial = INT_MIN;
        pthread_exit(NULL);
    }

    int local_max = v[inicio];

    for (int i = inicio + 1; i < fin; i++)
        if (v[i] > local_max)
            local_max = v[i];

    argumentos->maxparcial = local_max;
    pthread_exit(NULL);
}

/* ====================================================== */
/* FUNCIÓN PRINCIPAL PARALELA */
int maximoValor(int *vec, int n, int nhilos) {

    if (n <= 0) return INT_MIN;
    if (nhilos <= 0) nhilos = 1;
    if (nhilos > n) nhilos = n;

    pthread_t *threads = malloc(sizeof(pthread_t) * nhilos);
    param_H *args = malloc(sizeof(param_H) * nhilos);

    if (!threads || !args) {
        free(threads);
        free(args);
        return INT_MIN;
    }

    int base = n / nhilos;
    int rem = n % nhilos;
    int idx = 0;

    for (int t = 0; t < nhilos; ++t) {
        int chunk = base + (t < rem ? 1 : 0);
        args[t].inicio = idx;
        args[t].fin = idx + chunk;
        args[t].vector = vec;
        args[t].maxparcial = INT_MIN;
        idx += chunk;

        pthread_create(&threads[t], NULL, buscarMax, &args[t]);
    }

    int global_max = INT_MIN;
    for (int t = 0; t < nhilos; ++t) {
        pthread_join(threads[t], NULL);

        if (args[t].maxparcial > global_max)
            global_max = args[t].maxparcial;
    }

    free(threads);
    free(args);
    return global_max;
}

/* ====================================================== */
/* MAIN */
int main(int argc, char *argv[]) {

    FILE *fichero;
    int n, nhilos, i;
    int *vec;
    int maximo;

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <fichero> <nhilos>\n", argv[0]);
        exit(-1);
    }

    fichero = fopen(argv[1], "r");
    if (fichero == NULL) {
        perror("No se puede abrir fichero");
        exit(-2);
    }

    fscanf(fichero, "%d", &n);

    vec = malloc(sizeof(int) * n);
    if (!vec) exit(-3);

    for (i = 0; i < n; i++)
        fscanf(fichero, "%d", &vec[i]);

    fclose(fichero);

    nhilos = atoi(argv[2]);

    maximo = maximoValor(vec, n, nhilos);

    printf("Máximo encontrado: %d\n", maximo);

    free(vec);

    return 0;
}

