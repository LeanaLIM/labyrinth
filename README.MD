# Projet Labyrinthe

## Arborescence des fichiers
```
.
├── include
│   └── leaderboard.h
├── src
│   ├── labyrinth.c
│   ├── leaderboard.c
│   ├── main.c
│   ├── monster.c
│   └── player.c
├── obj
│   └── main.o
├── lab_lib
│   └── labyrinth_lab1.cfg
├── leaderboards
│   └── lab1.leaderboard
├── Makefile
└── README.md
```

## fichiers
Le projet est composé de plusieurs fichiers sources :
- `labyrinth.c` : contient les fonctions pour gérer le labyrinthe dont la création, l'affichage, la sauvegarde et le chargement
- `leaderboard.c` : contient les fonctions pour gérer le classement dont le chargement, l'ajout d'un score et la sauvegarde
- `main.c` : contient la fonction principale gérant notamment le menu
- `monster.c` : contient les fonctions pour gérer les monstres dont le placement et le déplacement
- `player.c` : contient les fonctions pour gérer le joueur dont la fonction principale pour jouer (comprenant logique de déplacement, de placement des objets et de gestion des monstres et du score)

- `labyrinth.h` : contient toutes les structures, les constantes et la déclaration des fonctions
  
Le dossier `lab_lib` contient tous les labyrinthes créés.

Le dossier `leaderboards` contient les fichiers de classement. Un fichier correspond au leaderboard d'un labyrinthe.

Le dossier `obj` contient les fichiers objets générés lors de la compilation.

Le fichier `Makefile` permet de compiler le projet.

## Comment fonctionne le projet
Le projet est un jeu de labyrinthe où le joueur doit trouver la sortie en évitant les monstres. 
Le joueur peut ramasser des objets pour diminuer son score. 
Le joueur peut également ramasser une clé généré aléatoirement sur la map, pour ouvrir la porte de sortie. 
Le joueur peut se déplacer avec les touches z, q, s, d.
Rencontrer un monstre provoque un malus aléatoire et augmente le score du joueur. 
L'objectif est de sortir du labyrinthe avec le plus bas score possible.
Si le joueur fait partie des 10 meilleurs scores, il peut rentrer son nom pour être enregistré dans le classement.
Le classement de chaque labyrinth est enregistré dans un fichier différent et est consultable depuis le menu

## Comment compiler le projet
Pour compiler le projet, il suffit de lancer la commande `make` dans le répertoire du projet, puis éxecuter le projet `./labyrinth`.

## Fonctionnalité clé
1. Créer un labyrinthe
2. Sauvegarder un labyrinthe
3. Afficher un labyrinthe
4. Jouer un labyrinthe chargé 
5. Créer un classement à partir des scores
6. Sauvegarder un classement avec un score et un nom de joueur
7. Afficher un classement

## Bug connu

- Les monstres peuvent se superposer
- Les monstres peuvent se placer sur les objets et sur la sortie

- Si il y a une autre entrée que celle proposé par le menu, alors le programme plante. 
- Dans le selecteur de labyrinth et de leaderboard, on ne peut pas sortir du menu sans choisir un labyrinthe ou un leaderboard

## Améliorations possible
- Ajouter une condition pour que les monstres ne se superposent pas
- Ajouter une condition pour que les monstres ne se placent pas sur les objets et sur la sortie
- Ajoute run caractère aléatoire au nombre de monstres qui spawn sur la map
- Gérer la libération de la mémoire de façon dynamique

- Ajouter une condition pour que le programme ne plante pas si il y a une autre entrée que celle proposé par le menu ou bien obliger l'utilisateur à choisir une option grâce à un selecteur de choix

