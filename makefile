CC=gcc
CCFLAGS= -Wall -Wextra
CPPFLAGS= -I ./include
LDFLAGS= -lncurses
OBJDIR=./obj
OBJS= $(OBJDIR)/main.o $(OBJDIR)/labyrinth.o $(OBJDIR)/monster.o $(OBJDIR)/player.o $(OBJDIR)/leaderboard.o
TEST_OBJS= $(OBJDIR)/test_labyrinth.o $(OBJDIR)/labyrinth.o

all: labyrinth

labyrinth: $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJDIR)/main.o: src/main.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

$(OBJDIR)/labyrinth.o: src/labyrinth.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

$(OBJDIR)/monster.o: src/monster.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

$(OBJDIR)/player.o: src/player.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

$(OBJDIR)/leaderboard.o: src/leaderboard.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

$(OBJDIR)/test_labyrinth.o: tests/test_labyrinth.c
	$(CC) $(CCFLAGS) $(CPPFLAGS) $< -c -o $@

test: $(TEST_OBJS)
	$(CC) $^ $(LDFLAGS) -o tests/test_labyrinth
	./tests/test_labyrinth

clean:
	rm -f $(OBJDIR)/*.o labyrinth tests/test_labyrinth
