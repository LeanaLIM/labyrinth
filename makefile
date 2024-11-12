CC=gcc
CCFLAGS= -Wall -Wextra
CPPFLAGS= -I ./include
LDFLAGS= -lncurses
OBJS= main.o labyrinth.o

all: labyrinth

labyrinth: $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

main.o: src/main.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

labyrinth.o: src/labyrinth.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

clean:
	rm *.o
