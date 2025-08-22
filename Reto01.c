/**************************************************************************************
 * Fecha:21 Agosto 2025
 * Autor: Juan Carlos Santamaria
 * Materia: Sistemas Operativos
 * Tema: Retos
 * Objetivo: Reto 1
**************************************************************************************/

#include <stdlib.h>  
#include <stdio.h>    
#include <string.h>   

int main() {
    char *p; //Puntero inicializado                     
    char *q = NULL;    //Puntero inicializado en NULL
    
    // Se imprime p interpretado como cadena (%s).
    printf("Address of p = %s\n", p);

    // Se intenta copiar una cadena en la dirección apuntada por p.
    strcpy(p, "Hello, I'm the best in Operating Systems!!!");

     // Si strcpy hubiera funcionado, aquí se imprimiría el contenido de p.
    printf("%s\n", p);

      // Mensaje antes de copiar otra cadena en q.
    printf("About to copy \"Goodbye\" to q\n");
    
     // Se intenta copiar la cadena "Goodbye" en q.
    strcpy(q, "Goodbye");
    
      // Solo se vería si no hubiera fallado la línea anterior.
    printf("String copied\n");
    
      // Imprime la cadena supuestamente copiada en q.
    printf("%s\n", q);

free(q);
free(p);
    return 0;
}
