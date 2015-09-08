
CC = g++
LIB =
OBJ = 	main.o catalog.o item.o string.o
FLAGS = -Wall -Weffc++
EXE = run

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LIB)  -o $(EXE)

.c.cpp.o: $.h
	$(CC) $(FLAGS) $<

clean:
	 rm -rf *.o $(EXE)
