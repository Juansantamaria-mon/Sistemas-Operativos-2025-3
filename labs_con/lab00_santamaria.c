/******************************************************************
*
* Pontificia Universidad Javeriana
* Autor:Juan Carlos Santamaria Orjuela
* Materia: Sistemas operativos
* Docente:     J. Corredor
* Fecha:       30/10/2025
* Tema:uso interfaz de creacion de hilos PTHREAD
*
* Descripcion:
*   Este programa ilustra la concurrencia con Pthreads en un entorno POSIX. A partir
*   de un parámetro entero positivo (NUM) recibido por línea de comandos, el proceso
*   principal crea exactamente NUM hilos. Cada hilo recibe, como argumento, la dirección
*   de una celda del arreglo 'tareas' que contiene un identificador entero en el rango
*   [1..NUM], lee ese identificador y lo imprime en la salida estándar con el formato
*   "Tarea :- X -". El proceso principal coordina la finalización de todos los hilos
*   realizando un pthread_join por cada uno antes de terminar. La dirección pasada a
*   cada hilo es segura porque el arreglo 'tareas' permanece válido hasta después de
*   todos los join, y no hay escrituras concurrentes sobre las celdas usadas por los hilos.
*
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>

/*
   La función 'funcion' es el punto de entrada de cada hilo. Recibe por
   parámetro un puntero genérico que, por convenio, apunta a un entero
   válido dentro del arreglo 'tareas' del hilo principal. El hilo lee ese
   entero como identificador de tarea y lo muestra por pantalla con un
   mensaje sencillo. No modifica memoria compartida ni devuelve un valor
   significativo, por lo que finaliza retornando NULL.
*/
static void *funcion(void *arg){
    int tarea = *(int*)arg;  // Lee el identificador de tarea desde el puntero recibido.
    printf("Tarea :- %d -\n", tarea); // Imprime la marca de progreso de este hilo.
    return NULL;  // Finaliza el hilo (equivalente a pthread_exit(NULL)).
}

/*
   La función 'main' coordina todo el flujo. Primero comprueba que se haya
   pasado exactamente un argumento; de no ser así, muestra el uso esperado
   y finaliza. Luego convierte ese argumento a entero con atoi() sin
   validaciones adicionales (por lo que valores no numéricos producirán 0).
   Con el valor N resultante, declara dos arreglos automáticos (VLA):
   'tareas' para almacenar identificadores de 1..N y 'hilos' para guardar
   los manejadores de cada hilo. A continuación, inicializa cada tareas[i]
   con i+1 y crea el hilo correspondiente pasando &tareas[i] como argumento,
   sin verificar el código de retorno de pthread_create. Finalmente, realiza
   un bucle de pthread_join sobre todos los hilos para esperar su
   finalización, también sin revisar códigos de retorno, y termina devolviendo 0.
*/
int main (int argc, char *argv[]){
/*
 Exige 1 argumento (NUM); si falta, muestra uso y termina.
*/
    if (argc != 2){
        printf("\t$ ./lab00_santamaria\n");
        exit(0);
    }

    int N = atoi(argv[1]);
    int tareas[N];
    pthread_t hilos[N];

/*
   Inicializa tareas[i]=i+1 y lanza el hilo i con ese ID.
*/
    for (int i = 0; i < N; i++){
        tareas[i] = i + 1;
        pthread_create(&hilos[i], NULL, funcion, &tareas[i]);
    }
/*
    Espera la finalización de cada hilo creado.
*/
    for (int i = 0; i < N; i++){
        pthread_join(hilos[i], NULL);
    }
    return 0;
}