/**************************************************************************************
 * Fecha:21 Agosto 2025
 * Autor: Juan Carlos Santamaria
 * Materia: Sistemas Operativos
 * Tema: Retos
 * Objetivo: Reto 3
**************************************************************************************/
#include <stdio.h>    
#include <stdlib.h>   

int main() {
    int *ptr; //Se declara un puntero de tipo entero (int)

    // Reservamos memoria para 15 enteros
    ptr = malloc(15 * sizeof(*ptr)); 

    if (ptr != NULL) {
        *(ptr + 5) = 480;   /* Se assigna 480 al sexto entero */
        printf("Value of the 6th integer is %d\n", *(ptr + 5));
        free(ptr);          // liberamos la memoria reservada
    }

    return 0;
}
