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
#define MAX_SCORES 10
#define NAME_LENGTH 50

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int x;
    int y;
} Monster;

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

typedef struct {
    char name[NAME_LENGTH];
    int score;
} ScoreEntry;

typedef struct {
    ScoreEntry entries[MAX_SCORES];
    int count;
} Leaderboard;

int init_labyrinth(Labyrinth *labyrinth, int width, int height, int id, const char *name);
void find_entry(Labyrinth *labyrinth, Position *player);
void display_labyrinth_with_player(Labyrinth *labyrinth, Position player, Position key, Position bonus, Position malus, Monster *monsters, int num_monsters);
void create_labyrinth(Labyrinth *labyrinth);
int verify_odd(const char *prompt);
int save_labyrinth(Labyrinth labyrinth, const char *filename);
int load_labyrinth(Labyrinth *labyrinth, const char *filename);
void load_leaderboard(Leaderboard *leaderboard, const char *filename);
char* select_labyrinth();
void play_labyrinth(Labyrinth *labyrinth, Position *player, Leaderboard *leaderboard, const char *labyrinth_name);
void enable_raw_mode(struct termios *orig_termios);
void disable_raw_mode(struct termios *orig_termios);
void place_key(Labyrinth *labyrinth, Position *key);
void place_bonus(Labyrinth *labyrinth, Position *bonus);
void place_malus(Labyrinth *labyrinth, Position *malus);
void move_monsters(Labyrinth *labyrinth, Monster *monsters, int num_monsters);
void place_monsters(Labyrinth *labyrinth, Monster *monsters, int *num_monsters);
