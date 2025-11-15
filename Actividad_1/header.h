/******************************************************************
*            Pontificia Universidad Javeriana                     *
*                         ---=---                                 *
*                                                                 *
* Autores: Danna Rojas, María Fernanda Velandia,                  * 
*	Cristian Becerra, Giovanny Duran                          *
* Fecha: 13 Noviembre 2025                                        *
* Docente:  J. Corredor                                           *
* Archivo:  header.h                                              * 
* Objetivo: Declarar funciones auxiliares para                    *
*	    la multiplicación clásica de matrices                 *
*	    utilizando procesos mediante fork().                  * 
* Descripción:                                                    *
*	- Funciones de inicialización, impresión y                *
*	  multiplicación parcial.                                 *
* 	- Gestión de memoria compartida y medición de tiempos     *
*	  de ejecución                                            *
******************************************************************/

#ifndef HEADER_H
#define HEADER_H

#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER 5

typedef struct {
    int bus[BUFFER];
    int entrada;
    int salida;
} compartir_datos;

#define SHM_NAME "/memoria_compartida"
#define SEM_VACIO "/vacio"
#define SEM_LLENO "/lleno"

#endif

