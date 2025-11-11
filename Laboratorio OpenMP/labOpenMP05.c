/******************************************************************
 * Autor: Juan Carlos Santamaria
 * Materia: Sistemas Operativos
 * Fecha: 06 noviembre 2025
 * Tema:Introducción OpenMP
 * ---------------------------------------------------------------
 * ===============================================================
 * Resumen
 *   Paraleliza un bucle que acumula sumas de sin(j) mediante una
 *   cláusula de reducción (+) sobre 'resSumatoria'. Reporta el máximo
 *   de hilos que el runtime de OpenMP planea usar y fija el número de
 *   hilos a emplear, se usa una región 'parallel' externa y
 *   otra 'parallel for' interna; si el paralelismo anidado está
 *   deshabilitado, cada hilo externo ejecuta el for
 *   completo y su resultado se suma repetidamente, inflando el total.
 *
 ******************************************************************/

#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/* Variables globales para medir tiempo con gettimeofday */
struct timeval inicio, fin;

/* Marca de inicio de medición */
void InicioMuestra() {
    gettimeofday(&inicio, (void *)0);
}

/* Marca de fin y retorna duración en microsegundos */
void FinMuestra() {
    gettimeofday(&fin, (void *)0);
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec -= inicio.tv_sec;
    double tiempo = (double)(fin.tv_sec * 1000000 + fin.tv_usec);
  printf("%9.0f\n", tiempo);
}

/*Se implementa la funcion de sumatoria*/
double fsum(int i) {
    int inicio = i * (i + 1) / 2; // Variable de inicio, esta tendra los valores 0,1,3,..., Por la formula del triangulo
    int fin = inicio + i; //El limite del bloque
    double valor_sum = 0; //Acumulador en cual estar i
//Recorrera j en el rango del bloque
    for (int j = inicio; j < fin; j++) {
        valor_sum += sin(j);//Suma sin(j) al acumulador y esto durante todo el bloque
    }

    return valor_sum; //Retornara la suma del bloque
}

int main() {
    double resSumatoria = 0;//Acumulador global
    int rep = 30000;//Numero de iteraciones en el ciclo FOR

    int numHilos = 4;//Cantidad de hilos a utilizar
    int maxCores = omp_get_max_threads();//Le asignaremos el numero maximo de hilos por defecto

/* Aca se ara un reporte  de el numero maximo de hilos por defecto y los que se asignaron en numHilos*/
    printf("Número máximo de hilos: %d\n", maxCores);
    printf("Se fija el número de hilos deseado: %d\n", numHilos);

    omp_set_num_threads(numHilos);//Fija el numero de hilos que se utilizaran para las regiones paralelas

    printf("Número de hilos fijados: %d\n", numHilos);

 //Inicio de la muestra de los hilos
        InicioMuestra();
    // Región paralela por OpenMP
/*
En este bloque se creara la region paralela y reparte el FOR, 'reduction(+:resSumatoria)'
crea acumuladores privados por hilo y los combina al final con suma.
*/
    #pragma omp parallel
    {
        #pragma omp parallel for reduction(+:resSumatoria)
        for (int i = 0; i < rep; i++) {
            resSumatoria += fsum(i);//Cada iteracion estara dando un aporte al acumulador del bloque que es la variable privada
        }// OpenMP fusiona los privados en resSumatoria al terminar
    }
        printf("Microsegunsos: ");
        FinMuestra();

    printf("Resultado final de la sumatoria: %0.2f\n", resSumatoria);//Se  mostrara la suma al final de la ejecucion

    return 0;
}
/*
Nota:
   La reducción (+) es correcta dentro de la región 'parallel for', pero al estar anidada
   dentro de una 'parallel' externa, y con anidamiento deshabilitado, cada hilo externo ejecuta
   el bucle completo y el resultado parcial vuelve a sumarse sobre 'resSumatoria', por lo que el
   total queda multiplicado, si se desea una sola pasada con reducción global, bastaría una única
   directiva 'parallel for reduction(+:resSumatoria)'. Además, 'omp_get_max_threads()' informa un
   máximo del runtime, y las sumas en punto flotante pueden variar en su
   último decimal por el orden de acumulación.
*/