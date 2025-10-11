/*******************************************************
+Pontificia Univercidad Javeriana
+Autor: Juan Carlos Santamaria
+fecha: 09-10-2025
+Materia: Sistemas Operativos
+Tema:Creacion de procesos dor
        -Identificacion del proceso padre hijo
**********************************************************************/
#include  <stdio.h>
#include  <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
  /* Se invoca la creacion del proceso en un INT para identificar entinces se llama a fork() y
    va a crear un proceso hijo y se guarda el valor de retorno en 'processoID' para saber en
       qué proceso estamos haciendo o si ocurrió un error.
  */

int processoID = fork();

/* Se duplica el proceso*/

if(processoID ==0){
           printf("Soy Luck. ID = %d\n", getpid());/* Imprime el ID del HIJO:*/
}
else if(processoID>0){
        printf("Luck, soy tu padre!!! ID = %d\n", getpid()); /* Imprime el ID del PADRE:*/
}
else{
        printf("Error del llamada FORK() \n");/* Imprime en el caso de que se produce un error*/
}

/*Este bloque lo ejecutan ambos procesos. Sirve para observar que, después de fork(),
     el flujo continúa en paralelo y las salidas pueden intercalarse sin orden garantizado. */
printf("\n\n Programa Principal:!! \n");
for(int i=0; i<5; i++)
{
        printf("Valor Bucle == %d ==\n", i);
}

/* Cada proceso finaliza por su cuenta, y el padre debe esperar al hijo*/
        printf("Fin del proceso \n");

return 0;
}
