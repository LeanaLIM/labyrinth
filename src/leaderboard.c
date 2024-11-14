#include "labyrinth.h"

// Ajoute un score au leaderboard
void add_score(Leaderboard *leaderboard, const char *name, int score) {
    // Si le leaderboard n'est pas plein, ajouter le score à la fin
    if (leaderboard->count < MAX_SCORES) {
        strcpy(leaderboard->entries[leaderboard->count].name, name);
        leaderboard->entries[leaderboard->count].score = score;
        leaderboard->count++;
    } else {
        // Si le leaderboard est plein, remplacer le plus petit score si le nouveau score est plus petit
        if (score < leaderboard->entries[MAX_SCORES - 1].score) {
            strcpy(leaderboard->entries[MAX_SCORES - 1].name, name);
            leaderboard->entries[MAX_SCORES - 1].score = score;
        }
    }
    // Trier les scores par ordre croissant
    for (int i = 0; i < leaderboard->count - 1; i++) {
        for (int j = i + 1; j < leaderboard->count; j++) {
            if (leaderboard->entries[i].score > leaderboard->entries[j].score) {
                // Échanger les entrées si elles ne sont pas dans le bon ordre
                ScoreEntry temp = leaderboard->entries[i];
                leaderboard->entries[i] = leaderboard->entries[j];
                leaderboard->entries[j] = temp;
            }
        }
    }
}

void save_leaderboard(const Leaderboard *leaderboard, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier pour sauvegarder le leaderboard");
        return;
    }
    fprintf(file, "%d\n", leaderboard->count);
    for (int i = 0; i < leaderboard->count; i++) {
        fprintf(file, "%s %d\n", leaderboard->entries[i].name, leaderboard->entries[i].score);
    }
    fclose(file);
}

void load_leaderboard(Leaderboard *leaderboard, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier pour charger le leaderboard");
        return;
    }
    fscanf(file, "%d\n", &leaderboard->count);
    for (int i = 0; i < leaderboard->count; i++) {
        fscanf(file, "%s %d\n", leaderboard->entries[i].name, &leaderboard->entries[i].score);
    }
    fclose(file);
}