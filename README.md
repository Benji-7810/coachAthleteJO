# coachAthleteJO

C’est bientôt les JO !
Ce programme permet à l’entraîneur de l’équipe de France d’athlétisme de suivre l’évolution des performances de ses sportifs.
Les différentes performances des athlètes lors des entraînements sont stockées dans des fichiers.
Fonctionnalités du programme : pouvoir ajouter de nouvelles, consulter certains résultats, ainsi que produire quelques statistiques sur les athlètes.
------------------------

# globalement notre programme fonctionne de cette manière
1. chargement des fichiers en mémoire dans des tableaux de structures
2. choix des actions de l'utilisateur par menu
3. lors des ajouts d'entrainements : écriture dans les fichiers
4. affiche les tableaux


# organisation de notre code source : 
structures.h             ---> toutes les structures utilisées pour le programme (athlete, date, épreuve, performance, entraînement, StatistiquesAthlete)

athletes.c               ---> toutes les fonctions pour la gestion des athlètes (ajouter un athlète, afficher les athlètes...)

entrainement.c           ---> toutes les fonctions pour la gestion des entraînements (ajouter un entraînement, afficher les entraînements...)

interface.c              ---> toutes les fonctions pour la gestion de l'interface (affichage d'un menu, demande à l'utilisateur des valeurs...)

Athletes_Selectione_JO.c ---> toutes les fonctions pour trouver les meilleurs athlètes (affichage particulier, comparaison d'entraînements...)

read_data_file.c         ---> toutes les fonctions pour la gestion de la lecture des fichiers (lecture / écriture...)

trie.c                   ---> toutes les fonctions pour trier des tableaux selon les demandes (trier par date / épreuve / peformance...)  

/data/athletes.csv       ---> liste de tous les athlètes

/data/'nom athlete 1'.csv ---> tous les entrainements de l'athlète : 1 par ligne, données séparées par des ";"
/data/'nom athlete 2'.csv ---> tous les entrainements de l'athlète : 1 par ligne, données séparées par des ";"
/data/'nom athlete 3'.csv ---> tous les entrainements de l'athlète : 1 par ligne, données séparées par des ";"
...


# ###########################
# commandes principales
# ###########################

# compiler, générer l'exécutable et lancer le programme
make

# compiler et générer l'exécutable
make compiler_sous_linux


# historique des commits
gitlog.sh
gitlog.bat



# ##########################
# anciennes commandes 
# ###########################

# commande pour compiler sous windows:
.\compile.bat

# commande pour lancer le programme sous window :
.\run.bat

# commande pour compiler sous linux:
./compile.sh

# commande pour lancer le programme sous linux :
./run.sh

