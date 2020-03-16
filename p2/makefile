CC=gcc
CFLAGS=-Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack_fp
### -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
EXE=p2_e0_a p2_e0_b p2_e1 p2_e2

.PHONY : clean
clean :
	rm -f *.o core $(EXE) 
	
all:$(EXE)
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' (dependencias)
########################################################################
p2_e0_a: p2_e0_a.o libstack_fp.a
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e0_a.o: p2_e0_a.c
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e0_b: p2_e0_b.o libstack_fp.a node.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS) node.o

p2_e0_b.o: p2_e0_b.c
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e1: p2_e1.o libstack_fp.a
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e1.o: p2_e1.c
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)
	

p2_e2: p2_e2.o libstack_fp.a
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e2.o: p2_e2.c
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e3: p2_e3.o element.o satck.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e3.o: p2_e3.c
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

node.o: node.c node.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<	

stack.o: stack.c stack.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<
	
element.o: element.c element.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

ej0a_test:
	@echo Ejecutando p2_e0_a
	valgrind --tool=memcheck --leak-check=yes ./p2_e0_a

ej0b_test:
	@echo Ejecutando p2_e0_b
	valgrind --tool=memcheck --leak-check=yes ./p2_e0_b

ej1_test:
	@echo Ejecutando p2_e1
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./p2_e1

ej2_test:
	@echo Ejecutando p2_e2		
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./p2_e2 "((A+B)*(C+D))%E"