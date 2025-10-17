/*##################################################################
*Pontificia Univercidad Javeriana
*Autor: Juan Carlos Santamaria
*Materia: Sistemas Operativos
*Tema: Implementacion de Productor Consumidor a partir de PioeNames
*Descripcion:
+       -Archivo servidor:
+
+       Este programa crea al inicio si no existe y abre un FIFO en /tmp/fi>
+       se queda leyendo cadenas que envía el fichero cliente y por cada me>
+       verifica si es "end" para cerrar y terminar, y si no lo es, inviert>
+       reverse_string, esto hace que los caracteres se inviertan de extrem>
+       vuelta por el mismo FIFO. Para evitar desbordes, lee hasta sizeof(r>
+       '\0' al final, imprime mensajes de depuración y hace una pausa brev>
+       darle tiempo al otro proceso a leer la respuesta.
+
# SERVIDOR

####################################################################*/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/fifo_twoway"

void reverse_string(char *);

int main() {
   int fd;
   char readbuf[80];    /* buffer de lectura */
   char end[10];        /* cadena para terminar ("end") */
   int to_end;
   int read_bytes;

   /* Create the FIFO if it does not exist */
   mkfifo(FIFO_FILE, S_IFIFO|0640);
   strcpy(end, "end");
   fd = open(FIFO_FILE, O_RDWR);
   while(1) {
      read_bytes = (int)read(fd, readbuf, sizeof(readbuf) - 1); /* lee hasta 79 bytes */
      if (read_bytes < 0) continue; /* si falla, reintenta */
      readbuf[read_bytes] = '\0';   /* agrega terminador NUL */
      printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, read_bytes);
      to_end = strcmp(readbuf, end); /* compara con "end" */
      if (to_end == 0) {
         close(fd); /* cierra y sale */
         break;
      }
      reverse_string(readbuf); /* invierte la cadena */
      printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      write(fd, readbuf, strlen(readbuf));      /*
      sleep - This is to make sure other process reads this, otherwise this
      process would retrieve the message
      */
      sleep(2); /* espera para que otro proceso lea */
   }
   return 0;
}

void reverse_string(char *str) {
   int last, limit, first;
   char temp;
   last = strlen(str) - 1; /* índice último char */
   limit = last/2;
   first = 0;              /* índice primer char */

   while (first < last) {
      temp = str[first];
      str[first] = str[last];
      str[last] = temp;
      first++;
      last--;
   }
}
