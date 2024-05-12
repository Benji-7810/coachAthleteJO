#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrainement.h"
#include "structure.h"
#include "read_data_file.h"

#define NB_MAX_ATHLETES 100000


entrainement** lis_un_fichier_d_entrainement(const char* nomFichier, int* nb_entrainement ){
     
    
        // create TAB_DATA of athlete
    entrainement** TAB_DATA = (entrainement**) malloc(NB_MAX_ATHLETES * sizeof(entrainement*));

    if (TAB_DATA == NULL) {
        printf("Allocation memoire KO :  entrainement** TAB_DATA[NB_MAX_ATHLETES]");
        exit(1);
    }

     // read file => to "tab_lines"
    int nbLines = 0;
    char*** tab_lines = readDataFile(nomFichier, ";", &nbLines);

    // for debug
    // printDataLines(tab_lines, nbLines);

    *nb_entrainement = nbLines;

    // create TAB_DATA of athlete
    // entrainement* TAB_DATA = malloc(*nb_entrainement * sizeof(entrainement));
    // if (TAB_DATA == NULL) {
    //     printf("Allocation memoire KO");
    //     exit(1);
    // }

    
    // fill TAB_DATA
    for (int i =0 ; i < nbLines ; i++) {


        // malloc athlete
        TAB_DATA[i] = (entrainement*) malloc(sizeof(entrainement));
        // Copier le nom d'entrainement dans le tableau final
        strcpy(TAB_DATA[i]->ladate.jour_mois_annee,  tab_lines[i][0]); 
        strcpy(TAB_DATA[i]->ladate.heure_min,       tab_lines[i][1]); 
        strcpy(TAB_DATA[i]->lepreuve.nom,           tab_lines[i][2]); 
        TAB_DATA[i]->laperf.perf =                  atof(tab_lines[i][3]);  
    }


    return TAB_DATA;
}


// print an array of Athlete
void printArrayOfentrainement(entrainement** TAB_DATA, int nbEntrainement)
{
    printf("Nombre d'athletes : %d\n", nbEntrainement);
    for (int i = 0; i < nbEntrainement; i++) {
        printf("entrainement %d -> date : %s, heure_min :%s, l'epreuve : %s, la perf : %f \n",
        i+1,
        TAB_DATA[i]->ladate.jour_mois_annee,
        TAB_DATA[i]->ladate.heure_min, 
        TAB_DATA[i]->lepreuve.nom, 
        TAB_DATA[i]->laperf.perf);
    }
}





// rewrite all athletes from array to file
void writeArrayOftrainingTOfile(const char* nomFichier, entrainement** tab_entrainement, int  nbEntrainement) {
    printf("woauf\n");
    printArrayOfentrainement(tab_entrainement, nbEntrainement);

    printf("woauf1\n");
    FILE* fichier = fopen(nomFichier, "w");  // on écrit tout le tableaux;

   
    if (!fichier) {  // Vérification si le fichier a bien été ouvert
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    
    for (int i = 0; i < nbEntrainement; i++) {
        fprintf(fichier, "%s;%s;%s;%f\n", 
        tab_entrainement[i]->ladate.jour_mois_annee,   
        tab_entrainement[i]->ladate.heure_min,
        tab_entrainement[i]->lepreuve.nom,
        tab_entrainement[i]->laperf.perf);  // Écrire le nom dans le fichier avec un saut de ligne
    }

    printf("\nnouvelle valeur\n");
    printArrayOfentrainement(tab_entrainement, nbEntrainement);
    
        printf("\nwoauf2");
    fclose(fichier);  // Fermer le fichier
}



void addNewEntrainement(entrainement** tab_entrainement, int* nbEntrainement){

    //*tab_entrainement = realloc(*tab_entrainement, ((*nbEntrainement)+1) * sizeof(entrainement*));

    // alloc new athlete
    entrainement* p_new_entrainement = (entrainement*) malloc(sizeof(entrainement));
    
    char la_date[100];
    char heure_min[100];
    char epeuve[100];
    float perf;
    
    printf("\nrentre un la date (ex 02/05/2058): ");
    scanf("%s", la_date);

    printf("\nrentre l'heure/min (ex  9h56): ");
    scanf("%s", heure_min);

    printf("\nrentre le type d'epreuve (ex 100m / 400m / 5000m / marathon / relais): ");
    scanf("%s", epeuve);

    printf("\nrentre le temps de sa perf (ex 10s): ");
    scanf("%f", &perf);
    
    

    // Copier le nom d'entrainement dans le tableau final
    strcpy(p_new_entrainement->ladate.jour_mois_annee,  la_date); 
    strcpy(p_new_entrainement->ladate.heure_min, heure_min); 
    strcpy(p_new_entrainement->lepreuve.nom,epeuve); 
    p_new_entrainement->laperf.perf = (perf);  
    
    tab_entrainement[*nbEntrainement] = p_new_entrainement;

    (*nbEntrainement)++;
    printf("\nnouveau tab\n");
    printArrayOfentrainement(tab_entrainement,*nbEntrainement);

    

    
}
