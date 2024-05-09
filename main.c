#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"
#include "athletes.h"
#include "entrainement.h"
#include "read_data_file.h"


#define FILE_ATHLETES "data/athletes.csv"
#define FILE_entrai "data/Usain Bolt.txt"


int main() {
    int nbAthletes = 0;

    int nbr_entraienemnt = 0;
    entrainement* tab_entrainement;
    

    // load athletes from file
    athlete* tab_athletes = readAthletesFromFile(FILE_ATHLETES, &nbAthletes);



    // 
    int user_choice = displayMenuPrincipal();
    switch( user_choice ){
        case 1 :
                printf("bah non ca marche pas\n");


                break;
        case 2 :
                char nom_athlete[100] = "Usain Bolt";
                char filename[100];

                sprintf(filename, "data/%s.csv", nom_athlete);


                printf("consulter l'historique des entrainements\n");
                tab_entrainement = lis_un_fichier_d_entrainement(filename, &nbr_entraienemnt);
                
                printArrayOfentrainement(tab_entrainement, nbr_entraienemnt);

                break;


        case 3 :
                printf("bah non ca marche pas\n");
                break;
        case 4 :
                // print all athletes
                printArrayOfAthlete(tab_athletes, nbAthletes);  
                break;
        case 5 :
                // rewrite all athletes from array to file
                addNewAthlete(tab_athletes, &nbAthletes);

                writeArrayOfAthleteTOfile(FILE_ATHLETES, tab_athletes, nbAthletes);

                printf("\nVoici ton nouveau tableau : \n");

                printArrayOfAthlete(tab_athletes, nbAthletes);  
                break;
        case 6 :
                exit(1);
                break;
    } 


    


    // free memory
    free(tab_athletes);



    return 0;
}
