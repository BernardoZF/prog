CC=gcc
CFLAGS=-Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack_fp
### -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
EXE=p2_e0_a p2_e0_b p2_e1 p2_e2
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

p2_e1: p2_e1.o libstack_fp.a
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e1.o: p2_e1.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)
	

p2_e2: p2_e2.o libstack_fp.a
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e2.o: p2_e2.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

node.o: node.c node.h
	$(CC) $(CFLAGS) -c -o node.o node.c

clean:
	rm -f *.o core $(EXE)

ej0a_test:
	valgrind --tool=memcheck --leak-check=yes ./p2_e0_a

ej0b_test:
	valgrind --tool=memcheck --leak-check=yes ./p2_e0_b

ej1_test:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./p2_e1

ej2_test:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./p2_e2 "((A+B)*(C+D))%E"