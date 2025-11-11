/******************************************************************
 * Autor: Juan Carlos Santamaria
 * Materia: Sistemas Operativos
 * Fecha: 06 noviembre 2025
 * Tema:Introducción a OpenMP
 * ---------------------------------------------------------------
 * ===============================================================
 * Resumen
 *   Este programa fija el número de hilos desde un argumento, informa el máximo
 *   potencial del runtime (omp_get_max_threads), configura el equipo
 *   con omp_set_num_threads y ejecuta una región paralela donde cada
 *   hilo imprime su ID; permite verificar la configuración y la
 *   ejecución concurrente básicas en OpenMP.
 *
 ******************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
//Verifica que los argumentos que se pasaron por consola deban ser el numero de hilos para que sea el parametro
        if(argc != 2){
         printf("Error \n\t$./ejecutable numHilos\n");
         exit(0);
        }
        int numHilos = (int) atoi(argv[1]);//Se convierte el argumento en entero
        int maxCores = omp_get_max_threads();//Se obtiene el maximo de hilos disponibles
        printf("Numero maximo de Cores de SO: %d \n", maxCores);

/*Se fija el numero de hilos deseado: numHilos*/
        omp_set_num_threads(numHilos);
/*Region Paralela por OMP*/

#pragma omp parallel
        {
        printf("Hilo ID de Region Paralela: %d \n", omp_get_thread_num());
        }
return 0;
}
/* Nota:
   Este programa es un demo mínimo de OpenMP que valida, de forma directa,
   la asignación de hilos y la ejecución concurrente, primero reporta
   el máximo potencial del runtime, luego fija el tamaño del equipo
   con omp_set_num_threads y, ya dentro de la región paralela, cada hilo imprime su
   identificador, la salida puede entrelazarse por concurrencia, además, el valor
   “máximo” mostrado es del runtime de OpenMP (puede no coincidir con los núcleos
   físicos del sistema).
*/