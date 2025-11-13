/************************************************
*
*	-Pontificia Univercidad Javeriana-
*
* Autor: Juan Carlos Santamaria
* Mateia: Sistemas Operativos
* Tema: Sistemas de Ficheros
* Descrpcion: Este codigo atraves del nombre de un 
* ficheronos mostrar el contenido del mismo
*
************************************************/
#include <stddef.h>
#include <stdio.h>

int main(int argc, char *argv[]){
//Nombre del fichero
	const char *filename = "readme.txt";
	FILE *fp = fopen(filename, "r");
//Mnesaje de error
 if (fp == NULL) {
        printf("Error: no se pudo abrir el archivo \"%s\".\n", filename);
        return 1;
    }
	printf("\n==============================\n");
	printf("\nLECTURA DE FICHERI readmi.txt\n");
	printf("\n==============================\n");
//Lectura del fichero "readme.txt", con un tamaño maximo de 256 bytes por linea
//Lectura de cada linea por linea
	const unsigned LARGO_MAX_LINEA=256;
	char buffer[LARGO_MAX_LINEA];

	while(fgets(buffer,LARGO_MAX_LINEA,fp))
	printf("%s", buffer);

/*Cierre del fichero*/
	fclose(fp);
return 0;
}
/*
El código permite realizar una pequeña demostración sobre el manejo de las funciones
básicas de acceso a ficheros en C ( apertura, lectura secuencial y cierre seguro del fichero). 
Permite también poner tras bambalinas cómo trabajar con buffers, y es una forma de validar 
errores en la gestión de recursos del sistema. En definitiva es un ejemplo claro, y que funciona, 
del acceso al fichero por su modo de lectura.
*/
