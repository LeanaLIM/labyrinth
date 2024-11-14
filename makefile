CC=gcc
CCFLAGS= -Wall -Wextra
CPPFLAGS= -I ./include
LDFLAGS= -lncurses
OBJS= main.o labyrinth.o monster.o player.o leaderboard.o

all: labyrinth

labyrinth: $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

main.o: src/main.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

labyrinth.o: src/labyrinth.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

monster.o: src/monster.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

player.o: src/player.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

leaderboard.o: src/leaderboard.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

clean:
	rm *.o
	