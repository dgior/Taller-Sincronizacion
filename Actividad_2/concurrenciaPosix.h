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

#ifndef CONCURRENCIA_POSIX_H
#define CONCURRENCIA_POSIX_H


#include <pthread.h>
#include <limits.h>


typedef struct argHilos{
int inicio;
int fin;
int *vector;
int maxparcial;
} param_H;


void *buscarMax(void *parametro);
int maximoValor(int *vec, int n, int nhilos);


#endif

