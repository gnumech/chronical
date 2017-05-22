CC=gcc
OBJ=chronical
CFLAGS=-g -lncurses -lm
SRC=src/main.c

$(OBJ) : src/
	$(CC) -o $(OBJ) $(CFLAGS) $(SRC)

clean: 
	rm -f $(OBJ)
