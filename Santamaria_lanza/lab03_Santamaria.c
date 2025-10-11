/*******************************************************
+Pontificia Univercidad Javeriana
+Autor: Juan Carlos Santamaria
+fecha: 09-10-2025
+Materia: Sistemas Operativos
+Tema:Creacion de procesos fork
        -Identificacion del proceso padre hijo
        -Procesos duplicados
        -Comunicacion entre Procesos con PIPE
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];              // Descriptores del pipe
    pid_t pHijo_PID;            // ID del proceso hijo

        /* Crear el pipe. Si falla, no hay canal de comunicación y se aborta. */
    if (pipe(pipefd) == -1) {
        perror("PIPE");
        exit(EXIT_FAILURE);
    }

        /* Crear el proceso hijo*/
    pHijo_PID = fork();
    if (pHijo_PID == -1) {
        perror("FORK");
        exit(EXIT_FAILURE);
    }

        /* Este es el proceso del hijo aca se cierra el extremo de escritura y hace la lectura */
    if (pHijo_PID == 0) {
        close(pipefd[1]);
        char mensaje[100];/* buffer de recepción*/
        int lecturaBYTES = read(pipefd[0], mensaje, sizeof(mensaje));

        /* Validar lectura, si en dada situacion la lectura falla, reporta error y termina. */
        if (lecturaBYTES == -1) {
            perror("LECTURA!!");
            exit(EXIT_FAILURE);
        }
    mensaje[lecturaBYTES] = '\0'; // Asegurar terminación nula
        printf("Proceso HIJO: Recibe mensaje: %s\n", mensaje);

        close(pipefd[0]);       // Cerrar lectura
    }
    // Proceso padre
    else {
        close(pipefd[0]);       // Cerrar lectura, solo escribe

        char mensaje[] = "Hola desde el PADRE!";
        write(pipefd[1], mensaje, strlen(mensaje));

        printf("Proceso PADRE: Mensaje enviado al hijo.\n");

        close(pipefd[1]);       // Cerrar escritura
    }

    return 0;
}