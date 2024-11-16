#include "labyrinth.h"

void play_labyrinth(Labyrinth *labyrinth, Position *player, Leaderboard *leaderboard, const char *labyrinth_name) {

    printf("Game Started!\n");

    // Trouver la position d'entrée
    int found_entry = 0;
    for (int y = 0; y < labyrinth->height; y++) {
        for (int x = 0; x < labyrinth->width; x++) {
            if (labyrinth->cells[y][x].room == ENTRY) {
                player->x = x;
                player->y = y;
                found_entry = 1;
                break;
            }
        }
        if (found_entry) break;
    }

    // Placer les éléments aléatoirement
    Position key;
    Position bonus;
    Position malus;

    place_key(labyrinth, &key);
    place_bonus(labyrinth, &bonus);
    place_malus(labyrinth, &malus);

    int num_monsters;
    Monster monsters[5];
    place_monsters(labyrinth, monsters, &num_monsters);

    int has_key = 0;
    int score = 0;

    // Activer le mode brut pour la lecture des entrées utilisateur
    struct termios orig_termios;
    enable_raw_mode(&orig_termios);

    int game_running = 1;

    char move;
    while (game_running) {
        printf("\033[H\033[J"); // Effacer l'écran
        display_labyrinth_with_player(labyrinth, *player, key, bonus, malus, monsters, num_monsters); // Afficher le labyrinthe

        // Afficher les commandes et le score
        printf("\033[%d;%dH", labyrinth->height + 2, 0);
        printf("Commandes :\n");
        printf("z - Haut\n");
        printf("s - Bas\n");
        printf("q - Gauche\n");
        printf("d - Droite\n");
        printf("e - Quitter\n");
        printf("Score : %d\n", score);

        move = getchar();  // Lecture du mouvement de l'utilisateur

        int new_x = player->x;
        int new_y = player->y;

        // Déterminer la nouvelle position du joueur en fonction du mouvement
        if (move == 'z' || move == 'Z') {
            new_y--;
        } else if (move == 's' || move == 'S') {
            new_y++;
        } else if (move == 'q' || move == 'Q') {
            new_x--;
        } else if (move == 'd' || move == 'D') {
            new_x++;
        } else if (move == 'e' || move == 'E') {
            game_running = 0;
            printf("Game Over\n");
            break;
        }

        
        // Vérifier si le mouvement est valide (pas un mur)
        if (new_x >= 0 && new_x < labyrinth->width &&
            new_y >= 0 && new_y < labyrinth->height &&
            labyrinth->cells[new_y][new_x].room != WALL) {
            player->x = new_x;
            player->y = new_y;
            score++;
            move_monsters(labyrinth, monsters, num_monsters);
        }

        // Vérification si le joueur a récupéré la clé
        if (player->x == key.x && player->y == key.y) {
            has_key = 1;
            key.x = -1; 
            key.y = -1;
        }

        // Vérification si le joueur a récupéré le bonus
        if (player->x == bonus.x && player->y == bonus.y) {
            score -= 10;
            bonus.x = -1; 
            bonus.y = -1;
        }

        // Vérification si le joueur est tombé sur un piège
        if (player->x == malus.x && player->y == malus.y) {
            score += 15;
            malus.x = -1; 
            malus.y = -1;
        }

        // Vérification si le joueur a rencontré un monstre
        for (int i = 0; i < num_monsters; i++) {
            if (player->x == monsters[i].x && player->y == monsters[i].y) {
                int monster_malus = (rand() % 16) + 5; // Malus aléatoire entre 5 et 20
                score += monster_malus;
                printf("Vous avez rencontré un monstre ! Malus : %d\n", monster_malus);
                usleep(1000000); 
                break;
            }
        }
        
        // Vérification de la sortie
        if (labyrinth->cells[player->y][player->x].room == EXIT) {
            if (has_key) {
                game_running = 0;
                printf("Bien joué ! Vous avez terminé le labyrinthe.\n");
                printf("Votre score est de %d\n", score);
                usleep(3000000);
                disable_raw_mode(&orig_termios);

                 // Vérifier si le score fait partie des 10 meilleurs
                if (leaderboard->count < MAX_SCORES || score < leaderboard->entries[MAX_SCORES - 1].score) {
                    char player_name[NAME_LENGTH];
                    printf("Bravo! vous avez fait un des 10 meilleurs score. Entrez votre nom : ");
                    scanf("%s", player_name);
                    add_score(leaderboard, player_name, score);
                    char leaderboard_filename[150];
                    sprintf(leaderboard_filename, "./leaderboards/%s.leaderboard", labyrinth_name);
                    save_leaderboard(leaderboard, leaderboard_filename);
                }

                return;
            } else {
                printf("Il vous faut la clé pour sortir!\n");
                usleep(1000000);
            }
        }
    }

    disable_raw_mode(&orig_termios);

}
