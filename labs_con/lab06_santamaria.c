/******************************************************************
*
* Pontificia Universidad Javeriana
* Autor: Juan Carlos Santamaria Orjuela
* Materia: Sistemas Operativos
* Docente:     J. Corredor
* Fecha:       30/10/2025
* Tema: suma concurrente de cuadrados con Pthreads y mutex
*
* Descripcion:
*       Este programa lanza 20 hilos POSIX que ejecutan la misma rutina: para cada
*       hilo se pasa un índice entero (1..20) codificado en el puntero de argumento,
*       se calcula su cuadrado y se acumula en una variable global compartida. El
*       acceso a esa variable global (‘acumulado’) se protege con un mutex para
*       evitar condiciones de carrera durante la actualización. El hilo principal
*       crea los hilos, espera su finalización con pthread_join y, al final, muestra
*       el resultado de la suma de cuadrados. La conversión mediante ‘intptr_t’
*       permite transportar enteros a través del parámetro void* de forma segura.
*
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
/*variables globales*/
int acumulado=0;
/*bloqueoC: condicion de carrera*/
pthread_mutex_t bloqueoCC = PTHREAD_MUTEX_INITIALIZER;
/*
   Esta rutina recibe el argumento genérico ‘x’ (void*), lo interpreta como
   entero mediante un cast intermedio a ‘intptr_t’ y obtiene el índice del
   hilo (1..20). Para preservar la consistencia del acumulador frente a
   accesos concurrentes, entra en una sección crítica: toma el mutex,
   suma el cuadrado del índice en la variable global ‘acumulado’ y libera
   el mutex. La operación protegida garantiza ausencia de condiciones de
   carrera en la actualización. No devuelve valor útil (retorna NULL).
*/
void *cuadrados(void *x){
    /*Se castea al tipo entero el puntero de argumento*/
    int xi = (intptr_t)x;

    /*Bloqueo de la sección crítica*/
    pthread_mutex_lock(&bloqueoCC);
    acumulado += xi * xi;
    pthread_mutex_unlock(&bloqueoCC);
    /*Desbloqueo después de modificar la variable compartida*/

    return NULL;
}

/*
   El proceso principal prepara un arreglo de 20 identificadores de hilo y,
   en un primer bucle, crea los hilos con pthread_create pasando a cada uno
   su índice (i+1) codificado como puntero. En un segundo bucle, espera su
   finalización mediante pthread_join, se pasa la dirección de un puntero
   local solo para cumplir la firma (las rutinas devuelven NULL). Tras
   completarse la sincronización, imprime el valor acumulado, que refleja
   la suma de los cuadrados de 1 a 20 calculada de forma segura gracias
   al uso del mutex.
*/
int main(){
    /*Declaración y Creación de 20 hilos*/
    pthread_t WorkersTh[20];
    for(int i = 0; i < 20; i++)
        pthread_create(&WorkersTh[i], NULL, &cuadrados, (void *)(intptr_t)(i + 1));

    /*Esperar a que cada hilo termine*/
    for(int i = 0; i < 20; i++){
        void *acumulado;
        pthread_join(WorkersTh[i], &acumulado);
    }

    /*Se presenta el valor resultado*/
    printf("Valor suma cuadrados = %d \n", (int) acumulado);

    return 0;
}