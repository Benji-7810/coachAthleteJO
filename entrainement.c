#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrainement.h"
#include "structure.h"
#include "read_data_file.h"

entrainement* lis_un_fichier_d_entrainement(const char* nomFichier, int* nb_entrainement ){
     // read file => to "tab_lines"
    int nbLines = 0;
    char*** tab_lines = readDataFile(nomFichier, ";", &nbLines);

    // for debug
    // printDataLines(tab_lines, nbLines);

    *nb_entrainement = nbLines;

    // create TAB_DATA of athlete
    entrainement* TAB_DATA = malloc(*nb_entrainement * sizeof(entrainement));
    if (TAB_DATA == NULL) {
        printf("Allocation memoire KO");
        exit(1);
    }

    
    // fill TAB_DATA
    for (int i =0 ; i < nbLines ; i++) {

        // Copier le nom d'entrainement dans le tableau final
        strcpy(TAB_DATA[i].ladate.jour_mois_annee,  tab_lines[i][0]); 
        strcpy(TAB_DATA[i].ladate.heure_min,       tab_lines[i][1]); 
        strcpy(TAB_DATA[i].lepreuve.nom,           tab_lines[i][2]); 
        TAB_DATA[i].laperf.perf =                  atof(tab_lines[i][3]);  
    }


    return TAB_DATA;
}


// print an array of Athlete
void printArrayOfentrainement(entrainement* TAB_DATA, int nbEntrainement)
{
    printf("Nombre d'athletes : %d\n", nbEntrainement);
    for (int i = 0; i < nbEntrainement; i++) {
        printf("entrainement %d -> date : %s, heure_min :%s, l'epreuve : %s, la perf : %f \n",
        i+1,
        TAB_DATA[i].ladate.jour_mois_annee,
        TAB_DATA[i].ladate.heure_min, 
        TAB_DATA[i].lepreuve.nom, 
        TAB_DATA[i].laperf.perf);
    }
}


