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
#ifndef _MODULO_H_
#define _MODULO_H_

#include <stdio.h>
#include  <stdlib.h>
#include <time.h>


/**************************************************************************
 Imprime un encabezado con el título de la aplicación.
 return 0 al finalizar la impresión.
**************************************************************************/
int printFuncion();


/**************************************************************************
 Calcula el índice de masa corporal (IMC).
 masa Masa en kilogramos.
 altura Altura en metros.
 El valor del IMC.
**************************************************************************/
float imcFuncion(float masa, float altura);


/**************************************************************************
 Imprime una matriz cuadrada en consola.
 mA Puntero a la matriz a imprimir.
 N Tamaño de la matriz (N x N).
*************************************************************************/
void impMatrix(float *mA, int N);


/**************************************************************************
 Multiplica dos matrices cuadradas.
 N Tamaño de las matrices (N x N).
 mA Puntero a la primera matriz.
 mB Puntero a la segunda matriz.
 return Puntero a la nueva matriz resultante (debe liberarse con free()).
**************************************************************************/
float *matrixMult(int N, float *mA, float *mB);


/**************************************************************************
 Llena dos matrices con valores aleatorios.
 N Tamaño de las matrices (N x N).
 mA Puntero a la primera matriz.
 mB Puntero a la segunda matriz.
**************************************************************************/
void llenarMatriz(int N, float * mA, float *mB);

#endif

