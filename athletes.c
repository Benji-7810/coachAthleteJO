#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"






void check_error(FILE * file){
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
}





void addNewAthlete(athlete* tab_athletes, int* nbAthletes){

    tab_athletes = realloc(tab_athletes, ((*nbAthletes)+1) * sizeof(athlete));
    
    char nv_athlete[100];
    printf("rentre un athlete: ");
    scanf("%s", nv_athlete);
    
    strcpy(tab_athletes[(*nbAthletes)].prenom_nom, nv_athlete);
    (*nbAthletes)++ ;
}





// return an array of athletes from file
athlete* readAthletesFromFile(const char* nomFichier, int* nbAthletes) {
    
    *nbAthletes = nbLinesNonVide(nomFichier);

    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible de lire le fichier: %s", nomFichier);
        exit(1);
    }

    athlete* tableauFinal = malloc(*nbAthletes * sizeof(athlete));
    if (tableauFinal == NULL) {
        printf("Allocation memoire KO");
        exit(1);
    }

    char ligne[MAX_LINE_LENGTH];
    int i = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        // Supprimer le saut de ligne à la fin de la ligne si présent
        size_t longueur = strlen(ligne);
        if (longueur > 0 && ligne[longueur - 1] == '\n')
            ligne[longueur - 1] = '\0';

        // Ignorer les lignes vides
        if (strlen(ligne) == 0)
            continue;

        // Copier le nom de l'athlete dans le tableau final
        strcpy(tableauFinal[i].prenom_nom, ligne);

        i++;
    }

    fclose(fichier);

    return tableauFinal;
}




// print an array of Athlete
void printArrayOfAthlete(athlete* tab_athletes, int nbAthletes)
{
    printf("Nombre d'athletes : %d\n", nbAthletes);
    for (int i = 0; i < nbAthletes; i++) {
        printf("Athlete %d : %s\n", i + 1, tab_athletes[i].prenom_nom);
    }
}



// rewrite all athletes from array to file
void writeArrayOfAthleteTOfile(const char* nomFichier, athlete* tab_athletes, int  nbAthletes) {

    FILE* fichier = fopen(nomFichier, "w");  // on écrit tout le tableaux;

   
    if (!fichier) {  // Vérification si le fichier a bien été ouvert
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    for (int i = 0; i < nbAthletes; i++) {
        fprintf(fichier, "%s\n", tab_athletes[i].prenom_nom);  // Écrire le nom dans le fichier avec un saut de ligne
    }


    
    fclose(fichier);  // Fermer le fichier
}
