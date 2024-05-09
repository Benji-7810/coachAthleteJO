#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"


#include "read_data_file.h"



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
    
    // read file => to "tab_lines"
    int nbLines = 0;
    char*** tab_lines = readDataFile(nomFichier, ";", &nbLines);

    //printDataLines(tab_lines, nbLines);

    *nbAthletes = nbLines;

    // create TAB_DATA of athlete
    athlete* TAB_DATA = malloc(*nbAthletes * sizeof(athlete));
    if (TAB_DATA == NULL) {
        printf("Allocation memoire KO");
        exit(1);
    }

    
    // fill TAB_DATA
    for (int i =0 ; i < nbLines ; i++) {

        // Copier le nom de l'athlete dans le tableau final
        strcpy(TAB_DATA[i].prenom_nom, tab_lines[i][0]); // first data
    }


    return TAB_DATA;
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
