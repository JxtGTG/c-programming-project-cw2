



# code details

EXE_DIR = .
EXE = $(EXE_DIR)/life

SRC= main.c game.c Load_store.c operate.c utility.c

# generic build details
CC =     gcc
CFLAGS = -Wall -O
LIBS =   -lSDL2 -lSDL2_image

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS) -lmingw32 -lSDL2main -lSDL2

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:  main.c game.h
game.o: game.c game.h
Load_store.o:Load_store.c Load_store.h
utility.o:utility.c utility.h
operate.o:operate.c operate.h

