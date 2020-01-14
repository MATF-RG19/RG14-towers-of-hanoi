PROGRAM   = towers_of_hanoi
CC        = gcc
CFLAGS    = -Wall -Wextra -std=c99
LDFLAGS   = -lGL -lGLU -lglut -lm
DEP       = main.o \
			stack.o \
			draw.o \
			move.o \
			algorithm.o \
			image.o

$(PROGRAM): $(DEP)
	$(CC) -o $(PROGRAM) $(DEP) $(LDFLAGS) $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CCFLAGS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
