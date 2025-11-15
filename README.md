# Taller 03 – Sincronización POSIX (Semáforos y Pthreads)

Este repositorio contiene la implementación del Taller 03 de Sistemas Operativos, enfocado en poner en práctica mecanismos de **concurrencia** y **sincronización** usando la interfaz **POSIX**.

El proyecto se divide en **dos actividades independientes**:

- **Actividad 1:** sincronización entre procesos usando **memoria compartida POSIX** y **semáforos con nombre**.  
- **Actividad 2:** sincronización entre hilos usando **pthreads**, **mutex** y **variables de condición**.

---

## 1. Estructura del repositorio

```text
.
├── Actividad_1/
│   ├── header.h
│   ├── productor.c
│   ├── consumidor.c
│   └── Makefile
└── Actividad_2/
    ├── concurrenciaPosix.c
    ├── concurrenciaPosix.h
    ├── posixSincro.c
    ├── posixSincro.h
    ├── prueba.txt
    └── Makefile
