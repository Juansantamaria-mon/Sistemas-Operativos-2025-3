/**************************************************************************************
 * Fecha:21 Agosto 2025
 * Autor: Juan Carlos Santamaria
 * Materia: Sistemas Operativos
 * Tema: Retos
 * Objetivo: Reto 2
**************************************************************************************/

#include <stdio.h> 
#include <stdlib.h>   
#include <string.h>
int main() {
    char *q = NULL; //Puntero inicializado en NULL
    printf("Requesting space for \"Goodbye!\" \n");

       // Reservamos memoria dinámica suficiente para "Goodbye" + '\0'
    q = (char *)malloc(strlen("Goodbye") + 1);

    // Verificamos si malloc falló
    if (!q) {
        perror("Failed to allocate space because");
        exit(1);
    }

     // Avisamos la dirección donde vamos a copiar
printf("About to copy \"Goodbye\" to q at address %p \n", (void*)q);


     // Copiamos la cadena literal en la memoria reservada
    strcpy(q, "Goodbye");
    printf("String copied\n");

      // Imprimimos el contenido de q
    printf("%s \n", q);

free(q);
    return 0;
}
