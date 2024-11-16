#include "../include/labyrinth.h"

int init_labyrinth(Labyrinth *labyrinth, int width, int height, int id, const char *name) {
    // Initialiser les attributs de base du labyrinthe
    labyrinth->id = id;
    labyrinth->width = width;
    labyrinth->height = height;
    strncpy(labyrinth->name, name, sizeof(labyrinth->name) - 1);
    labyrinth->name[sizeof(labyrinth->name) - 1] = '\0';

    // Allouer de la mémoire pour les cellules du labyrinthe
    labyrinth->cells = (cellType **)malloc(labyrinth->height * sizeof(cellType *));
    if (labyrinth->cells == NULL) {
        return 1;
    }

    // Allouer de la mémoire pour chaque ligne de cellules
    for (int i = 0; i < labyrinth->height; i++) {
        labyrinth->cells[i] = (cellType *)malloc(labyrinth->width * sizeof(cellType));
        if (labyrinth->cells[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(labyrinth->cells[j]);
            }
            free(labyrinth->cells);
            return 1;
        }
    }

    // Initialiser les cellules du labyrinthe
    int room_number = 1;
    for (int y = 0; y < labyrinth->height; y++) {
        for (int x = 0; x < labyrinth->width; x++) {
            if (x == 0 || y == 0 || x == labyrinth->width - 1 || y == labyrinth->height - 1) {
                // Bordures du labyrinthe
                labyrinth->cells[y][x].room = WALL;
                labyrinth->cells[y][x].value = 0;
            } else if (x % 2 != 0 && y % 2 != 0) {
                // Pièces du labyrinthe
                labyrinth->cells[y][x].room = ROOM;
                labyrinth->cells[y][x].value = room_number++;
            } else {
                // Murs internes du labyrinthe
                labyrinth->cells[y][x].room = WALL;
                labyrinth->cells[y][x].value = 0;
            }
        }
    }

    // Définir l'entrée et la sortie du labyrinthe
    labyrinth->cells[0][1].room = ENTRY;
    labyrinth->cells[0][1].value = ENTRY; 
    labyrinth->cells[labyrinth->height - 1][labyrinth->width - 2].room = EXIT;
    labyrinth->cells[labyrinth->height - 1][labyrinth->width - 2].value = EXIT;  // Sortie

    return 0;
}

void create_labyrinth(Labyrinth *labyrinth) {
    int total_rooms = (labyrinth->width / 2) * (labyrinth->height / 2); // Calculer le nombre total de pièces
    int connected_rooms = 1; // Initialiser le nombre de pièces connectées à 1

    // Boucle jusqu'à ce que toutes les pièces soient connectées
    while (connected_rooms < total_rooms) {
        int x = rand() % (labyrinth->width - 2) + 1; 
        int y = rand() % (labyrinth->height - 2) + 1; 

        if (labyrinth->cells[y][x].room == WALL) { 
            int dx = 0, dy = 0;
            if (x % 2 == 0) {
                dx = 1; // Si x est pair, on se déplace horizontalement
            } else {
                dy = 1; // Si x est impair, on se déplace verticalement
            }

            int nx = x + dx; 
            int ny = y + dy; 
            int px = x - dx;
            int py = y - dy;

            // Vérifier si les cellules voisines sont des pièces et ont des valeurs différentes
            if (labyrinth->cells[ny][nx].room == ROOM && labyrinth->cells[py][px].room == ROOM &&
                labyrinth->cells[ny][nx].value != labyrinth->cells[py][px].value) {
                // Casser le mur pour connecter les pièces
                labyrinth->cells[y][x].room = ROOM;
                labyrinth->cells[y][x].value = labyrinth->cells[py][px].value;

                int old_value = labyrinth->cells[ny][nx].value; // Sauvegarder l'ancienne valeur de la pièce
                int new_value = labyrinth->cells[py][px].value; // Sauvegarder la nouvelle valeur de la pièce

                // Mettre à jour toutes les cellules avec l'ancienne valeur pour qu'elles aient la nouvelle valeur
                for (int i = 0; i < labyrinth->height; i++) {
                    for (int j = 0; j < labyrinth->width; j++) {
                        if (labyrinth->cells[i][j].value == old_value) {
                            labyrinth->cells[i][j].value = new_value;
                        }
                    }
                }

                connected_rooms++; // Incrémenter le nombre de pièces connectées
            }
        }
    }
}

int save_labyrinth(Labyrinth labyrinth, const char *filename) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        return 1;
    }

    fprintf(file, "ID: %d\n", labyrinth.id);
    fprintf(file, "Name: %s\n", labyrinth.name);
    fprintf(file, "Width: %d\n", labyrinth.width);
    fprintf(file, "Height: %d\n", labyrinth.height);

    for (int i = 0; i < labyrinth.height; i++) {
        for (int j = 0; j < labyrinth.width; j++) {
            if (labyrinth.cells[i][j].value == ENTRY) {
                fprintf(file, "2");
            } else if (labyrinth.cells[i][j].value == EXIT) {
                fprintf(file, "3");
            } else {
                fprintf(file, "%d", labyrinth.cells[i][j].room);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);

    return 0;
}

int load_labyrinth(Labyrinth *labyrinth, const char *filename) {
    FILE *file = fopen(filename, "r");  // Ouvrir le fichier en mode lecture
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");  // Afficher une erreur si le fichier ne peut pas être ouvert
        return 1;
    }

    // Lire les informations de base du labyrinthe
    fscanf(file, "ID: %d\n", &labyrinth->id);
    fscanf(file, "Name: %s\n", labyrinth->name);
    fscanf(file, "Width: %d\n", &labyrinth->width);
    fscanf(file, "Height: %d\n", &labyrinth->height);

    // Allouer de la mémoire pour les cellules du labyrinthe
    labyrinth->cells = (cellType **)malloc(labyrinth->height * sizeof(cellType *));
    if (labyrinth->cells == NULL) {
        fclose(file);  // Fermer le fichier en cas d'erreur
        return 1;
    }
    
    // Allouer de la mémoire pour chaque ligne de cellules
    for (int i = 0; i < labyrinth->height; i++) {
        labyrinth->cells[i] = (cellType *)malloc(labyrinth->width * sizeof(cellType));
        if (labyrinth->cells[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(labyrinth->cells[j]);  // Libérer la mémoire allouée en cas d'erreur
            }
            free(labyrinth->cells);
            fclose(file);  // Fermer le fichier
            return 1;
        }
    }

    // Lire les cellules du labyrinthe à partir du fichier
    for (int i = 0; i < labyrinth->height; i++) {
        for (int j = 0; j < labyrinth->width; j++) {
            int room;
            fscanf(file, "%1d", &room);  // Lire la valeur de la cellule
            labyrinth->cells[i][j].room = room;  // Définir le type de cellule
            if (room == ENTRY) {
                labyrinth->cells[i][j].value = ENTRY;  // Définir la valeur de l'entrée
            } else if (room == EXIT) {
                labyrinth->cells[i][j].value = EXIT;  // Définir la valeur de la sortie
            } else {
                labyrinth->cells[i][j].value = (room == WALL) ? 0 : 1;  // Définir la valeur des autres cellules
            }
        }
        fscanf(file, "\n");  // Lire le caractère de nouvelle ligne
    }

    fclose(file);  // Fermer le fichier
    return 0;  // Retourner 0 pour indiquer le succès
}


void display_labyrinth_with_player(Labyrinth *labyrinth, Position player, Position key, Position bonus, Position malus, Monster *monsters, int num_monsters) {
    // Vérifiez que les coordonnées du joueur sont valides
    if (player.x < 0 || player.x >= labyrinth->width || player.y < 0 || player.y >= labyrinth->height) {
        printf("Erreur: Coordonnées du joueur invalides.\n");
        return;
    }

    // Afficher le labyrinthe avec le joueur
    for (int y = 0; y < labyrinth->height; y++) {
        for (int x = 0; x < labyrinth->width; x++) {

            // Vérifier si un monstre est présent à cette position
            int is_monster = 0;
            for (int i = 0; i < num_monsters; i++) {
                if (monsters[i].x == x && monsters[i].y == y) {
                    printf("👻");  // Afficher un monstre
                    is_monster = 1;
                    break;
                }
            }
            if (is_monster) {
                continue;
            }

            // Afficher les différents éléments du labyrinthe
            if (player.x == x && player.y == y) {
                printf("🐵");  // Afficher le joueur
            } else if (key.x == x && key.y == y) {
                printf("🔑");  // Afficher la clé
            } else if (bonus.x == x && bonus.y == y) {
                printf("🍌");  // Afficher le bonus
            } else if (malus.x == x && malus.y == y) {
                printf("💣");  // Afficher le malus
            } else if (labyrinth->cells[y][x].room == WALL) {
                printf("🌴");  // Afficher un mur
            } else if (labyrinth->cells[y][x].room == ENTRY) {
                printf("  ");  // Afficher l'entrée
            } else if (labyrinth->cells[y][x].room == EXIT) {
                printf("  ");  // Afficher la sortie
            } else {
                printf("  ");  // Afficher une case vide
            }
        }
        printf("\n");
    }
    // Afficher les positions du joueur et de la clé pour le débogage
/*     printf("Positions : Joueur (%d, %d), Clé (%d, %d)\n",
    player.x, player.y, key.x, key.y); */
}


void find_entry(Labyrinth *labyrinth, Position *player) {
    for (int y = 0; y < labyrinth->height; y++) {
        for (int x = 0; x < labyrinth->width; x++) {
            if (labyrinth->cells[y][x].value == 2) {  // Si c'est l'entrée
                // Placer le joueur une case en dessous de l'entrée
                if (y + 1 < labyrinth->height) { // Assurez-vous que la case en dessous existe
                    player->x = x;
                    player->y = y + 1;  // Placer le joueur sous l'entrée
                }
                return;
            }
        }
    }
}

void place_key(Labyrinth *labyrinth, Position *key) {
    int x, y;
    do {
        x = rand() % labyrinth->width;
        y = rand() % labyrinth->height;
    } while (labyrinth->cells[y][x].room != ROOM);

    key->x = x;
    key->y = y;
}

void place_bonus(Labyrinth *labyrinth, Position *bonus) {
    int x, y;
    do {
        x = rand() % labyrinth->width;
        y = rand() % labyrinth->height;
    } while (labyrinth->cells[y][x].room != ROOM);

    bonus->x = x;
    bonus->y = y;
}

void place_malus(Labyrinth *labyrinth, Position *malus) {
    int x, y;
    do {
        x = rand() % labyrinth->width;
        y = rand() % labyrinth->height;
    } while (labyrinth->cells[y][x].room != ROOM);

    malus->x = x;
    malus->y = y;
}

int verify_odd(const char *prompt) {
    int value;
    do {
        printf("%s (valeur impaire): ", prompt);
        scanf("%d", &value);
        if (value % 2 == 0) {
            printf("Erreur: veuillez entrer une valeur impaire.\n");
        }
    } while (value % 2 == 0);
    return value;
}

char* select_labyrinth() {
    DIR *d;
    struct dirent *dir;
    d = opendir("./lab_lib");
    if (!d) {
        perror("Erreur lors de l'ouverture du répertoire");
        return NULL;
    }

    char *labyrinths[100];
    int count = 0;
    while ((dir = readdir(d)) != NULL) {
        if (strstr(dir->d_name, ".cfg")) {
            labyrinths[count] = malloc(100 * sizeof(char));
            strncpy(labyrinths[count], dir->d_name, strlen(dir->d_name) - 4);
            labyrinths[count][strlen(dir->d_name) - 4] = '\0';  // Retirer ".cfg"
            count++;
        }
    }
    closedir(d);

    if (count == 0) {
        printf("Aucun labyrinthe disponible.\n");
        return NULL;
    }

    struct termios orig_termios;
    enable_raw_mode(&orig_termios);

    int highlight = 0;
    int choice = -1;
    while (choice == -1) {
        printf("\033[H\033[J"); // Effacer l'écran
        printf("Liste des labyrinthes\n\n");
        for (int i = 0; i < count; i++) {
            if (i == highlight) {
                printf("> %s\n", labyrinths[i]);  // Afficher le labyrinthe sélectionné
            } else {
                printf("  %s\n", labyrinths[i]);  // Afficher les autres labyrinthes
            }
        }

        char ch;
        if (read(STDIN_FILENO, &ch, 1) > 0) {
            if (ch == 'z' || ch == 'Z') {
                highlight = (highlight > 0) ? highlight - 1 : count - 1;
            } else if (ch == 's' || ch == 'S') {
                highlight = (highlight < count - 1) ? highlight + 1 : 0;
            } else if (ch == '\n') {
                choice = highlight;
            }
        }
    }

    printf("\033[H\033[J"); // Effacer l'écran

    disable_raw_mode(&orig_termios);
    return labyrinths[choice];  // Retourner le nom du labyrinthe choisi
}

void enable_raw_mode(struct termios *orig_termios) {
    tcgetattr(STDIN_FILENO, orig_termios);
    struct termios raw = *orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN );
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(struct termios *orig_termios) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}
