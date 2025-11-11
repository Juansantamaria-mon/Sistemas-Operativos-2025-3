/******************************************************************
 * Autor: Juan Carlos Santamaria
 * Materia: Sistemas Operativos
 * Fecha: 06 noviembre 2025
 * Tema:Introducción OpenMP
 * ---------------------------------------------------------------
 * ===============================================================
 * Resumen
 *      Este programa muestra el funcionamiento del modelo
 *      de paralelismo de OpenMP. Crea una región paralela en la que
 *      múltiples hilos ejecutan un mismo bloque de código de forma
 *      concurrente. Un hilo mostrara la cantidad de
 *      hilos activos en la ejecución, mientras que cada hilo imprime
 *      su identificador. Permite observar la ejecución simultánea,
 *      el control de hilos.
 *
 ******************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

 int maxCores= omp_get_max_threads();//Consulta el maximo de hilos que puede usar el runtime por defecto
 printf("Numero maximo de hilos en OpenMP: %d \n", maxCores);
/*Region Paralela por OMP*/

#pragma omp parallel //Se crea un equipo de hilos y cada hilo se ejecutara en el bloque  compuesto que sigue
    {


        #pragma omp single
        {
            printf("OpenMP activo con %d hilos\n", omp_get_num_threads());
        }
        // Código que será ejecutado por todos los hilos
        printf("Hello World desde el thread %d\n", omp_get_thread_num());
    }

    return 0;
}
/*
Nota:
Este código muestra la estructura mínima de un programa paralelo en OpenMP.
Permite visualizar la creación de hilos, la ejecución concurrente de instrucciones
y el uso de la directiva 'single' para ejecutar una sección de manera exclusiva,
sirviendo como base para la comprensión del paralelismo compartido.
*/