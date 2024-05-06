#ifndef INTERFACE_H  // FILENAME
#define INTERFACE_H

#include "interface.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// return the number of lines with more than 1 characters 
// to avoid empty lines !
int nbLinesNonVide(const char* nomFichier) {
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
        if (strlen(ligne) >= MIN_LINE_LENGTH) // 1
            nbLignesOK++;
    }
    return nbLignesOK;
}

int demande_a_l_utilisateur_un_entier(char* question, int min, int max) {
    int nombre;
    do{
        printf("%s entre %d et %d\n", question, min, max);
        scanf("%d", &nombre);
    }while(nombre<min || max<nombre);


    return nombre;
}

void demande_a_l_utilisateur_une_chaine_de_caractere(char* question, char* p_txt, int longueur_min, int longueur_max) {
    do{
         printf("%s (taille min %d, taille max %d)", question, longueur_min, longueur_max);
        scanf("%s", p_txt);
    } while( strlen(p_txt)<longueur_min || longueur_max<strlen(p_txt));}





int displayMenuGeneric(char* tab_option[], int nb_option){

    printf("print displayMenuGeneric %d\n", nb_option);  
    for(int i = 1 ; i<=nb_option ; i++){

        printf("%d : %s\n", i, tab_option[i-1]);  
      

    }
    return demande_a_l_utilisateur_un_entier("quelle choix veux tu choisir ?", 1, nb_option);

    
}
    



int displayMenuPrincipal(){

    int nb_option=6;

    char *tab[] = { 
        "nouvel entrainement",
        "consulter l'historique des entrainements",
        "satistique des athletes",
        "afficher_la_liste_des_athletes",
        "ajouter_des_athletes",
        "rage_quit"
    };


    return displayMenuGeneric(tab, nb_option);
}



#endif