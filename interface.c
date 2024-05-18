#ifndef INTERFACE_H  // FILENAME
#define INTERFACE_H

#include "interface.h"

#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int demande_a_l_utilisateur_un_entier(char* question, int min, int max) {
    int nombre;
    do{
        printf("%s  entre %d et %d : ", question, min ,max);
        scanf("%d", &nombre);
    }while(nombre<min || max<nombre);


    return nombre;
}

int demande_a_l_utilisateur_un_entier_sans_affichage(char* question, int min, int max) {
    int nombre;
    do{
        printf("%s\n ", question);
        scanf("%d", &nombre);
    }while(nombre<min || max<nombre);


    return nombre;
}

// ne pas utiliser : bug si un espace est saisi
void demande_a_l_utilisateur_une_chaine_de_caractere_ne_pas_utiliser(char* question, char* p_txt, int longueur_min, int longueur_max) {
    do{
         printf("%s (taille min %d, taille max %d)", question, longueur_min, longueur_max);
        scanf("%s", p_txt);
    } while( strlen(p_txt)<longueur_min || longueur_max<strlen(p_txt));
}



void demande_a_l_utilisateur_une_chaine_de_caractere_fgets(char* question, char* p_txt, int taille_max)
{
    printf("\n%s", question);
    
    // 2x pour eviter le boucle infinie...
    fgets(p_txt, taille_max-1, stdin);
    fgets(p_txt, taille_max-1, stdin);

    int length = (int)strlen(p_txt);
    p_txt[length-1] = '\0';


}


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


// format: JJ/MM/AAAA HH:MM
void print_date(date ladate)
{
    printf("%02d/%02d/%04d %02d:%02d", 
    ladate.jour, ladate.mois, ladate.annee, ladate.heure, ladate.min); 
}


// return format: JJ/MM/AAAA HH:MM
char* get_date_printable(date ladate)
{
    char* date_printable = (char*) malloc(sizeof(char) * (16+1));

    sprintf(date_printable, "%02d/%02d/%04d %02d:%02d", 
    ladate.jour, ladate.mois, ladate.annee, ladate.heure, ladate.min); 

    return date_printable;
}

int numero_jour( date d){
    int m= (d.mois+9)%12;
    int a= d.annee-(m>=10);
     return 1461*a/4-a/100+a/100+(m*306+5)/10+d.jour;
}

int nombre_jours(date d1, date d2){
    return numero_jour(d1)-numero_jour(d2);
}


#endif