



# code details

EXE_DIR = .
EXE = $(EXE_DIR)/life

SRC= main.c game.c Load_store.c operate.c utility.c

# generic build details
CC =     gcc
CFLAGS = -std=c99 -Wall -O
LIBS =   -lSDL2 -lSDL2_ttf

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS) -lmingw32 -lSDL2main -lSDL2

# clean up compilation

clean:
	rm-rd  *.o life

# dependencies



