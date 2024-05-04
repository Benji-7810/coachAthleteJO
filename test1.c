
typedef struct{
    char nom;
}athlete;

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




void athlete(){

    int nbr = demande_a_l_utilisateur_un_entier("combien d'athletes vous voulez rentrer pour les jo",0, 100);

    char *tab = (char)malloc(sizeof(char)*nbr);

    for(int i = 0; i<nbr ;i++){
        tab[i] = demande_a_l_utilisateur_une_chaine_de_caractere("quel est ton nom de l'athele suivant",)
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(int argc, char *argv[])
{
    printf("Hello world !\n");

    return 0;
}


