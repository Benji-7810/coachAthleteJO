#ifndef INTERFACE_H  // FILENAME
#define INTERFACE_H

#include "interface.h"

#include"structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int demande_a_l_utilisateur_un_entier(char* question, int min, int max) {
    int nombre;
    do{
        printf("%s\n", question);
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

    //printf("print displayMenuGeneric %d\n", nb_option);  
    for(int i = 1 ; i<=nb_option ; i++){

        printf("%d : %s\n", i, tab_option[i-1]);  
      

    }
    return demande_a_l_utilisateur_un_entier("\nquelle choix veux tu choisir ?", 1, nb_option);

    
}
    



int displayMenuPrincipal(){

    int nb_option=5;

    char *tab[] = { 
        "performances athletes",
        "satistique des athletes",
        "afficher_la_liste_des_athletes",
        "ajouter_des_athletes",
        "rage_quit"
    };

    
    return displayMenuGeneric(tab, nb_option);
}


#endif