#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <termios.h>
#include <unistd.h>

#define WALL 1
#define ROOM 0
#define ENTRY 2
#define EXIT 3

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int value;
    int room;
} cellType;

typedef struct {
    int id;
    int width;
    int height;
    char name[50];
    cellType **cells;
} Labyrinth;

int init_labyrinth(Labyrinth *labyrinth, int width, int height, int id, const char *name);
void find_entry(Labyrinth *labyrinth, Position *player);
void display_labyrinth_with_player(Labyrinth *labyrinth, Position player, Position key, Position bonus, Position malus);
void create_labyrinth(Labyrinth *labyrinth);
int verify_odd(const char *prompt);
int save_labyrinth(Labyrinth labyrinth, const char *filename);
int load_labyrinth(Labyrinth *labyrinth, const char *filename);
char* select_labyrinth();
void play_labyrinth(Labyrinth *labyrinth, Position *player);
void enable_raw_mode(struct termios *orig_termios);
void disable_raw_mode(struct termios *orig_termios);
void place_key(Labyrinth *labyrinth, Position *key);
void place_bonus(Labyrinth *labyrinth, Position *bonus);
void place_malus(Labyrinth *labyrinth, Position *malus);
