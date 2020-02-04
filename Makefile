CC = gcc -ansi -pedantic 
CFLAGS = -Wall
EXE = p1_e1 p1_e2 p1_e3

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o node.o graph.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o node.o graph.o

node.o : node.c node.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<
		
graph.o : graph.c graph.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

	
	
p1_e1_test:
	@echo Ejecutando p1_e1
	@valgrind --leak-check=full ./p1_e1

p1_e2_test:
	@echo Ejecutando p1_e2
	@valgrind --leak-check=full ./p1_e2

p1_e3_test:
	@echo Ejecutando p1_e3
	@valgrind --leak-check=full ./p1_e3 g1.txt