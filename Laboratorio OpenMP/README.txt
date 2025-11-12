============================================================
Laboratorios OpenMP — Sistemas Operativos
Autor: Juan Carlos Santamaría Orjuela
Fecha: 06/11/2025
============================================================

Descripción general
-------------------
Este conjunto de programas (Lab01–Lab06) introduce el modelo de
paralelismo de OpenMP en C: creación de regiones paralelas, fijación
de hilos, alcance de variables y
reducciones sobre sumatorias con funciones trigonométricas.

Estructura
----------
labOpenMP01.c : Región paralela simple ("Hello, World" por hilo).
labOpenMP02.c : Fija número de hilos por argumento y verifica dentro de la región.
labOpenMP03.c : parallel for con variables privadas; ‘b’ compartida (efecto no determinista).
labOpenMP04.c : Demostración de private.
labOpenMP05.c : Sumatoria de sin(j) con reducción (+). Mide tiempo en microsegundos.
labOpenMP06.c : Variante parametrizable de Lab05 (hilos y repeticiones por argumento).
