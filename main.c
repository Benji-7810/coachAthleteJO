#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"
#include "athletes.h"

#define FILE_ATHLETES "data/athletes.csv"


int main() {
    int nbAthletes = 0;

    
    //rajoute_moi();
    // load athletes from file
    athlete* tab_athletes = readAthletesFromFile(FILE_ATHLETES, &nbAthletes);


    
    // 
    int user_choice = displayMenuPrincipal();
    switch( user_choice ){
        case 1 :
                printf("bah non ca marche pas");
                break;
        case 2 :
                printf("bah non ca marche pas");
                break;
        case 3 :
                printf("bah non ca marche pas");
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
