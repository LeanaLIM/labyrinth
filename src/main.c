#include "../include/labyrinth.h"

int id = 0;

int main(void) {
    Labyrinth labyrinth = {0};
    Leaderboard leaderboard = {0};
    int choice;
    int width;
    int height;
    char name[100];
    char *selected_labyrinth = NULL;
    Position player = {1, 1};
    Position bonus = {-1, -1};
    Position malus = {-1, -1};

    srand(time(NULL));

    printf("\033[H\033[J");

    while (1) {

        printf("########################\n");
        printf("#        Menu          #\n");
        printf("########################\n\n");
        printf("1) ✏️ Créer un labyrinthe\n");
        printf("2) 🌴 Charger un labyrinthe\n");
        printf("3) ▶ Jouer\n");
        printf("4) 🥇 Voir le leaderboard\n");
        printf("5) 💨 Quitter\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Créer un labyrinthe
                width = verify_odd("Quelle taille fait votre labyrinthe en largeur?");
                height = verify_odd("Quelle taille fait votre labyrinthe en hauteur?");
                printf("Entrez un nom pour le labyrinthe : ");
                scanf("%s", name);

                // Initialiser le labyrinthe et créer les cellules et afficher
                init_labyrinth(&labyrinth, width, height, id, name);
                create_labyrinth(&labyrinth);
                find_entry(&labyrinth, &player);
                display_labyrinth_with_player(&labyrinth, player, (Position){-1, -1}, bonus, malus, NULL, 0); // Afficher le labyrinthe sans clé

                //enregistrement du labyrinthe
                char filename[150];
                sprintf(filename, "./lab_lib/labyrinth_%s.cfg", name);
                if (save_labyrinth(labyrinth, filename) != 0) {
                    printf("Erreur lors de la sauvegarde du labyrinthe.\n");
                } else {
                    printf("Labyrinthe sauvegardé dans le fichier %s\n", filename);
                }

                 // Libération de la mémoire
                if (labyrinth.cells != NULL) {
                    for (int i = 0; i < labyrinth.height; i++) {
                        if (labyrinth.cells[i] != NULL) {
                            free(labyrinth.cells[i]);
                            labyrinth.cells[i] = NULL;
                        }
                    }
                    free(labyrinth.cells);
                    labyrinth.cells = NULL;
                }

                id++;
                break;

            case 2:
                //menu de slection
                selected_labyrinth = select_labyrinth();
                if (selected_labyrinth == NULL) {
                    break;
                }
                char load_filename[150];
                sprintf(load_filename, "./lab_lib/%s.cfg", selected_labyrinth);

                // Chargement du labyrinthe
                if (load_labyrinth(&labyrinth, load_filename) != 0) {
                    printf("Erreur lors du chargement du labyrinthe.\n");
                } else {
                    find_entry(&labyrinth, &player);
                    char leaderboard_filename[150];
                    sprintf(leaderboard_filename, "./leaderboards/%s.leaderboard", selected_labyrinth);
                    load_leaderboard(&leaderboard, leaderboard_filename);

                    // Placer les éléments aléatoirement
                    place_bonus(&labyrinth, &bonus);
                    place_malus(&labyrinth, &malus);
                    display_labyrinth_with_player(&labyrinth, player, (Position){-1, -1}, bonus, malus, NULL, 0); 
                }

                free(selected_labyrinth); // Libérer la mémoire sinon gros problème
                selected_labyrinth = NULL;
                break;

            case 3:
                // Jouer
                if (labyrinth.cells == NULL) {
                    printf("Erreur : Aucun labyrinthe n'est chargé.\n");
                    break;
                } else {
                    find_entry(&labyrinth, &player);
                    play_labyrinth(&labyrinth, &player, &leaderboard, labyrinth.name); 
                }
                break;

            case 4:
                // Voir le leaderboard
                selected_labyrinth = select_labyrinth();
                if (selected_labyrinth == NULL) {
                    break;
                }

                char leaderboard_filename[150];
                sprintf(leaderboard_filename, "./leaderboards/%s.leaderboard", selected_labyrinth);
                load_leaderboard(&leaderboard, leaderboard_filename);

                printf("Leaderboard pour %s:\n", selected_labyrinth);
                for (int i = 0; i < leaderboard.count; i++) {
                    printf("%d. %s - %d\n", i + 1, leaderboard.entries[i].name, leaderboard.entries[i].score);
                }

                free(selected_labyrinth); 
                selected_labyrinth = NULL;
                break;
            
            case 5:
                if (labyrinth.cells != NULL) {
                    for (int i = 0; i < labyrinth.height; i++) {
                        if (labyrinth.cells[i] != NULL) {
                            free(labyrinth.cells[i]);
                            labyrinth.cells[i] = NULL;
                        }
                    }
                    free(labyrinth.cells);
                    labyrinth.cells = NULL;
                }
                printf("Quitter le programme.\n");
                exit(0);
            
            default:
                break;
        }
    }

    return 0;
}


