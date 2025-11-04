/******************************************************************
*
* Pontificia Universidad Javeriana
* Autor: Juan Carlos Santamaria Orjuela
* Materia: Sistemas Operativos
* Docente:     J. Corredor
* Fecha:       30/10/2025
* Tema: sincronización con variable de condición y mutex (Pthreads)
*
* Descripcion:
*       Este programa demuestra el uso coordinado de un mutex y una variable de
*       condición para comunicar eventos entre hilos. Un hilo “reportar” toma el
*       mutex, lee un valor compartido y espera sobre la variable de condición
*       hasta que otro hilo “asignar” actualiza dicho valor y emite la señal.
*       El diseño garantiza que la lectura “después de la señal” ocurra con el
*       mismo mutex tomado, evitando condiciones de carrera y pérdidas de señal.
*       Se utiliza un flag booleano para convertir la espera en un patrón de
*       “wait con predicado” (while) que maneja correctamente señales espurias.
*
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>   // para sleep()

/* Variables globales */
pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int valor = 100;
bool notificar = false;

/*
   Este hilo adquiere el mutex para observar de forma consistente el estado
   compartido (valor y flag). Imprime el valor “antes de la señal” y, si el
   evento aún no ha ocurrido (notificar == false), entra en espera atómica
   con pthread_cond_wait: libera el mutex y se bloquea en la variable de
   condición, despertando solo cuando recibe señal y puede volver a adquirir
   el mutex. Al salir del bucle (predicado satisfecho), imprime el valor
   “después de la señal”, suelta el mutex y termina. El uso del bucle while
   evita problemas por señales desordenadas o carreras entre señalización y espera.
*/
void *reportar(void *nousado){
    pthread_mutex_lock(&mutex);
    printf("Antes de la señal, el valor es: %d\n", valor);
    while(!notificar){
        pthread_cond_wait(&var_cond, &mutex);
    }

    printf("Después de la señal, el valor es: %d\n", valor);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

/*
   Este hilo simula trabajo previo con sleep(1) y luego adquiere el mutex
   para actualizar de manera segura el dato compartido. Cambia 'valor',
   establece el flag 'notificar' a true y emite una señal con
   pthread_cond_signal, garantizando que el hilo en espera pueda despertar
   cuando recupere el mutex. Libera el mutex y finaliza. Este patrón
   (actualizar estado + señal bajo el mismo lock) es la forma correcta de
   sincronizar productores/consumidores de eventos.
*/
void *asignar(void *nousado){
    sleep(1); // Espera para simular cambio posterior
    pthread_mutex_lock(&mutex);
    valor = 20;
    notificar = true;
    pthread_cond_signal(&var_cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

/*
   El proceso principal crea dos hilos: 'reportar' y 'asignar'. El primero
   esperará la notificación, el segundo actualizará el estado y emitirá la
   señal. Finalmente, el main sincroniza la terminación de ambos con
   pthread_join y concluye. No se imprime valor adicional desde el main,
   pues la observación del estado antes/después está encapsulada en los
   propios hilos.
*/
int main(int argc, char *argv[]){
    pthread_t reporte, asigne; //Identificadores de los dos hilos

    //Lanzar hilo que espera y hilo que señala
    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);
   //Esperar a que ambos hilos finalicen
    void *nousado;
    pthread_join(reporte, &nousado);
    pthread_join(asigne, &nousado);

    return 0;
}