CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = p3_e1 

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE) 

$(EXE) : % : %.o node.o graph.o Queue.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o node.o graph.o Queue.o

Queue.o: Queue.c Queue.H
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

graph.o : graph.c graph.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<



p3_e1_test:
	@echo Ejecutando p1_e1
	@valgrind --leak-check=full --show-leak-kinds=all ./p3_e1 g3.txt

