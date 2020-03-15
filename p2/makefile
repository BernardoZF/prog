CC=gcc
CFLAGS=-Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack_fp
### -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
EXE=p2_e0_a p2_e0_b
all:$(EXE)
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' (dependencias)
########################################################################
p2_e0_a: p2_e0_a.o libstack_fp.a
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS)
p2_e0_a.o: p2_e0_a.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e0_b: p2_e0_b.o libstack_fp.a node.o
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS) node.o
p2_e0_b.o: p2_e0_b.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

node.o: node.c node.h
	$(CC) $(CFLAGS) -c -o node.o node.c

clean:
	rm -f *.o core $(EXE)

val:
	valgrind --tool=memcheck --leak-check=yes ./p2_e0_b
