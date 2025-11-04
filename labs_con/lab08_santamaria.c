/******************************************************************
*
* Pontificia Universidad Javeriana
* Autor: Juan Carlos Santamaria Orjuela
* Materia: Sistemas Operativos
* Docente:     J. Corredor
* Fecha:       30/10/2025
* Tema: sincronización con mutex y variable de condición (Pthreads)
*
* Descripcion:
*       Este programa muestra el patrón clásico de “espera con predicado” usando
*       un mutex y una variable de condición. Un hilo (reportar) toma el candado,
*       verifica el predicado `notificar` y, mientras sea falso, espera en la
*       variable de condición liberando atómicamente el mutex. Cuando el otro hilo
*       (asignar) actualiza el estado compartido (`valor`) y pone `notificar=true`,
*       señala la condición y el hilo en espera se reanuda, vuelve a tomar el
*       candado y lee el valor actualizado de forma consistente. El flujo garantiza
*       que la lectura ocurra bajo protección del mismo mutex, evitando condiciones
*       de carrera y pérdidas de señal. El `while` frente a `if` maneja correctamente
*       señales espurias y carreras entre señalización y espera.
*
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

/**variables globales**/
int valor = 100;
bool notificar = false;

/*bloqueoCC: condición de carrera*/
pthread_mutex_t bloqueoCC = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condCC   = PTHREAD_COND_INITIALIZER;

/*
   Este hilo implementa el lado “consumidor/esperador”. Entra a la sección
   crítica tomando el mutex y revisa el predicado `notificar`. Mientras el
   predicado no se haya cumplido, llama a `pthread_cond_wait`, que libera
   atómicamente el mutex y bloquea al hilo hasta recibir una señal. Al
   despertarse, `pthread_cond_wait` vuelve a adquirir el mutex antes de
   retornar, permitiendo revalidar el predicado y, una vez satisfecho,
   leer el dato compartido `valor` de forma consistente. Finalmente libera
   el mutex y termina.
*/
void *reportar(void *nousada){
    pthread_mutex_lock(&bloqueoCC);
    while(!notificar)
        pthread_cond_wait(&condCC, &bloqueoCC);
    printf("\n\tEl valor es: %d\n", valor);
    pthread_mutex_unlock(&bloqueoCC);
    return NULL;
}

/*
   Este hilo representa el “productor/señalizador”. Primero actualiza la
   variable compartida `valor` (la asignación a `valor` ocurre fuera
   del candado tal como está el código, en diseños más estrictos suele
   hacerse bajo el mismo mutex). Luego toma el mutex para cambiar el
   predicado `notificar` a true y emite `pthread_cond_signal` mientras aún
   mantiene el candado. Señalar con el lock tomado asegura que el estado
   visible para el hilo que despierta esté coherente al momento de reanudar.
   Finalmente libera el mutex y termina.
*/
void *asignar(void *nousada){
    valor = 20;
    pthread_mutex_lock(&bloqueoCC);
    notificar = true;
    pthread_cond_signal(&condCC);
    pthread_mutex_unlock(&bloqueoCC);
    return NULL;
}

/*
   El hilo principal crea dos hilos POSIX: uno que espera la señal (`reportar`)
   y otro que actualiza el estado y emite la señal (`asignar`). Posteriormente
   sincroniza la finalización de ambos con `pthread_join` y concluye. El valor
   se imprime dentro de `reportar`, ya protegido por el mutex, por lo que el
   main no realiza lecturas adicionales.
*/
int main(){
    /*Declaración y Creación*/
    pthread_t reporte, asigne;

    pthread_create(&reporte, NULL, &reportar, NULL);
    pthread_create(&asigne, NULL, &asignar, NULL);

    /*Creo variable para recoger valor al esperar*/
    void *nousada;
    pthread_join(reporte, &nousada);
    pthread_join(asigne, &nousada);

    return 0;
}