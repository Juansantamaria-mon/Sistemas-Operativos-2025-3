/*######################################################################
*Pontificia Univercidad Javeriana
*Autor: Juan Carlos Santamaria
*Materia: Sistemas Operativos
*Tema: Implementacion de Productor Consumidor a partir de PioeNa
*Descripcion:
+       -Archivo cliente:
+
+       Este programa abre el mismo FIFO en /tmp/fifo_twoway, pide al usuario
+       atravez de consola una cadena, le quita el salto de línea y compara con
+       "end" si la entrada no es "end", la escribe en el FIFO, espera la respuesta
+       del servidor, la termina con '\0' y la muestra en pantalla, si sí es "end",
+       la envía, cierra el descriptor y finaliza. De esta forma, el cliente sirve
+       de interfaz de usuario y el servidor de procesador que transforma (invierte)
+       las cadenas.
+
# CLIENTE

#######################################################################*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/fifo_twoway"


int main() {
   int fd;
   int end_process;       // indicador si se debe terminar
   int stringlen;         // largo de la cadena leída
   int read_bytes;        // bytes leídos desde el FIFO
   char readbuf[80];      // buffer para entrada y lectura del FIFO
   char end_str[5];       // cadena que indica "end"
   printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");
   fd = open(FIFO_FILE, O_CREAT|O_RDWR, 0640); // abre/crea el FIFO
   strcpy(end_str, "end"); // inicializa la cadena de fin

   while (1) {
      printf("Enter string: ");
      fgets(readbuf, sizeof(readbuf), stdin); // lee línea desde stdin
      stringlen = strlen(readbuf);            // calcula longitud
      readbuf[stringlen - 1] = '\0';          // quita el '\n' final
      end_process = strcmp(readbuf, end_str); // compara con "end"
      //printf("end_process is %d\n", end_process);
      if (end_process != 0) {
         write(fd, readbuf, strlen(readbuf)); // envía al FIFO
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         read_bytes = (int)read(fd, readbuf, sizeof(readbuf) - 1); // espera respuesta
         if (read_bytes < 0) continue; // si error, vuelve a leer
         readbuf[read_bytes] = '\0';   // termina la cadena leída
         printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, read_bytes);
      } else  {
         write(fd, readbuf, strlen(readbuf)); // envía "end"
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         close(fd); // cierra descriptor y termina
         break;
      }
   }
  return 0;
}
