/**************************************************************************************
 * Fecha:21 Agosto 2025
 * Autor: Juan Carlos Santamaria
 * Materia: Sistemas Operativos
 * Tema: Retos
 * Objetivo: Reto 5
**************************************************************************************/

#include <stdio.h> 
#include <stdlib.h>   

int main() {
    int *ptr, i , n1, n2; //Se inicializan 4 punteros de tipo entero (int)
 
//Se reservara la memoria con el espacio de memoria que se le asigne
   printf("Enter size: ");
    scanf("%d", &n1);
    ptr = (int*) malloc(n1 * sizeof(int));

//Muestra la dirreccion de memoria en cada posicion
    printf("Addresses of previously allocated memory: ");
    for(i = 0; i < n1; ++i){
        printf("\n\np = %p\n", ptr+i);
}

//Nuevo tamaño del arreglo
    printf("\n Enter the new size: ");
    scanf("%d", &n2);

    ptr = realloc(ptr, n2 * sizeof(int));
    
//Muestra la dirreccion de memoria en cada posicion
    printf("Addresses of newly allocated memory: ");
    for(i = 0; i < n2; ++i){
        printf("\n\np = %p\n", ptr+i);
}
    //liberara la memoria reservada
    free(ptr);

return 0;
}

