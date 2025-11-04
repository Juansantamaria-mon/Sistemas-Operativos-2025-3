/******************************************************************
*
* Pontificia Universidad Javeriana
* Autor: Juan Carlos Santamaria Orjuela
* Materia: Sistemas Operativos
* Docente:     J. Corredor
* Fecha:       30/10/2025
* Tema: cálculo concurrente de suma de cuadrados con Pthreads
*
* Descripcion:
*       Este programa lanza 20 hilos POSIX que ejecutan la misma rutina: reciben un
*       entero (del 1 al 20) por conversión de puntero y acumulan su cuadrado en una
*       variable global compartida. El hilo principal crea los hilos, luego espera su
*       terminación con pthread_join y finalmente muestra un “resultado”. En esta
*       versión, la acumulación se hace sobre una variable global sin protección
*       (concurrencia sin mutex), por lo que existe condición de carrera: el valor
*       final de ‘acumulado’ puede variar entre ejecuciones. Además, el join captura
*       un retorno tipo puntero en una variable local llamada también ‘acumulado’ y se
*       imprime ese puntero convertido a int, no necesariamente la suma global.
*
*****************************************************************/

#include <stdio.h>      // printf
#include <stdlib.h>     // exit, general utilities
#include <pthread.h>    // manejo de hilos (pthread_create, pthread_join)
#include <stdint.h>     // intptr_t para convertir punteros a enteros

/**variables globales**/
int acumulado = 0;

/*
   Esta rutina recibe un argumento ‘x’ como void*, que se interpreta mediante
   cast a ‘intptr_t’ y luego a ‘int’ para obtener el valor entero del índice
   del hilo (1..20). Calcula el cuadrado de ese entero y lo suma en la
   variable global ‘acumulado’. No retorna un resultado útil (NULL). Dado que
   ‘acumulado’ es compartido y no se protege con mutex, múltiples hilos pueden
   escribir simultáneamente, provocando condición de carrera y resultados
   no deterministas. El cast por ‘intptr_t’ evita warnings al pasar enteros
   por puntero.
*/
void *cuadrados(void *x){
    /*Se castea al tipo entero el puntero de argumento*/
    int xi = (intptr_t)x;
    acumulado += xi * xi;
    return NULL;
}

/*
   El proceso principal prepara un arreglo de 20 identificadores de hilo y
   lanza cada hilo pasando como “argumento” su índice (1..20) codificado en
   un puntero. A continuación, realiza un bucle de joins para esperar a que
   todos terminen. En este join, se usa una variable local llamada también
   ‘acumulado’ para recibir el puntero de salida (si lo hubiera), lo que
   enmascara la global y no aporta al cómputo. Finalmente, se imprime “Valor
   suma cuadrados” casteando ese puntero local a int, que no refleja
   necesariamente la suma global real. La intención aparente era imprimir la
   variable global ‘acumulado’. */
int main(){
    /*Declaración y Creación de 20 hilos*/
    pthread_t WorkersTh[20];
    for(int i = 0; i < 20; i++)
        pthread_create(&WorkersTh[i], NULL, &cuadrados, (void *)(intptr_t)(i + 1));

    /*Join de cada hilo; se captura un puntero en una variable local. */
    for(int i = 0; i < 20; i++){
        void *acumulado;
        pthread_join(WorkersTh[i], &acumulado);
    }

    /*Se presenta el valor resultado*/
    printf("Valor suma cuadrados = %d \n", (int) acumulado);
    return 0;
}
