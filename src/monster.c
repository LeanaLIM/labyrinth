#include "labyrinth.h"


void place_monsters(Labyrinth *labyrinth, Monster *monsters, int *num_monsters) {
    int max_monsters = (labyrinth->width * labyrinth->height) / 40; // Ajustez ce ratio selon vos besoins
    if (max_monsters > 5) {
        max_monsters = 5; // Limite maximale de monstres
    }

    *num_monsters = max_monsters;
    srand(time(NULL));
    for (int i = 0; i < max_monsters; i++) {
        int x, y;
        do {
            x = rand() % labyrinth->width;
            y = rand() % labyrinth->height;
        } while (labyrinth->cells[y][x].room != ROOM);

        monsters[i].x = x;
        monsters[i].y = y;
    }
}

//la fonction prend une valeur aléatoire pour le déplacement des monstres
//puis il fait un déplkacement aléatoire
void move_monsters(Labyrinth *labyrinth, Monster *monsters, int num_monsters) {
    srand(time(NULL));
    for (int i = 0; i < num_monsters; i++) {
        int direction = rand() % 4; 
        int new_x = monsters[i].x;
        int new_y = monsters[i].y;

        switch (direction) {
            case 0: // haut
                new_y -= 1;
                break;
            case 1: // bas
                new_y += 1;
                break;
            case 2: // gauche
                new_x -= 1;
                break;
            case 3: // droite
                new_x += 1;
                break;
        }

        // Vérifier si le mouvement est valide (pas un mur)
        if (new_x >= 0 && new_x < labyrinth->width &&
            new_y >= 0 && new_y < labyrinth->height &&
            labyrinth->cells[new_y][new_x].room != WALL) {
            monsters[i].x = new_x;
            monsters[i].y = new_y;
        }
    }
}