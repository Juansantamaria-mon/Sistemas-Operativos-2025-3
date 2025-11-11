/******************************************************************
 * Autor: Juan Carlos Santamaria
 * Materia: Sistemas Operaivos
 * Fecha: 06 noviembre 2025
 * Tema:Introducción OpenMP
 * ---------------------------------------------------------------
 * ===============================================================
 * Resumen
 *   Paraleliza un bucle que acumula sin(j) en bloques dependientes
 *   de i y mide el tiempo en microsegundos. Reporta el máximo de hilos
 *   que el runtime de OpenMP planea usar y fija el número de hilos,hay
 *   una región 'parallel' externa y otra 'parallel for'
 *   interna, si el paralelismo anidado está deshabilitado,
 *   cada hilo externo ejecuta el for completo y su resultado se suma
 *   repetidamente.
 *
 ******************************************************************/

#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

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
    int inicio = i * (i + 1) / 2; // formula triangular
    int fin = inicio + i;//limite exclusivo
    double valor_sum = 0;

    for (int j = inicio; j < fin; j++) {
        valor_sum += sin(j);
    }

    return valor_sum;
}

int main(int argc, char *argv[]) {
    double resSumatoria = 0;

    if (argc < 3) {
        printf("Error:\n\t./ejecutable numHilos numerIteraciones\n");
        exit(0);
    }

    int numHilos = (int) atoi(argv[1]);//Se convierte el parametro a entero para los hilos solicitados
    int maxCores = omp_get_max_threads();//Numero maximpo de hilos por drfrvto
    int rep = (int) atoi(argv[2]);//Se convierte el parametro a entero para el numero de iteciones del FOR
/*
Bloque de informacion sobre los hilos
*/
    printf("Número máximo de hilos: %d\n", maxCores);
    printf("Se fija el número de hilos deseado: %d\n", numHilos);

    omp_set_num_threads(numHilos);

    printf("Número de hilos fijados: %d\n", numHilos);
//Inicio de la muestra de los hilos
        InicioMuestra();
    // Región paralela por OpenMP, se crea la region paralela y reparte el FOR, el  reduction(+:resSumatoria) asegura la suma sin carreras.
    #pragma omp parallel
    {
        #pragma omp parallel for reduction(+:resSumatoria)
        for (int i = 0; i < rep; i++) {
            resSumatoria += fsum(i);
        }
    }
        printf("Microsegunsos: ");
        FinMuestra();
        printf("\nResultado final de la sumatoria: %0.2f\n", resSumatoria);

    return 0;
}
/*
Nota:
   La reducción (+) es correcta en la región 'parallel for', pero al estar anidada dentro
   de una 'parallel' externa y con anidamiento deshabilitado,
   cada hilo externo ejecuta el for completo y su parcial se suma sobre 'resSumatoria',
   inflando el total. Si se busca una única pasada con reducción global, bastaría un solo
   'parallel for reduction(+:resSumatoria)'. Además, omp_get_max_threads() reporta el máximo
   del runtime, y en punto flotante el último decimal puede variar por
   el orden de acumulación.
*/