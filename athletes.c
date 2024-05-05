#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"

// return the number of lines with more than 5 characters 
// to avoid empty lines !
int nbLinesOK(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible de lire le fichier: %s", nomFichier);
        exit(1);
    }

    int nbLignesOK = 0;
    char ligne[MAX_LINE_LENGTH];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        
        // Supprimer le saut de ligne à la fin de la ligne si présent
        size_t longueur = strlen(ligne);
        if (longueur > 0 && ligne[longueur - 1] == '\n')
            ligne[longueur - 1] = '\0';

        // Ignorer les lignes vides
        if (strlen(ligne) > MIN_LINE_LENGTH) // 5
            nbLignesOK++;
    }
    return nbLignesOK;
}



// return an array of athletes from file
athlete* lireAthletesDepuisFichier(const char* nomFichier, int* nbAthletes) {
    
    *nbAthletes = nbLinesOK(nomFichier);

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
