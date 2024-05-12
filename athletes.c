#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"


#include "read_data_file.h"

#define NB_MAX_ATHLETES 1000




// return an array of athletes from file
athlete** readAthletesFromFile(const char* nomFichier, int* nbAthletes) {
    
    // create TAB_DATA of athlete
    athlete** TAB_DATA = (athlete**) malloc(NB_MAX_ATHLETES * sizeof(athlete*));

    if (TAB_DATA == NULL) {
        printf("Allocation memoire KO :  athlete** TAB_DATA[NB_MAX_ATHLETES]");
        exit(1);
    }

    // read file => to "tab_lines"
    int nbLines = 0;
    char*** tab_lines = readDataFile(nomFichier, ";", &nbLines);

    //printDataLines(tab_lines, nbLines);

    // init nbAthletes
    *nbAthletes = nbLines;

    
    // fill TAB_DATA
    for (int i =0 ; i < nbLines ; i++) {

        // malloc athlete
        TAB_DATA[i] = (athlete*) malloc(sizeof(athlete));

        // Copier le nom de l'athlete dans le tableau final
        strcpy( TAB_DATA[i]->prenom_nom, tab_lines[i][0]); // first data
    }


    return TAB_DATA;
}




// print an array of Athlete
void printArrayOfAthlete(athlete** tab_athletes, int nbAthletes)
{
    printf("Nombre d'athletes : %d\n", nbAthletes);
    for (int i = 0; i < nbAthletes; i++) {
        printf("Athlete %d : %s\n", i + 1, tab_athletes[i]->prenom_nom);
    }
}



// rewrite all athletes from array to file
void writeArrayOfAthleteTOfile(const char* nomFichier, athlete** tab_athletes, int  nbAthletes) {


    printArrayOfAthlete(tab_athletes, nbAthletes);

    
    FILE* fichier = fopen(nomFichier, "w");  // on écrit tout le tableaux;

   
    if (!fichier) {  // Vérification si le fichier a bien été ouvert
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    

    for (int i = 0; i < nbAthletes; i++) {
        //printf("%s\n", tab_athletes[i]->prenom_nom);  // Écrire le nom dans le fichier avec un saut de ligne
        fprintf(fichier, "%s\n", tab_athletes[i]->prenom_nom);  // Écrire le nom dans le fichier avec un saut de ligne
    }


    
    //fclose(fichier);  // Fermer le fichier
}




void addNewAthlete(athlete** tab_athletes, int* nbAthletes){

    // alloc new athlete
    athlete* p_new_athlete = (athlete*) malloc(sizeof(athlete));
    
    // init new athlete
    char nv_athlete[100];
    printf("rentre un athlete: ");
    scanf("%s", nv_athlete); 
    strcpy(p_new_athlete->prenom_nom, nv_athlete);

    // add new athlete to tab
    tab_athletes[*nbAthletes] = p_new_athlete;


    (*nbAthletes)++;



}
