CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
LDFLAGS=-L./
LDLIBS=-lstack_fp
LIBS = -lm -pthread
EJ12 = p3_e1 p3_e2
EJ3 = p3_e3
all : $(EJ12) $(EJ3)

.PHONY : clean
clean :
	rm -f *.o core $(EJ12) $(EJ3)

$(EJ12) : % : %.o node.o graph.o queue_fp.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o node.o graph.o queue_fp.o

$(EJ3) : % : %.o node.o libstack_fp.a graph.o queue_fp.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o $(LDFLAGS) $(LDLIBS) $(LIBS) node.o graph.o queue_fp.o

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
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p3_e2 g2_s.txt 1 4

p3_e3_test:
	@echo Ejecutando p3_e3
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./p3_e3 g2_s.txt 1 10
