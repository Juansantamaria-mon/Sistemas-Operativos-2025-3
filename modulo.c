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

int printFuncion() {
  printf("***************************************");
  printf("\n Calculador de masa corporal \n");
  printf("*************************************** \n");
  return 0;
}

float imcFuncion(float masa, float altura) {
//Calcula el IMC
  float IMC = masa / (altura * altura);
  return IMC;
}

void impMatrix(float *mA, int N) {
// Recorre filas y columnas de la matriz para imprimir sus valores  
for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf(" %f ", mA[i * N + j]);
    }
    printf(" \n");
  }
}

float *matrixMult(int N, float *mA, float *mB) {

// Reserva memoria para la matriz resultante
  float *mC = (float *)malloc(N * N * 4);

// Multiplicación de matrices estándar
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      float suma = 0;
      for (int k = 0; k < N; k++) {
        suma += mA[i * N + k] * mB[k * N + j];
      }
      mC[i * N + j] = suma;
    }
  }
  return mC;
}

void llenarMatriz(int N, float *mA, float *mB) {
// Rellena ambas matrices con valores aleatorios
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      mA[i * N + j] = rand() % 100 * 0.121;
      mB[i * N + j] = rand() % 100 * 0.121;
    }
}
