**Laboratorios de Programación Concurrente con Pthreads)**

**Pontificia Universidad Javeriana**  
**Autor:** Juan Carlos Santamaría Orjuela  
**Materia:** Sistemas Operativos  
**Docente:** J. Corredor  
**Fecha:** Octubre  2025  


## Descripción general
Este proyecto recopila una serie de **laboratorios en lenguaje C** orientados al aprendizaje de la **programación concurrente con Pthreads (POSIX Threads)**.  
Cada práctica aborda un concepto clave: **creación de hilos, sincronización, exclusión mutua y variables de condición**, mostrando tanto implementaciones correctas como errores intencionados para análisis.

## Estructura de archivos
---
├── lab00_santamaria.c   → Creación dinámica de hilos con argumentos.
├── lab01_santamaria.c   → Ejemplo básico de dos hilos concurrentes.
├── lab02_santamaria.c   → Uso de mutex y contador compartido.
├── lab03_santamaria.c   → Sincronización con variable de condición.
├── lab04_santamaria.c   → Uso incorrecto de mutex (análisis de error).
├── lab05_santamaria.c   → Condición de carrera sin mutex.
├── lab06_santamaria.c   → Corrección del lab05 con exclusión mutua.
├── lab07_santamaria.c   → Espera con predicado (mutex + condición).
├── lab08_santamaria.c   → Versión simplificada del patrón de condición.
└── Makefile             → Compilación automática de todos los laboratorios.
---

## Objetivos generales
- Comprender el modelo de **ejecución concurrente** con hilos POSIX.  
- Identificar y resolver **condiciones de carrera**.  
- Implementar mecanismos de **sincronización** mediante `pthread_mutex_t` y `pthread_cond_t`.  
- Analizar comportamientos no deterministas y su corrección mediante exclusión mutua.  


## Compilación y ejecución
### Compilar todos los laboratorios:

make


### Ejecutar un laboratorio específico:

./lab03_santamaria


### Limpiar binarios generados:

make clean




## Resumen de prácticas
---
| **Lab** | **Tema** | **Propósito** | **Resultado esperado** |
|----------|-----------|----------------|-------------------------|
| 00 | Creación de hilos | Crear múltiples hilos con argumentos. | Impresiones en orden no determinista. |
| 01 | Hilos básicos | Ejecutar dos hilos independientes. | Impresiones alternadas sin sincronización. |
| 02 | Mutex y contador | Usar exclusión mutua parcial. | Valor final variable por no usar join. |
| 03 | Mutex + condición | Coordinar hilos mediante señales. | Pausa/reanudación entre hilos. |
| 04 | Error de mutex | Mostrar consecuencias de no inicializar. | Posible fallo o comportamiento indefinido. |
| 05 | Condición de carrera | Sumar sin protección de mutex. | Resultado inconsistente entre ejecuciones. |
| 06 | Mutex corregido | Evitar la carrera del lab05. | Resultado estable y correcto (2870). |
| 07 | Espera con predicado | Comunicación segura entre hilos. | Sincronización correcta antes/después del cambio. |
| 08 | Versión simplificada | Reforzar el patrón anterior. | Igual funcionalidad con menos código. |
---

## Requisitos
- **Sistema:** Linux (Ubuntu)  
- **Compilador:** GCC ≥ 9.0  
- **Biblioteca:** POSIX Threads (`pthread`)  



## Autor
**Juan Carlos Santamaría Orjuela**  
Estudiante de Ingeniería de Sistemas  
**Pontificia Universidad Javeriana — 2025**
