/**************************************************************************************
 * Fecha:21 Agosto 2025
 * Autor: Juan Carlos Santamaria
 * Materia: Sistemas Operativos
 * Tema: Retos
 * Objetivo: Reto 4
**************************************************************************************/

#include <stdio.h>    
#include <stdlib.h>   

int main() {
    int n, i, *ptr, sum = 0;//Se declara un apuntador y tres variables de tipo entero

    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Reserva dinámica de memoria con calloc (inicializa en 0)
    ptr = (int*) calloc(n, sizeof(int));

    if (ptr == NULL) {
        printf("Error! memory not allocated.\n");
        exit(0);
    }

   //Almacenaremos cada dato  para hacer ir sumando

    for (i = 0; i < n; ++i) {
    printf("Enter elements: ");
        scanf("%d", ptr + i);   // Guardamos cada número en la posición correspondiente
        sum += *(ptr + i);      // Acumulamos la suma

    }

    printf("Sum = %d\n", sum);

    free(ptr);  // Liberamos la memoria reservada dinámicamente

    return 0;
}
