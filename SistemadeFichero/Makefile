##################################################
#
#       -Pontificia Univercidad Javeriana-
#
# Autor: Juan Carlos Santamaria
# Mateia: Sistemas Operativos
# Tema: Sistemas de Ficheros
# Descrpcion: Automatizacion de laboratorio 
#
##################################################

GCC = gcc

# Lista de ejecutables (sin .c)
PROGRAMAS = lab01_Santamaria lab02_Santamaria lab03_Santamaria

all: $(PROGRAMAS)

lab01_Santamaria: lab01_Santamaria.c
	$(GCC) $@.c -o $@

lab02_Santamaria: lab02_Santamaria.c
	$(GCC) $@.c -o $@

lab03_Santamaria: lab03_Santamaria.c
	$(GCC) $@.c -o $@
#Limpieza
clean:
	$(RM) $(PROGRAMAS)
