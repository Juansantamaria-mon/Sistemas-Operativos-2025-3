/******************************************************************
 * Autor: Juan Carlos Santamaria
 * Materia: Sistemas Operativos
 * Fecha: 06 noviembre 2025
 * Tema:Introducción a OpenMP
 * ---------------------------------------------------------------
 * ===============================================================
 * Resumen
 *   Demostración de 'parallel for' con variables privadas. Cada hilo
 *   trabaja con copias privadas de 'i' y 'a', y calcula b = a + i para
 *    su iteración. La variable 'b' es compartida, por lo que su valor final
 *    no está definido (última. Sirve para ilustrar 'private' en un 'for'
 *    paralelo y el efecto de variables compartidas en la salida.
 *
 ******************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int i; //Variable que se indica en el for, esta variable es privada
    const int N = 1000; //limite del bucle
    int a = 50; //Valor base
    int b = 0; //Esta variable sera el resultado, tomara el valor de la ultima iteracion
/*
Cada hilo tendra un indice propio que sera i en cada una de sus posiciones, en firstprivate(a)
cada hilo tendra una 'a' que etara inicializado a 50 y al finalizar en la salida 'b' quedara con
el valor de la ultima iteracion en orden de iteracion
*/
     #pragma omp parallel for private(i) private(a)
    for (i = 0; i < N; i++){
         a = 50;
        b = a + i;
    }
//Al finalizar la iteracion estar (i = N - 1), b=50+999 = 1049
    printf("a = %d b = %d (Se espera a=50 b = 1049)\n", a, b);
    return 0;
}
/* Nota:
   En 'parallel for', la variable de control 'i' es privada por defecto, declararla private(i)
   es redundante, aunque válido. Con private(a) cada hilo recibe su propia 'a' no inicializada,
   por eso se asigna 'a = 50' dentro del bucle. Dado que 'b' es compartida, su valor final es
   no determinista, si se quisiera capturar el valor de la iteración
   léxicamente última, usar 'lastprivate(b)'. Si se quisiera que 'a' empiece en 50 sin reasignarla
   dentro, usar 'firstprivate(a)'.
*/