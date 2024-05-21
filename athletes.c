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

    // for debug
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

    if (PRINT_DEBUG)
        printf("\nfin readAthletesFromFile()");

    return TAB_DATA;
}




// print an array of Athlete
void printArrayOfAthlete(athlete** tab_athletes, int nbAthletes)
{
    //printf("Nombre d'athletes : %d\n\n", nbAthletes);
    printf("\n");
    for (int i = 0; i < nbAthletes; i++) {
        printf("Athlete %2d : '%s'\n", i + 1, tab_athletes[i]->prenom_nom);
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


    
    fclose(fichier);  // Fermer le fichier
}



// add new athlete to array
// return 1 if OK else 0
int addNewAthlete(athlete** tab_athletes, int* nbAthletes){

    // alloc new athlete
    athlete* p_new_athlete = (athlete*) malloc(sizeof(athlete));
    
    char nv_athlete[100];
    demande_a_l_utilisateur_une_chaine_de_caractere_fgets("Entrez le nom de l'athlète (min 3 caractères): ", nv_athlete, 100-1);

    if (strlen(nv_athlete) < 3) {
        printf("le nom de l'athlete est trop petit !!\n");
        return 0;
    } 
    else 
    {
        strcpy(p_new_athlete->prenom_nom, nv_athlete);

        // add new athlete to tab
        tab_athletes[*nbAthletes] = p_new_athlete;

        (*nbAthletes)++;
        return 1;
    }
}



// Fonction pour tester l'existence du fichier
int fichier_existe(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier) {
        fclose(fichier);
        return 1; // Le fichier existe
    } else {
        return 0; // Le fichier n'existe pas
    }
}


// Fonction pour créer le fichier s'il n'existe pas
void creer_fichier_si_non_existant(const char *nom_fichier){
    if (!fichier_existe(nom_fichier)) {
        FILE *fichier = fopen(nom_fichier, "w");
        if (fichier) {
            //printf("Le fichier '%s' a été créé.\n", nom_fichier);
            fclose(fichier);
        } else {
            printf("Erreur lors de la création du fichier '%s'.\n", nom_fichier);
        }
    } else {
        printf("Le fichier '%s' existe déjà.\n", nom_fichier);
    }
}

