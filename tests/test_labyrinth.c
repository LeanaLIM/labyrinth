#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "labyrinth.h"

Labyrinth labyrinth;

// Test functions pour l'initialisation du labyrinth
MU_TEST(test_init_labyrinth) {
    int result = init_labyrinth(&labyrinth, 7, 7, 1, "TestLab");
    mu_assert_int_eq(0, result);
    mu_assert_int_eq(7, labyrinth.width);
    mu_assert_int_eq(7, labyrinth.height);
    mu_assert_string_eq("TestLab", labyrinth.name);
    mu_assert_int_eq(ENTRY, labyrinth.cells[0][1].value);
    mu_assert_int_eq(EXIT, labyrinth.cells[6][5].value);
}

//test pour la sauvegarde du labyrinth en tant que fichier avec un nom donné, une largeur et une hauteur
MU_TEST(test_save_and_load_labyrinth) {
    save_labyrinth(labyrinth, "test_lab.txt");

    Labyrinth loaded_labyrinth;
    int result = load_labyrinth(&loaded_labyrinth, "test_lab.txt");
    mu_assert_int_eq(0, result);
    mu_assert_int_eq(labyrinth.width, loaded_labyrinth.width);
    mu_assert_int_eq(labyrinth.height, loaded_labyrinth.height);
    mu_assert_string_eq(labyrinth.name, loaded_labyrinth.name);

}

//test pour placer la clé dans le labyrinth
MU_TEST(test_place_key) {
    Position key;
    place_key(&labyrinth, &key);

    mu_assert_int_eq(ROOM, labyrinth.cells[key.y][key.x].room);
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_init_labyrinth);
    MU_RUN_TEST(test_save_and_load_labyrinth);
    MU_RUN_TEST(test_place_key);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}