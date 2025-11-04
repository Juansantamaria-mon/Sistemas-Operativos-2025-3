/******************************************************************
*
* Pontificia Universidad Javeriana
* Autor: Juan Carlos Santamaria Orjuela
* Materia: Sistemas Operativos
* Docente:     J. Corredor
* Fecha:       30/10/2025
* Tema: sincronización con mutex y variables de condición (Pthreads)
*
* Descripcion:
*       Este programa coordina dos hilos que incrementan un contador global usando
*       dos mutex y una variable de condición. El primer hilo (count01) se bloquea
*       cuando el contador está en el intervalo [COUNT_HALT1 .. COUNT_HALT2] y solo
*       continúa cuando el segundo hilo (count02) emite una señal de condición.
*       Ambos hilos protegen el acceso de escritura al contador con un mutex dedicado,
*       y el flujo de “pausa/reanudación” entre hilos se maneja con un segundo mutex
*       y una variable de condición. Cada hilo imprime el valor del contador al
*       incrementarlo y ambos finalizan cuando el contador alcanza COUNT_DONE.
*
*****************************************************************/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>

/*
   Mutex para el contador, mutex para la condición y variable de condición.
*/
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;


/*
   Contador compartido y umbrales de control del flujo.
*/
int count = 0;
#define COUNT_DONE  15
#define COUNT_HALT1 4
#define COUNT_HALT2 11

/*
   Hilo productor controlado que respeta una “zona de pausa”. En un bucle
   infinito, primero adquiere el mutex asociado a la condición y, si el
   contador está en el rango [COUNT_HALT1, COUNT_HALT2], espera sobre la
   variable de condición liberando atómicamente ese mutex hasta recibir una
   señal. Al salir de la espera (o si no estaba en el rango), libera el
   mutex de condición, toma el mutex del contador, incrementa 'count',
   imprime su valor y libera el mutex. Si el contador alcanzó COUNT_DONE,
   retorna NULL para terminar el hilo.
*/
void *count01() {
    for(;;) {
/*
   Pausa si count está en [HALT1..HALT2] hasta que reciba señal.
*/
        pthread_mutex_lock( &condition_mutex );
        while( count >= COUNT_HALT1 && count <= COUNT_HALT2 )
        {
            pthread_cond_wait( &condition_cond, &condition_mutex );
        }
        pthread_mutex_unlock( &condition_mutex );
/*
   Incremento protegido del contador compartido.
*/
        pthread_mutex_lock( &count_mutex );
        count++;
        printf("Counter value functionCount ==> 01 <==: %d\n",count);
        pthread_mutex_unlock( &count_mutex );

        if(count >= COUNT_DONE) return(NULL);
    }
}
/*
   Hilo compañero que “despierta” a count01 cuando éste debe salir de la
   pausa. En cada iteración, toma el mutex de condición y, si el contador
   NO está en el rango de pausa (es decir, es menor a COUNT_HALT1 o mayor
   a COUNT_HALT2), emite una señal con pthread_cond_signal para reanudar
   a quien esté esperando. Luego libera el mutex de condición, entra en la
   sección crítica del contador con su mutex dedicado, incrementa, imprime
   y libera. Termina cuando el contador alcanza COUNT_DONE.
*/
void *count02() {
    for(;;) {
/*
   Si count está fuera de [HALT1..HALT2], envía signal.
*/
        pthread_mutex_lock( &condition_mutex );
        if( count < COUNT_HALT1 || count > COUNT_HALT2 )
        {
            pthread_cond_signal( &condition_cond );
        }
        pthread_mutex_unlock( &condition_mutex );
/*
   Incremento protegido del contador compartido.
*/
        pthread_mutex_lock( &count_mutex );
        count++;
        printf("Counter value functionCount ==> 02 <==: %d\n",count);
        pthread_mutex_unlock( &count_mutex );

        if(count >= COUNT_DONE) return(NULL);
    }
}

/*
   El hilo principal crea dos hilos POSIX que ejecutan count01 y count02,
   respectivamente. Ambos hilos comparten la misma variable global 'count'
   y coordinan su avance mediante 'count_mutex' (para protección del contador)
   y la pareja 'condition_mutex' + 'condition_cond' (para el protocolo de
   espera/señal que detiene a count01 dentro del intervalo controlado).
   El main espera la finalización de ambos hilos con pthread_join y termina.

*/
int main() {
    pthread_t thread1, thread2;
/*
    Lanzar count01 y count02 sin argumentos.
*/
    pthread_create( &thread1, NULL, &count01, NULL);
    pthread_create( &thread2, NULL, &count02, NULL);
/*
    Esperar a que ambos hilos concluyan.
*/
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
    exit(0);
}