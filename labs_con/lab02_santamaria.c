/******************************************************************
*
*Pontificia Universidad Javeriana
*Autor: Juan Carlos Santamaria Orjuela
*Materia: Sistemas Operativos
*Docente:     J. Corredor
*Fecha:       30/10/2025
*Tema: uso de mutex y contadores compartidos con Pthreads
*
* Descripcion:
*       Este programa crea NTHREADS hilos que ejecutan una función común. Cada hilo
*       imprime su “número de hilo” (valor leído desde un puntero recibido como
*       argumento) y su identificador con pthread_self(). Luego entra a una sección
*       crítica protegida por un mutex para incrementar un contador global compartido
*       y sale de la región crítica. El hilo principal lanza los hilos en un bucle y,
*       sin esperar su finalización, imprime el valor final del contador. Tal como está
*       escrito, el programa "no sincroniza" la finalización de los hilos mediante
*       pthread_join y "pasa la dirección de la misma variable de bucle `i`" a todos
*       los hilos, lo que puede producir que varios hilos lean el mismo valor (comportamiento
*       no determinista). El incremento del contador sí es seguro frente a condiciones de
*       carrera gracias al mutex.
*
*****************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

/*
   Número de hilos, mutex inicializado estáticamente y contador compartido.
*/

#define NTHREADS 10
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

/*
   Esta función recibe un puntero genérico que el programa interpreta como
   la dirección de un entero “número de hilo”, imprimir el número y el ID
   del hilo. A continuación, entra a la sección crítica con pthread_mutex_lock
   sobre 'mutex1', incrementa el contador global 'counter' y libera el candado
   con pthread_mutex_unlock. Con esto, el acceso de escritura a 'counter' es
   atómico respecto de otros hilos, y se evita la condición de carrera en el
   incremento. No retorna un valor útil (NULL).
*/
void *thread_function(void *arg) {
    int i = *(int *)(arg);
    printf("Thread number: %d | Thread ID %ld\n", i, pthread_self());
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);
}

/*
   El hilo principal declara un arreglo de identificadores 'thread_id' para
   NTHREADS hilos y dos variables de bucle. Recorre un ciclo de creación en el
   que invoca pthread_create, pasando siempre la dirección de la misma
   variable de bucle 'i' como argumento a todos los hilos. Esto implica que
   los hilos pueden leer valores distintos (o repetidos) de 'i' según su
   momento de ejecución, produciendo resultados no deterministas sobre el
   “número de hilo” impreso. Tras crear los hilos, el programa imprime el
   valor “final” del contador **sin esperar** a que los hilos terminen, por
   lo que el valor mostrado puede ser 0 u otro número menor a NTHREADS según
   el planificador.
*/
void main() {
 /*
   Identificadores de hilos y variables de bucle.
*/
    pthread_t thread_id[NTHREADS];
        int i, j;
/*
   Crea NTHREADS hilos, pasando &i como argumento compartido.
*/
    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&thread_id[i], NULL, thread_function, &i);
    }

    printf("Final counter value: %d\n", counter);
}