/************************************************
*
*       -Pontificia Univercidad Javeriana-
*
* Autor: Juan Carlos Santamaria
* Mateia: Sistemas Operativos
* Tema: Sistemas de Ficheros
* Descrpcion: Este Programa lee un directorio, 
* lista sus archivos y muestra permisos, tipo y 
* si fueron modificados en los últimos 10 días.
*
************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int er;
    char nomdir[100], nomfich[100], resp[30];
    struct stat atr;
    DIR *d;
    struct dirent *rd1;
    time_t fecha;

    printf ("Nombre directorio\n");
    fgets (nomdir, sizeof (nomdir), stdin);

    /* quitar el \n del nombre del directorio */
    nomdir[strcspn(nomdir, "\n")] = '\0';

    fecha = time(NULL);

    if ((d = opendir(nomdir)) == NULL) {
/* Si el directorio no existe o no se puede abrir */
        printf ("No existe ese directorio \n");
        return 1;
    }
    else {
        while ((rd1 = readdir(d)) != NULL) {
            if ((strcmp(rd1->d_name, ".") != 0) && (strcmp(rd1->d_name, "..") != 0)) {
		/*Construccion de la ruta completa*/
                strcpy (nomfich, nomdir);
                strcat (nomfich, "/");
                strcat (nomfich, rd1->d_name);

		/* Mostrar ruta del fichero */
                printf ("fichero :%s:", nomfich);

		/* Obtener atributos con stat() */
                er = stat (nomfich, &atr);
		/* Mostrar modo (bits de permisos/tipo) */
                printf ("modo :%#o:", atr.st_mode);

                if ((atr.st_mode & 0400) != 0)
                    printf (" permiso R para propietario\n");
                else
                    printf (" No permiso R para propietario\n");

                if (S_ISDIR(atr.st_mode))
                    printf (" Es un directorio \n");

                if (S_ISREG(atr.st_mode))
                    /* ficheros modificados en los últimos 10 dias */
                    if (atr.st_mtime >= fecha - (10 * 24 * 60 * 60)) {
                        /* Mostrar la informacion del archivo */
			printf ("FICHERO:%s: fecha acceso %s, en sgdos %ld\n",
                                rd1->d_name,
                                ctime(&atr.st_mtime),
                                atr.st_mtime);
                    }
            }
        } /* Cierre del archivo*/
        closedir (d);
    }
    return 0;
}

/*
Este programa compagina múltiples utilidades del sistema para revisar
detenidamente un directorio: verifica derechos, distingue tipos de
ficheros y localiza cambios recientes mediante utilidades especiales que
hacen uso de marcas temporales, se trata de un ejercicio
interesante como para captar cómo los metadatos de un fichero
permiten examinar el estado del mismo y refuerza el uso de `stat` y el
trato con rutas en el sistema operativo.
*/
