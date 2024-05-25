#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"


#include "read_data_file.h"

#define NB_MAX_ATHLETES 1000




// renvoi un tableau d'athlete
athlete** readAthletesFromFile(const char* nomFichier, int* nbAthletes) {
    
    // creer TAB_DATA d'athlete
    athlete** TAB_DATA = (athlete**) malloc(NB_MAX_ATHLETES * sizeof(athlete*));

    if (TAB_DATA == NULL) {
        printf("Allocation memoire KO :  athlete** TAB_DATA[NB_MAX_ATHLETES]");
        exit(1);
    }

    // read file => to "tab_lines"
    int nbLines = 0;
    char*** tab_lines = readDataFile(nomFichier, ";", &nbLines);


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




// affiche un tableau d'athlete
void printArrayOfAthlete(athlete** tab_athletes, int nbAthletes)
{
    printf("\n  ***********************");
    printf("\n  * Liste des athlètes  *");
    printf("\n  ***********************\n");


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
        fprintf(fichier, "%s\n", tab_athletes[i]->prenom_nom);  // Écrire le nom dans le fichier avec un saut de ligne
    }

    fclose(fichier);  // Fermer le fichier
}



// ajoute nouveau athlete au tableau
// return 1 if OK else 0
int addNewAthlete(athlete** tab_athletes, int* nbAthletes) {
    
    // Alloue de la mémoire pour le nouvel athlète
    athlete* p_new_athlete = (athlete*) malloc(sizeof(athlete));
    
    // Demande à l'utilisateur le nom de l'athlète
    char nv_athlete[100];
    demande_a_l_utilisateur_une_chaine_de_caractere_fgets("Entrez le nom de l'athlète (minimum 3 caractères): ", nv_athlete, 100-1);

    // Vérifie la longueur du nom de l'athlète
    if (strlen(nv_athlete) < 3) {
        printf("Le nom de l'athlète est trop court !\n");
        return 0; // Retourne 0 pour indiquer une erreur
    } 
    
    else {
        
        // Copie le nom de l'athlète dans la structure de l'athlète nouvellement créé
        strcpy(p_new_athlete->prenom_nom, nv_athlete);

        // Ajoute le nouvel athlète au tableau
        tab_athletes[*nbAthletes] = p_new_athlete;

        (*nbAthletes)++; // Incrémente le nombre total d'athlètes
        return 1; // Retourne 1 pour indiquer le succès
    }
}



// Fonction pour tester l'existence du fichier
int fichier_existe(const char *nom_fichier) {
    
    // Tente d'ouvrir le fichier en mode lecture
    FILE *fichier = fopen(nom_fichier, "r");
    
    if (fichier) {
        fclose(fichier); // Ferme le fichier
        return 1; // Le fichier existe
    } 

    else {
        return 0; // Le fichier n'existe pas
    }
}



// Fonction pour créer le fichier s'il n'existe pas
void creer_fichier_si_non_existant(const char *nom_fichier) {
    
    // Vérifie si le fichier existe déjà
    if (!fichier_existe(nom_fichier)) {
        
        // Si le fichier n'existe pas, ouvre-le en mode écriture
        FILE *fichier = fopen(nom_fichier, "w");
        if (fichier) {
           
            // Le fichier a été ouvert avec succès, donc il est créé
            fclose(fichier); // Ferme le fichier
        } else {
            
            // Affiche un message d'erreur si le fichier n'a pas pu être créé
            printf("Erreur lors de la création du fichier '%s'.\n", nom_fichier);
        }
    } else {
        
        // Affiche un message indiquant que le fichier existe déjà
        printf("Le fichier '%s' existe déjà.\n", nom_fichier);
    }
}
