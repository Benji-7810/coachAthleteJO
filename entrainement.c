#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrainement.h"
#include "structure.h"
#include "read_data_file.h"
#include "interface.h"
#include "athletes.h"

#define NB_MAX_ATHLETES 1000
#define NB_MAX_ENTRAINEMENT 100
#define NB_COLONNE_ENTRAINEMENT_DANS_FICHIER 9

entrainement** lis_un_fichier_d_entrainement(const char* nomFichier, int* nb_entrainement ){
    
    if (PRINT_DEBUG) {
        printf("\ndebut lis_un_fichier_d_entrainement() '%s'", nomFichier);
        printf("\n %s: %d OK", __FILE__, __LINE__);
    }

    // Création de TAB_DATA pour stocker les données d'entraînement
    entrainement** TAB_DATA = (entrainement**) malloc(NB_MAX_ENTRAINEMENT * sizeof(entrainement*));

    if (TAB_DATA == NULL) {
        printf("\nAllocation memoire KO :  entrainement** TAB_DATA[NB_MAX_ENTRAINEMENT]\n");
        exit(1);
    }

    if (PRINT_DEBUG) {
        printf("\n %s: %d OK", __FILE__, __LINE__);
    }

    // Lecture du fichier et stockage des lignes dans tab_lines
    int nbLines = 0;
    char*** tab_lines = readDataFile(nomFichier, ";", &nbLines);

    
    // Pour débogage
    if (PRINT_DEBUG) {
        printf("\n %s: %d OK", __FILE__, __LINE__);
        printDataLines(tab_lines, nbLines);
        printf("\n %s: %d OK", __FILE__, __LINE__);
    }

    (*nb_entrainement) = nbLines;


    // Remplissage de TAB_DATA
    int num_ligne_ok = 0;
    for (int i =0 ; i < nbLines ; i++) {

        if (PRINT_DEBUG)
            printf("\nlis_un_fichier_d_entrainement %d / %d", i, nbLines);

        
        // verifie le nombre de colonnes 
        int nb_colonne = 1;
        int j = 0;
        while (tab_lines[i][j] != NULL) {
            nb_colonne++; 
            j++;
        }

        //printf("\n\nLa ligne %d du fichier d'entrainement '%s' comporte %d colonnes \n", i, nomFichier, nb_colonne);

        if (nb_colonne < NB_COLONNE_ENTRAINEMENT_DANS_FICHIER)
        {
            printf("\n\n----------------------------------------------------------------------------------------------------------");
            printf("\nLa ligne %d du fichier d'entrainement '%s' ne comporte pas le bon nombre de colonnes %d < %d : ligne ignoree", i+1, nomFichier, nb_colonne, NB_COLONNE_ENTRAINEMENT_DANS_FICHIER );
            printf("\n------------------------------------------------------------------------------------------------------------\n\n");

            (*nb_entrainement) = (*nb_entrainement)-1;
        }
        else
        {
             // Allocation de mémoire pour un nouvel entraînement


            // Copie des données de tab_lines vers TAB_DATA
            TAB_DATA[num_ligne_ok] = (entrainement*) malloc(sizeof(entrainement));
            TAB_DATA[num_ligne_ok]->ladate.jour =                  atof(tab_lines[i][0]);
            TAB_DATA[num_ligne_ok]->ladate.mois =                  atof(tab_lines[i][1]);
            TAB_DATA[num_ligne_ok]->ladate.annee =                 atof(tab_lines[i][2]);
            TAB_DATA[num_ligne_ok]->ladate.heure =                 atof(tab_lines[i][3]);
            TAB_DATA[num_ligne_ok]->ladate.min =                   atof(tab_lines[i][4]);
            strcpy(TAB_DATA[num_ligne_ok]->lepreuve.nom,           tab_lines[i][5]); 
            TAB_DATA[num_ligne_ok]->laperf.perf =                  atof(tab_lines[i][6]);
            TAB_DATA[num_ligne_ok]->lepreuve.position_relais =     atof(tab_lines[i][7]);

            num_ligne_ok++;
        }

    }
    
    if (PRINT_DEBUG) {
        printf("\nfin lis_un_fichier_d_entrainement() %s: OK", nomFichier);
    }

    return TAB_DATA;
}


// Affichage du tableau d'athlete
void printArrayOfentrainement(entrainement** TAB_DATA, int nbEntrainement)
{

    for (int i = 0; i < nbEntrainement; i++) {

        print1entrainement(TAB_DATA[i], i+1);

    }
}

// Affichage du tableau d'un athlete
void print1entrainement(entrainement* p_entrainement, int i)
{
    char epreuve[20]; // Variable pour stocker le nom de l'épreuve ou la version formatée pour les relais


     // Cas spécial pour les relais
    if (strcmp(p_entrainement->lepreuve.nom, "relais") == 0) {

        // Formate le nom de l'épreuve pour inclure la position du relais
        sprintf(epreuve, "relais(%d)", p_entrainement->lepreuve.position_relais);
    } else {

        // Copie le nom de l'épreuve dans la variable epreuve
        strcpy(epreuve, p_entrainement->lepreuve.nom);
    }

    printf("entrainement %2d -> date : %s, l'epreuve : %9s,  la perf : %s \n",
        i,
        // Appelle get_date_printable pour obtenir la date formatée en chaîne de caractères
        get_date_printable(p_entrainement->ladate),
        epreuve,
        // Appelle get_perf_printable pour obtenir la performance formatée en chaîne de caractères
        get_perf_printable(p_entrainement->laperf));

}








// rewrite 
void writeArrayOftrainingTOfile(const char* nomFichier, entrainement** tab_entrainement, int  nbEntrainement) {
 
  
    FILE* fichier = fopen(nomFichier, "w");  // on écrit tout le tableaux;

   
    if (!fichier) {  // Vérification si le fichier a bien été ouvert
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Parcourt chaque entraînement dans le tableau
    for (int i = 0; i < nbEntrainement; i++) {
        // Écrit les détails de l'entraînement dans le fichier
        fprintf(fichier, "%d;%d;%d;%d;%d;%s;%.2lf;%d\n", 
        tab_entrainement[i]->ladate.jour,
        tab_entrainement[i]->ladate.mois,  
        tab_entrainement[i]->ladate.annee,  
        tab_entrainement[i]->ladate.heure,  
        tab_entrainement[i]->ladate.min,     
        tab_entrainement[i]->lepreuve.nom,
        tab_entrainement[i]->laperf.perf,
        tab_entrainement[i]->lepreuve.position_relais);  // Écrire le nom dans le fichier avec un saut de ligne
    }

    // printf("\n\n\nNouvelle valeur dans");

    
    fclose(fichier);  // Fermer le fichier
}





void addNewEntrainementSaisiUser(entrainement** tab_entrainement, int* nbEntrainement, char*epeuve){

    // Alloue de la mémoire pour un nouvel entraînement
    entrainement* p_new_entrainement = (entrainement*) malloc(sizeof(entrainement));
    
    int jour;
    int mois;
    int annee;
    int heure;
    int min;
    

    performance laperf;
    int position_relais;
    date ladate;
    

    // Demande à l'utilisateur de saisir la date de l'entraînement
    printf("\nDate de l'entrainement ?\n");
    jour  = demande_a_l_utilisateur_un_entier("jour ?",1,31);
    mois  = demande_a_l_utilisateur_un_entier("mois ?",1,12);
    annee = demande_a_l_utilisateur_un_entier("année ? (entre 2000 et 2024)",2000,2024);
    heure = demande_a_l_utilisateur_un_entier("heure ?",0,24);
    min   = demande_a_l_utilisateur_un_entier("minutes ?",0,60);

    // Transforme les données en structure date
    transforme_en_date(jour, mois, annee, heure, min, &ladate);


    // menu choix epreuve
    //displayMenuChoixUneEpreuveATaper(epeuve);

    // Demande à l'utilisateur de saisir la performance selon le type d'épreuve    
    if(strcmp(epeuve, "marathon")==0){
        demande_a_l_utilisateur_une_perf_marathon(&laperf);

    }
    else{
         demande_a_l_utilisateur_une_perf(&laperf);
    }


     // Si l'épreuve est un relais, demande à l'utilisateur la position dans le relais
    if(strcmp(epeuve, "relais")==0)
        position_relais = demande_a_l_utilisateur_un_entier(" Quelle était sa position dans le relai",1,4);

    else{
        position_relais = 0;
    }
    
    

    // Création d'un nouvel entraînement avec les données saisies
    p_new_entrainement = getNewEntrainement(ladate, epeuve, laperf, position_relais);
    

    printf("\n\nperf : %.2lf\n\n", laperf.perf);
    // ajout du nouvel entrainement dans le tab de tous les entrainements
    addNewEntrainementDansTab(tab_entrainement, nbEntrainement, p_new_entrainement);
}



//Ajout du nouvel entrainement dans le tab de tous les entrainements
void addNewEntrainementDansTab(entrainement** tab_entrainement, int* nbEntrainement, entrainement* p_new_entrainement) {


    tab_entrainement[*nbEntrainement] = p_new_entrainement;
    
    (*nbEntrainement)++;
    
}


// Creation nouvel entrainement
// return pointeur dessus
entrainement* getNewEntrainement(date la_date, char* epreuve, performance perf, int position_relais)
{
    // alloc new entrainement
    entrainement* p_new_entrainement = (entrainement*) malloc(sizeof(entrainement));
     
    p_new_entrainement->ladate.jour  = la_date.jour;
    p_new_entrainement->ladate.mois  = la_date.mois;
    p_new_entrainement->ladate.annee = la_date.annee;
    p_new_entrainement->ladate.heure = la_date.heure;
    p_new_entrainement->ladate.min   = la_date.min;
    p_new_entrainement->laperf.perf  = perf.perf;


    strcpy(p_new_entrainement->lepreuve.nom,epreuve); 

    p_new_entrainement->lepreuve.position_relais = (position_relais);  
    

    return p_new_entrainement;
}


// Ajout du nouvel entrainement dans le tab de tous les entrainements !
// 1. lit le fichier de l'athlete
// 2. ajout l'entrainement
// 3. reecris le fichier
void addNewEntrainementDansFichier(const char* nomAthlete, entrainement* p_new_entrainement)
{
    // 1. lit le fichier de l'athlete

    char filename[500];
    int nbEntrainement = 0;

    // generation du nom de fichier
    sprintf(filename, "data/%s.csv", nomAthlete);


    if ( !fichier_existe(filename) ) {
        printf("\nfichier introuvable : %s\n", filename);
        printf("Par conséquent le fichier a été créé");
        creer_fichier_si_non_existant(filename);
    }

    // lit le fichier
    entrainement** tab_entrainement = lis_un_fichier_d_entrainement(filename, &nbEntrainement);


    // 2.
    // ajout du nouvel entrainement dans le tab de tous les entrainements
    addNewEntrainementDansTab(tab_entrainement, &nbEntrainement, p_new_entrainement);


    // 3. reecris le fichier avec le nouvel entrainement
    writeArrayOftrainingTOfile(filename, tab_entrainement, nbEntrainement);


}