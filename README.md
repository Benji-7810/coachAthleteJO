# coachAthleteJO

C’est bientôt les JO !
Ce programme permet à l’entraîneur de l’équipe d’athlétisme de France de suivre l’évolution des performances de ses sportifs.
Les différentes performances des athlètes lors des entraînements sont stockées dans des fichiers.
Fonctionnalités du programme : pouvoir les mettre à jour, consulter certains résultats, ainsi que produire quelques statistiques sur les athlètes.
------------------------

# commande pour compiler sous windows:
.\compile.bat

# commande pour lancer le programme sous window :
.\run.bat

# commande pour compiler sous linux:
./compile.sh

# commande pour lancer le programme sous linux :
./run.sh


# organisation de notre code source : 

strcutres.h              -----> toutes les structures utilisées pour le programme (athlete, date, épreuve, performance, entraînement, StatistiquesAthlete)

athletes.c               -----> toutes les fonctions pour la gestion des athlètes (ajouter un athlète, afficher les athlètes ...)

entrainement.h           -----> toutes les fonctions pour la gestion des entraînements (ajouter un entraînement saisi, afficher les entraînements ...)

interface.h              -----> toutes les fonctions pour la gestion de l'interface (affichage du menu, demande à l'utilisateur un entier ...)

Athletes_Selectione_JO.c -----> toutes les fonctions pour la gestion des athlètes sélectionnés (affichage particulier, comparaison d'entraînements ...)

read_data_file.c         -----> toutes les fonctions pour la gestion de la lecture des fichiers (supprimer les lignes vides, calculer le nombre de lignes dans le fichier ...)

trie.c                   -----> toutes les fonctions pour trier des tableaux selon les demandes (trier les tableaux par épreuve, créer un tableau avec tous les entraînements)  
