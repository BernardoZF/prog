CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = p3_e1 p3_e2

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o node.o graph.o queue_fp.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o node.o graph.o queue_fp.o

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

graph.o : graph.c graph.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<



p3_e1_test:
	@echo Ejecutando p3_e1
	@valgrind --leak-check=full --show-leak-kinds=all ./p3_e1 g3.txt

p3_e2_test:
	@echo Ejecutando p3_e2
	@valgrind --leak-check=full --show-leak-kinds=all ./p3_e2 g2_s.txt 1 4
