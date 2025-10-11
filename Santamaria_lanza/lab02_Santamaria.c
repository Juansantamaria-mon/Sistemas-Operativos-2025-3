/*******************************************************
+Pontificia Univercidad Javeriana
+Autor: Juan Carlos Santamaria
+fecha: 09-10-2025
+Materia: Sistemas Operativos
+Tema:Creacion de procesos dor
        -Identificacion del proceso padre hijo
        -Procesos duplicados
**********************************************************************/
#include  <stdio.h>
#include  <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{

 printf("\n\nPrograma Principal !! \n\n");
  /* Se invoca la creacion del proceso en un INT para identificar*/

int processoID = fork();

/* Se duplica el proceso*/

 /* Si fork() devuelve 0 estamos en el HIJO. Imprimimos su PID y luego un bucle */

if(processoID ==0){
        printf("Soy Luck. ID = %d\n", getpid());

        for(int i=0 ; i<5 ;i++) /*Imprime del 0 al 4*/
        {
        printf("Valor HIJO == %d ==\n", i);
        }
}

/* Si fork() devuelve >0 estamos en el PADRE. Mostramos su PID
 y ejecutamos un bucle descendente*/
else if(processoID>0){
        printf("Luck, soy tu padre!!! ID = %d\n", getpid());

        for(int i=5 ; i>=0 ;i--)
        {
        printf("Valor PADRE == %d ==\n", i);/*Imprime del 5 al 0*/
        }

}
else{
        printf("Error del llamada FORK() \n");
}

      printf("Fin del proceso \n\n");

return 0;
}