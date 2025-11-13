README – Sistemas de Ficheros

Este proyecto contiene tres programas en C que trabajan con el sistema de ficheros en Linux.
Cada uno realiza una tarea distinta y todos se compilan mediante un Makefile.

ARCHIVOS

lab01_Santamaria.c -> Lee y muestra el contenido del archivo readme.txt.

lab02_Santamaria.c -> Lista los ficheros regulares en un directorio y muestra su tamaño.

lab03_Santamaria.c ->Lista los archivos de un directorio mostrando permisos, tipo y si fueron modificados en los últimos 10 días.

Makefile -> Compila automáticamente los tres programas y permite limpiar los ejecutables.

COMO COMPILAR

Compilar todo:
make

Compilar uno solo:
make lab02_Santamaria

Limpiar ejecutables:
make clean

COMO EJECUTAR

./lab01_Santamaria
./lab02_Santamaria
./lab03_Santamaria

Cada programa pedirá el directorio o archivo según corresponda.
