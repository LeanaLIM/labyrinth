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

/**
 * @brief Initialize the labyrinth with the given width
 * 
 * @param labyrinth Labyrinth to initialize
 * @param width Width of the labyrinth
 * @param height Height of the labyrinth
 * @param id ID of the labyrinth
 * @param name Name of the labyrinth
 * 
 * @return 0 if successful, 1 otherwise
 * 
 * @see create_labyrinth
 */
int init_labyrinth(Labyrinth *labyrinth, int width, int height, int id, const char *name);

/**
 * @brief Find the entry of the labyrinth
 * 
 * @param labyrinth Labyrinth to search
 * @param player Player position
 * 
 * @see play_labyrinth
 */
void find_entry(Labyrinth *labyrinth, Position *player);

/**
 * @brief Display the labyrinth with the player
 * 
 * @param labyrinth Labyrinth to display
 * @param player Player position
 * @param key Key position
 * @param bonus Bonus position
 * @param malus Malus position
 * @param monsters Array of monsters
 * @param num_monsters Number of monsters
 * 
 * @see play_labyrinth
 */
void display_labyrinth_with_player(Labyrinth *labyrinth, Position player, Position key, Position bonus, Position malus, Monster *monsters, int num_monsters);

/**
 * @brief Create a labyrinth
 * 
 * @param labyrinth Labyrinth to create
 * 
 * @see init_labyrinth
 */
void create_labyrinth(Labyrinth *labyrinth);

/**
 * @brief Verify if a number is odd
 * 
 * @param prompt Message to display
 * 
 * @return Odd number
 */
int verify_odd(const char *prompt);

/**
 * @brief Save the labyrinth to a file
 * 
 * @param labyrinth Labyrinth to save
 * @param filename Name of the file
 * 
 * @return 0 if successful, 1 otherwise
 */
int save_labyrinth(Labyrinth labyrinth, const char *filename);

/**
 * @brief Load a labyrinth from a file
 * 
 * @param labyrinth Labyrinth to load
 * @param filename Name of the file
 * 
 * @return 0 if successful, 1 otherwise
 */
int load_labyrinth(Labyrinth *labyrinth, const char *filename);

/**
 * @brief Load the leaderboard from a file
 * 
 * @param leaderboard Leaderboard to load
 * @param filename Name of the file
 */
void load_leaderboard(Leaderboard *leaderboard, const char *filename);

/**
 * @brief Select a labyrinth from the available labyrinths
 * 
 * @return Name of the selected labyrinth
 */
char* select_labyrinth();

/**
 * @brief Play the labyrinth
 * 
 * @param labyrinth Labyrinth to play
 * @param player Player position
 * @param leaderboard Leaderboard to update
 * @param labyrinth_name Name of the labyrinth
 */
void play_labyrinth(Labyrinth *labyrinth, Position *player, Leaderboard *leaderboard, const char *labyrinth_name);

/**
 * @brief Enable raw mode for terminal input
 * 
 * @param orig_termios Original terminal settings
 */
void enable_raw_mode(struct termios *orig_termios);

/**
 * @brief Disable raw mode for terminal input
 * 
 * @param orig_termios Original terminal settings
 */
void disable_raw_mode(struct termios *orig_termios);

/**
 * @brief Place the key in the labyrinth
 * 
 * @param labyrinth Labyrinth to place the key
 * @param key Key position
 */
void place_key(Labyrinth *labyrinth, Position *key);

/**
 * @brief Place the bonus in the labyrinth
 * 
 * @param labyrinth Labyrinth to place the bonus
 * @param bonus Bonus position
 */
void place_bonus(Labyrinth *labyrinth, Position *bonus);

/**
 * @brief Place the malus in the labyrinth
 * 
 * @param labyrinth Labyrinth to place the malus
 * @param malus Malus position
 */
void place_malus(Labyrinth *labyrinth, Position *malus);

/**
 * @brief Move the monsters in the labyrinth
 * 
 * @param labyrinth Labyrinth to move the monsters
 * @param monsters Array of monsters
 * @param num_monsters Number of monsters
 */
void move_monsters(Labyrinth *labyrinth, Monster *monsters, int num_monsters);

/**
 * @brief Place the monsters in the labyrinth
 * 
 * @param labyrinth Labyrinth to place the monsters
 * @param monsters Array of monsters
 * @param num_monsters Number of monsters
 */
void place_monsters(Labyrinth *labyrinth, Monster *monsters, int *num_monsters);

/**
 * @brief Add a score to the leaderboard
 * 
 * @param leaderboard Leaderboard to update
 * @param name Name of the player
 * @param score Score to add
 */
void add_score(Leaderboard *leaderboard, const char *name, int score);

/**
 * @brief Save the leaderboard to a file
 * 
 * @param leaderboard Leaderboard to save
 * @param filename Name of the file
 */
void save_leaderboard(const Leaderboard *leaderboard, const char *filename);
