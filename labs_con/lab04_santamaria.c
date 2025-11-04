/******************************************************************
*
* Pontificia Universidad Javeriana
* Autor: Juan Carlos Santamaria Orjuela
* Materia: Sistemas Operativos
* Docente:     J. Corredor
* Fecha:       30/10/2025
* Tema: sincronización básica con mutex y creación de hilos (Pthreads)
*
* Descripcion:
*       Este programa crea tres hilos que ejecutan una rutina común. Cada hilo, al
*       iniciar, entra a una sección crítica protegida con un mutex para incrementar
*       un contador global y anunciar con printf que su “job” ha comenzado, luego
*       simula trabajo mediante un bucle ocupado (busy-wait) y finalmente imprime que
*       el “job” ha terminado. El hilo principal crea los tres hilos, espera su
*       finalización con pthread_join y destruye el mutex al final.

* Importante para alinear con el código tal cual:
*       - El mutex 'lock' "no se inicializa" antes de su uso (debería hacerse con
*         PTHREAD_MUTEX_INITIALIZER o pthread_mutex_init), por lo que su comportamiento
*         es indefinido; aquí se documenta el uso, no se corrige la lógica.
*       - El mensaje de “finished” se imprime fuera de la sección crítica, por lo que
*         puede mostrar un valor de 'counter' ya modificado por otro hilo.
*
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> // Para la función strerror()

/*
 Identificadores de hilos, contador compartido y mutex sin inicializar.
*/
pthread_t tid[3];
int counter;
pthread_mutex_t lock;

/*
 Esta rutina representa el trabajo de cada hilo. Primero intenta entrar a la
   sección crítica protegiéndose con 'lock' para incrementar el contador global
   'counter' y anunciar el inicio del job. La exclusión mutua garantiza (si el
   mutex estuviera correctamente inicializado) que ese incremento y el mensaje
   de “has started” no se mezclen con otros hilos. Luego ejecuta un bucle ocupado
   para simular carga de trabajo sin bloquear el mutex, y finalmente imprime que
   el job ha terminado. Nótese que la impresión final ocurre fuera de la sección
   crítica, por lo que el valor mostrado de 'counter' puede haber cambiado por
   otros hilos entre el “start” y el “finish”. La función no devuelve resultado.
*/

void *compute(void *arg)
{
    unsigned long i = 0;
/*
   Incrementa 'counter' y anuncia inicio.
*/
    pthread_mutex_lock(&lock);
    counter += 1;
    printf("\nJob %d has started\n", counter);
    pthread_mutex_unlock(&lock);
/*
   Bucle ocupado sin retener el mutex.
*/
    for(i = 0; i < 0xFFFFFFFF; i++);
/*
   Anuncia fin, pero 'counter' pudo cambiar.
*/
    printf("\nJob %d has finished\n", counter);

    return NULL;
}
/*
   El hilo principal crea tres hilos que ejecutan 'compute', verificando el
   resultado de pthread_create mediante el código de error convertido a texto
   con strerror(). Tras lanzar los hilos, realiza tres pthread_join para
   esperar su finalización y, por último, destruye el mutex con
   pthread_mutex_destroy. En este listado, el mutex 'lock' se usa sin haber
   sido inicializado explícitamente, lo cual es un riesgo real de carrera o
   comportamiento indefinido, sin embargo, se respeta el código original y
   se documenta su intención.
*/
int main(void)
{
/*
   Índice de creación y código de error de pthread_create.
*/
    int i = 0;
    int error;
/*
   Crea 3 hilos; reporta error con strerror() si falla.
*/
    while(i < 3)
    {
        error = pthread_create(&(tid[i]), NULL, &compute, NULL);

        if (error != 0)
            printf("\nThread can't be created: [%s]", strerror(error));
        i++;
    }
/*
   Espera la finalización de los tres hilos creados.
*/
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
/*
   Destruye el mutex (no fue inicializado en este código).
*/
    pthread_mutex_destroy(&lock);

    return 0;
}