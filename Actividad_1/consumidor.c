/******************************************************************
*            Pontificia Universidad Javeriana                     *
*                         ---=---                                 *
*                                                                 *
* Autores: Danna Rojas, María Fernanda Velandia,                  * 
*	Cristian Becerra, Giovanny Duran                          *
* Fecha: 13 Noviembre 2025                                        *
* Docente:  J. Corredor                                           *
* Archivo:  moClasicaFork.c                                       * 
* Objetivo: Declarar funciones auxiliares para                    *
*	    la multiplicación clásica de matrices                 *
*	    utilizando procesos mediante fork().                  * 
* Descripción:                                                    *
*	- Funciones de inicialización, impresión y                *
*	  multiplicación parcial.                                 *
* 	- Gestión de memoria compartida y medición de tiempos     *
*	  de ejecución                                            *
******************************************************************/

#include "header.h"

int main() {
    // Abrir semáforos existentes
    sem_t *vacio = sem_open(SEM_VACIO, 0);
    sem_t *lleno = sem_open(SEM_LLENO, 0);

    if (vacio == SEM_FAILED || lleno == SEM_FAILED) {
        perror("Error al abrir semáforos");
        exit(EXIT_FAILURE);
    }

    // Abrir memoria compartida existente
    int fd_compartido = shm_open(SHM_NAME, O_RDWR, 0644);
    if (fd_compartido < 0) {
        perror("Error al abrir memoria compartida");
        exit(EXIT_FAILURE);
    }

    compartir_datos *compartir = mmap(NULL, sizeof(compartir_datos),
                                      PROT_READ | PROT_WRITE, MAP_SHARED, fd_compartido, 0);
    if (compartir == MAP_FAILED) {
        perror("Error en mmap consumidor");
        exit(EXIT_FAILURE);
    }

    // Inicializar índice de salida
    compartir->salida = 0;

    // Bucle de consumo
    for (int i = 1; i <= 10; i++) {
        sem_wait(lleno); // Esperar a que haya elementos
        int item = compartir->bus[compartir->salida];
        printf("Consumidor: Consume %d\n", item);
        compartir->salida = (compartir->salida + 1) % BUFFER;
        sem_post(vacio); // Liberar un espacio
        sleep(2);
    }

    // Liberar recursos
    munmap(compartir, sizeof(compartir_datos));
    close(fd_compartido);
    sem_close(vacio);
    sem_close(lleno);

    // Limpieza final de semáforos y memoria compartida
    sem_unlink(SEM_VACIO);
    sem_unlink(SEM_LLENO);
    shm_unlink(SHM_NAME);

    printf("Consumidor finalizado.\n");
    return 0;
}

