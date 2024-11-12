#include "../include/labyrinth.h"

int main(void) {
    Labyrinth labyrinth = {0};
    int choice;
    int width;
    int height;
    char name[100];
    int id = 1;
    char *selected_labyrinth = NULL;
    Position player;
    Position bonus = {0, 0};
    Position malus = {0, 0};

    srand(time(NULL));

    while (1) {
        printf("Menu:\n");
        printf("1. Créer un labyrinthe\n");
        printf("2. Charger un labyrinthe\n");
        printf("3. Jouer\n");
        printf("4. Quitter\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                width = verify_odd("Quelle taille fait votre labyrinthe en largeur?");
                height = verify_odd("Quelle taille fait votre labyrinthe en hauteur?");
                printf("Entrez un nom pour le labyrinthe : ");
                scanf("%s", name);

                init_labyrinth(&labyrinth, width, height, id, name);
                create_labyrinth(&labyrinth);

                find_entry(&labyrinth, &player);

                display_labyrinth_with_player(&labyrinth, player, (Position){-1, -1}, bonus, malus); // Afficher le labyrinthe sans clé

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
                selected_labyrinth = select_labyrinth();
                if (selected_labyrinth == NULL) {
                    break;
                }

                char load_filename[150];
                sprintf(load_filename, "./lab_lib/%s.cfg", selected_labyrinth);

                if (load_labyrinth(&labyrinth, load_filename) != 0) {
                    printf("Erreur lors du chargement du labyrinthe.\n");
                } else {
                    find_entry(&labyrinth, &player);
                    place_bonus(&labyrinth, &bonus);
                    place_malus(&labyrinth, &malus);
                    display_labyrinth_with_player(&labyrinth, player, (Position){-1, -1}, bonus, malus); 
                }

                free(selected_labyrinth); // Libérer la mémoire ici
                selected_labyrinth = NULL;
                break;

            case 3:
                if (labyrinth.cells == NULL) {
                    printf("Erreur : Aucun labyrinthe n'est chargé.\n");
                    break;
                } else {
                    find_entry(&labyrinth, &player);
                    play_labyrinth(&labyrinth, &player); 
                }
                break;

            case 4:
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


