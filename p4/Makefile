CC=gcc
CFLAGS=-Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack_fp -llist
### -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
EXE= p4_e1 p4_e2

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

p4_e2: p4_e2.o liblist.a node.o graph_list.o queue_fp.o
		@echo "#---------------------------"
		@echo "# Generando $@ "
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS) node.o graph_list.o queue_fp.o liblist.a

p4_e2.o: p4_e2.c
		@echo "#---------------------------"
		@echo "# Generando $@ "
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

extrafunctions_int.o: extrafunctions_int.c extrafunctions_int.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

queue_fp.o: queue_fp.c queue_fp.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

node.o : node.c node.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

graph_list.o : graph_list.c graph_list.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<


ej1_test:
	@echo Ejecutando p4_e1
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./p4_e1 5

ej2_test:
	@echo Ejecutando p4_e2
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p4_e2 g2_s.txt 1 4
