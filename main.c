#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "structure.h"
#include "athletes.h"
#include "entrainement.h"
#include "read_data_file.h"


#define FILE_ATHLETES "data/athletes.csv"
#define FILE_entrai "data/Usain Bolt.csv"



int main() {



    int nbAthletes = 0;

    int nbEntrainement = 0;

    entrainement** tab_entrainement = lis_un_fichier_d_entrainement(FILE_entrai, &nbEntrainement );
    
    // load athletes from file
    athlete** tab_athletes = readAthletesFromFile(FILE_ATHLETES, &nbAthletes);


        char nom_athlete[50] = "Usain Bolt";
        char filename[100];

    
    // 
    while(1)
    {
        printf("\n\n");
        int user_choice = displayMenuPrincipal();
        switch( user_choice ){
                case 1 :

                        
                        printf("\nVoici les nouvels perfs : \n");
                        addNewEntrainement(tab_entrainement, &nbEntrainement);

                        writeArrayOftrainingTOfile(FILE_entrai,tab_entrainement, nbEntrainement);

                        printf("\nVoici les nouvels perfs : \n");
                        
                        printArrayOfentrainement(tab_entrainement, nbEntrainement);


                        break;
                case 2 :
                        

                        sprintf(filename, "data/%s.csv", nom_athlete);


                        printf("consulter l'historique des entrainements\n");
                        tab_entrainement = lis_un_fichier_d_entrainement(filename, &nbEntrainement);
                        
                        printArrayOfentrainement(tab_entrainement, nbEntrainement);

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
    }

    


    // free memory
    free(tab_athletes);



    return 0;
}
