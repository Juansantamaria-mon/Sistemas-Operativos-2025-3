/******************************************************************

* Pontificia Universidad Javeriana
* Autor: Juan Carlos Santamaria Orjuela
* Materia: Sistemas Operativos
* Docente:     J. Corredor
* Fecha:       30/10/2025
* Tema: uso de la interfaz de creación de hilos (PTHREAD)
*
* Descripcion:
*	Este programa ejemplifica la creación y coordinación básica de hilos con
*	Pthreads en un entorno POSIX. El proceso principal crea dos hilos
*	independientes que ejecutan la misma función: cada hilo recibe un puntero
*	a cadena como argumento y lo imprime en la salida estándar. Tras lanzar
*	los hilos, el proceso principal espera su finalización con pthread_join,
*	y luego reporta los códigos de retorno de pthread_create para cada hilo.
*	El ejemplo es mínimo y didáctico: no se realiza sincronización adicional
*	porque cada hilo solo lee un mensaje inmutable y escribe en stdout.
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
   Esta función es el punto de entrada que ejecuta cada hilo creado.
   Recibe un puntero genérico (void*) que, por convenio, apunta a una
   cadena C válida y de vida suficiente (en este ejemplo, literales).
   Dentro de la función, el puntero se convierte a char*, se imprime
   el mensaje y se retorna NULL para indicar que no se devuelve un
   resultado. No modifica memoria compartida, su único efecto es E/S
   por stdout, por lo que no requiere mecanismos de sincronización.
*/
void *print_message_function(void *ptr) {
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
    return NULL;
}

/*
   El hilo principal crea dos hilos con pthread_create, pasando a cada
   uno la misma función de entrada pero con argumentos distintos
   (punteros a cadenas literales). Los valores devueltos por
   pthread_create (iret1, iret2) indican éxito o código de error; aquí
   se guardan y se imprimen al final como referencia. Luego, el hilo
   principal llama a pthread_join para cada identificador, bloqueándose
   hasta que ambos hilos concluyen su ejecución, esto garantiza un cierre
   ordenado sin hilos en ejecución al terminar el programa. */

int main() {
/*
   Identificadores de hilos, mensajes a imprimir y códigos de retorno.
*/

    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int iret1, iret2;

    /* Create independent threads each of which will execute function */
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*)  message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*)  message2);

    /* Esperar a que los hilos terminen antes de continuar */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);

    exit(0);
}
