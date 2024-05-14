#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrainement.h"
#include "structure.h"
#include "read_data_file.h"

#define NB_MAX_ATHLETES 10000000


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
    //printDataLines(tab_lines, nbLines);


    *nb_entrainement = nbLines;


    
    // fill TAB_DATA
    for (int i =0 ; i < nbLines ; i++) {


        // malloc athlete

        TAB_DATA[i] = (entrainement*) malloc(sizeof(entrainement));
        // Copier le nom d'entrainement dans le tableau final
        TAB_DATA[i]->ladate.jour =                  atof(tab_lines[i][0]);
        TAB_DATA[i]->ladate.mois =                  atof(tab_lines[i][1]);
        TAB_DATA[i]->ladate.annee =                  atof(tab_lines[i][2]);
        TAB_DATA[i]->ladate.heure =                  atof(tab_lines[i][3]);
        TAB_DATA[i]->ladate.min =                  atof(tab_lines[i][4]);
        // strcpy(TAB_DATA[i]->ladate.jour_mois_annee,  tab_lines[i][0]); 
        // strcpy(TAB_DATA[i]->ladate.heure_min,       tab_lines[i][1]); 
        strcpy(TAB_DATA[i]->lepreuve.nom,           tab_lines[i][5]); 
        TAB_DATA[i]->laperf.perf =                  atof(tab_lines[i][6]);
        TAB_DATA[i]->lepreuve.position_relais =                  atof(tab_lines[i][7]);
          
    }


    return TAB_DATA;
}


// print an array of Athlete
void printArrayOfentrainement(entrainement** TAB_DATA, int nbEntrainement)
{
    printf("Nombre d'entrainenement : %d\n", nbEntrainement);

    for (int i = 0; i < nbEntrainement; i++) {
        printf("entrainement %d -> date : %d/%d/%d, heure_min : %d:%d, l'epreuve : %s, la perf : %f \n",
        i+1,
        TAB_DATA[i]->ladate.jour,
        TAB_DATA[i]->ladate.heure,
        TAB_DATA[i]->ladate.annee,
        TAB_DATA[i]->ladate.heure,
        TAB_DATA[i]->ladate.min,
        TAB_DATA[i]->lepreuve.nom, 
        TAB_DATA[i]->laperf.perf);
    }
}





// rewrite all athletes from array to file
void writeArrayOftrainingTOfile(const char* nomFichier, entrainement** tab_entrainement, int  nbEntrainement) {
 


  
    FILE* fichier = fopen(nomFichier, "w");  // on écrit tout le tableaux;

   
    if (!fichier) {  // Vérification si le fichier a bien été ouvert
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    
    for (int i = 0; i < nbEntrainement; i++) {
        fprintf(fichier, "%d;%d;%d;%d;%d;%s;%f;%d\n", 
        tab_entrainement[i]->ladate.jour,
        tab_entrainement[i]->ladate.heure,  
        tab_entrainement[i]->ladate.annee,  
        tab_entrainement[i]->ladate.heure,  
        tab_entrainement[i]->ladate.min,     
        tab_entrainement[i]->lepreuve.nom,
        tab_entrainement[i]->laperf.perf,
        tab_entrainement[i]->lepreuve.position_relais);  // Écrire le nom dans le fichier avec un saut de ligne
    }

    printf("\n\n\nNouvelle valeur dans");

    
    fclose(fichier);  // Fermer le fichier
}



void addNewEntrainement(entrainement** tab_entrainement, int* nbEntrainement){

    //*tab_entrainement = realloc(*tab_entrainement, ((*nbEntrainement)+1) * sizeof(entrainement*));

    // alloc new athlete
    entrainement* p_new_entrainement = (entrainement*) malloc(sizeof(entrainement));
    
    int jour;
    int mois;
    int annee;
    int heure;
    int min;
    char epeuve[100];
    float perf;
    int position_relais;
    int check;
    
    do
    {   
        printf("\nRentrer le jour de l'entrainement : ");
        scanf("%d", &jour);}
    while((jour > 31 || jour<0));


    do{
        printf("rentre le mois : ");
        scanf("%d",&mois);
    }while((jour==31 && ( mois==2 || mois==4 || mois ==6 || mois==9 || mois == 11 )));


    do{
         printf("rentre l'annee : ");
        scanf("%d",&annee);
    

    } while (jour==29 && mois ==2 && (annee%4!=0 && annee%100==0));


    do
    {
        printf("\nrentre l'heure : ");
        scanf("%d",&heure ); 
        printf("\nrentre la min : ");
        scanf("%d",&min ); 
    }   while((heure<0 || heure>23) && ( min<0 || min>59));



    do {
        printf("\nEntre le type d'épreuve (ex 100m / 400m / 5000m / marathon / relais): ");
        scanf("%s", epeuve);
    } while (strcmp(epeuve, "100m") != 0 && strcmp(epeuve, "400m") != 0 && strcmp(epeuve, "5000m") != 0 && strcmp(epeuve, "marathon") != 0 && strcmp(epeuve, "relais") != 0);

    

    printf("\nrentre le temps de sa perf (en float) : ");
    scanf("%f", &perf);


    if(strcmp(epeuve, "relais")==0){
        do{
            printf("\n Quelle était sa position dans le relay");
            scanf("%d",&position_relais);    
    }   while(position_relais<1 || position_relais>4);
    }
    else{
        position_relais = 0;
    }
    
    
    p_new_entrainement->ladate.jour = (jour);
    p_new_entrainement->ladate.mois = (mois);
    p_new_entrainement->ladate.annee = (annee);
    p_new_entrainement->ladate.heure = (heure);
    p_new_entrainement->ladate.min = (min);

    
    // Copier le nom d'entrainement dans le tableau final
    // strcpy(p_new_entrainement->ladate.jour_mois_annee,  la_date); 
    // strcpy(p_new_entrainement->ladate.heure_min, heure_min); 
    strcpy(p_new_entrainement->lepreuve.nom,epeuve); 
    p_new_entrainement->laperf.perf = (perf);
    p_new_entrainement->lepreuve.position_relais = (position_relais);  
    
    tab_entrainement[*nbEntrainement] = p_new_entrainement;

    (*nbEntrainement)++;
    
}

