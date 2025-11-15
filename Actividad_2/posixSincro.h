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

#ifndef POSIX_SINCRO_H
#define POSIX_SINCRO_H


#include <pthread.h>


#define MAX_BUFFERS 8


extern char buf [MAX_BUFFERS][100];
extern int buffer_index;
extern int buffer_print_index;


extern pthread_mutex_t buf_mutex;
extern pthread_cond_t buf_cond;
extern pthread_cond_t spool_cond;


extern int buffers_available;
extern int lines_to_print;


void *producer(void *arg);
void *spooler(void *arg);


#endif

