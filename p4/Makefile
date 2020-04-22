CC=gcc
CFLAGS=-Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack_fp -llist
### -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
EXE= p4_e1

all:$(EXE)

.PHONY : clean
clean :
		rm -f *.o core $(EXE)
		
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' (dependencias)
########################################################################
p4_e1: p4_e1.o libstack_fp.a liblist.a extrafunctions_int.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS) extrafunctions_int.o

p4_e1.o: p4_e1.c
		@echo "#---------------------------"
		@echo "# Generando $@ "
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

#extrafunctions_int.o: extrafunctions_int.c stack_types.h
#		@echo "#---------------------------"
#		@echo "# Generando $@"
#		@echo "# Depende de $^"
#		@echo "# Ha cambiado $<"
#		$(CC) $(CFLAGS) -c $<



ej1_test:
	@echo Ejecutando p4_e1
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./p4_e1 5
