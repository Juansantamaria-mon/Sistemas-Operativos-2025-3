/******************************************************************
 * Autor: Juan Carlos Santamaria
 * Materia: Sistemas Operativos
 * Fecha: 06 noviembre 2025
 * Tema:Introducción OpenMP
 * ---------------------------------------------------------------
 * ===============================================================
 * Resumen
 *   Demostración de 'parallel for' con variables privadas. El bucle
 *   ejecuta b = a + i en paralelo declarando private(i), private(a) y
 *   private(b). Debido a 'private(a)', cada hilo tiene su propia 'a'
 *   sin valor inicial y, con 'private(b)', la 'b' escrita
 *   dentro del bucle no afecta a la 'b' externa.
 *   Sirve para evidenciar el efecto de la cláusula 'private' sobre el
 *   estado de las variables y la salida del programa.
 *
 ******************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int i;//Variable que se indica en el for, esta variable es privada
    const int N = 1000;//limite del bucle
    int a = 50;//Valor base
    int b = 0;//Esta variable sera el resultado, tomara el valor de la ultima iteracion

/* En este 'parallel for', 'i' se declara private, 'a' también es private
   por lo que cada hilo tiene su propia copia sin inicializar y 'b' es private dentro
   del bucle, de modo que sus escrituras no afectan a la 'b' externa. Al finalizar la 'b' global conserva su
   valor inicial.
*/

    #pragma omp parallel for private(i) private(a) private(b)
    for (i = 0; i < N; ++i){
        b = a + i;
    }
//Al finalizar la iteracion estar (i = N - 1), b=50+999 = 1049
    printf("a = %d b = %d (Se espera a=50 b = 1049)\n", a, b);
    return 0;
}
