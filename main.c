/*****************************************************************************
*                     Pontificia Universidad Javeriana
* ================================*=========================================
*
* Autor: Juan Carlos Santamaria
* Materia: Sistemas Operativos
* Docente: J. Correrdor. PhD
* Objetivo: Puntero en c
* fecha: 31 de julio

******************************************************************************/

#include "modulo.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int main(int argc, char *argv[]) {
 // Validación de argumentos
 
 if (argc < 4) {
    printf("$./ejecutable valor1 valor2 valor3\n");
    exit(0);
  }

// Conversión de argumentos
  float altura = (float)atof(argv[1]);
  float masacorporal = (float)atof(argv[2]);
  int N = (int)atof(argv[3]);

// Muestra título del programa
  printFuncion();

// Calcula el IMC e imprime el resultado
  float valorIMC = imcFuncion(masacorporal, altura);

  printf("El indice de masa corporal es %f\n", valorIMC);
  printf("*********************************************\n\n\n");
  printf("*********************************************\n");
  printf("                    Matriz                  *\n");
  printf("*********************************************\n");

// Reserva memoria para matrices
  float *m1 = (float *)malloc(N * N * 4);
  float *m2 = (float *)malloc(N * N * 4);
  
// Llena matrices con datos aleatorios
llenarMatriz(N, m1, m2);

// Imprime matrices A y B
  impMatrix(m1, N);
  impMatrix(m2, N);

// Multiplica matrices y muestra el resultado
  float *mC = matrixMult(N, m1, m2);
  impMatrix(mC, N);

// Libera el espacio de memoria utilizado
  free(m1);
  free(m2);
  free(mC);
  return 0;
}
