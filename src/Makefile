IDIR =../include

CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS = battleship.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o boardLibrary.o computerLogic.o coordinatesFunctions.o shipsFunctions.o stack.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

battleship_make: $(OBJ) | $(LDIR)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 