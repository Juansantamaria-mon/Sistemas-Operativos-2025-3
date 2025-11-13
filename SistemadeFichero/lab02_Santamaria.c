/************************************************
*
*	-Pontificia Univercidad Javeriana-
*
* Autor: Juan Carlos Santamaria
* Mateia: Sistemas Operativos
* Tema: Sistemas de Ficheros
* Descrpcion: Este codigo atraves del nombre de un
* directorio mostrar el nombre de los ficheros y su tamaño
*
************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
//Variables y estructuras 
   DIR *d;
    struct dirent *direc;
    struct stat datos;
    char nomdir[90], nomfich[90];
//Recoleccion del nombre del directorio
    printf("Introduzca el Nombre de un Directorio: ");
    fgets (nomdir, sizeof(nomdir), stdin);
    nomdir[strlen(nomdir)-1] = '\0'; /*Eliminamos el caracter del Nombre del Fichero*/
//Mensaje de error
    if ((d = opendir(nomdir)) == NULL){
        printf ("El directorio no existe\n");
        return -1;
    }
	printf ("\n");
//Imprecion de tpodos los datos de los ficheros (Nombre - Tamaño) en el directorio
    while ((direc = readdir(d)) != NULL) {
        strcpy (nomfich, nomdir);
        strcat (nomfich, "/");
        strcat (nomfich, direc->d_name); //Nombre del directorio
        stat (nomfich, &datos);
        if (S_ISREG(datos.st_mode))
//Imprecion de la informacion de cada fichero
            printf ("Nombre: %s\t \nTamaño: %ld\n", direc->d_name, datos.st_size);
    } /*Fin del ciclo while*/
	printf ("\n");
    closedir(d); //Cierre del archivo
    return 0;
}
/*
El programa facilita la comprensión del manejo de directorios a partir de las llamadas 
al sistema `opendir`, `readdir`y `stat`, y muestra cómo obtener la información relevante 
de cada archivo, como su nombre y su tamaño, mediante el filtrado de solamente los ficheros 
regulares, constituyendo una práctica básica para entender la interacción con el sistema de 
ficheros a nivel de usuario.
*/
