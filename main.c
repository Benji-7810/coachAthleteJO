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

    int num_athlete = 0;

    //entrainement** tab_entrainement = lis_un_fichier_d_entrainement(FILE_entrai, &nbEntrainement );
    
    // load athletes from file
    athlete** tab_athletes = readAthletesFromFile(FILE_ATHLETES, &nbAthletes);


        char nom_athlete[1000];
        char filename[1000] ;
        char fichier_nom[1000];

    
    // 
    while(1)
    {
        printf("\n\n");
        int user_choice = displayMenuPrincipal();
        switch( user_choice ){
                case 1 :

                        printArrayOfAthlete(tab_athletes, nbAthletes);

                        // printf("\nChoisi un athletes parmis cette liste de %d athltes\n",nbAthletes);
                        // scanf("%s",nom_athlete);
        

                        // sprintf(fichier_nom, "data/%s.csv", nom_athlete);
                        // printf("%s",fichier_nom);
                        // entrainement** tab_entrainement = lis_un_fichier_d_entrainement(fichier_nom, &nbEntrainement );


                        // addNewEntrainement(tab_entrainement, &nbEntrainement);
                        
        
                        

 
                      
                        // writeArrayOftrainingTOfile(fichier_nom,tab_entrainement, nbEntrainement);

                        // printf("\nVoici les nouvels perfs : \n");
                        
                        // printArrayOfentrainement(tab_entrainement, nbEntrainement);


                        break;

                //  consulter l'historique des entrainements d'un athlete
                case 2 :
                        
                        
                        printArrayOfAthlete(tab_athletes, nbAthletes);
                        
                        // choix de l'athlete
                        printf("\nChoisi un athletes parmis cette liste de %d athletes\n", nbAthletes);
                        scanf("%d", &num_athlete);


                        //printf("\nnom de l'athlete choisi : '%s'\n\n", tab_athletes[num_athlete-1]->prenom_nom);


                        // generation du nom de fichier
                        sprintf(filename, "data/%s.csv", tab_athletes[num_athlete-1]->prenom_nom);
                        
                        // for debug
                        //printf("\nfilename :  '%s'\n", filename);



                        if ( !fichier_existe(filename) ) {
                                printf("\nfichier introuvable: %s", filename);
                        }
                        

                        entrainement** tab_entrainement = lis_un_fichier_d_entrainement(FILE_entrai, &nbEntrainement );
                        printf(" tab_athletes[0]->prenom_nom : %s\n", tab_athletes[num_athlete-1]->prenom_nom);


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

                        // recupere le nouvel athete
                        sprintf(filename, "data/%s.csv",tab_athletes[0]->prenom_nom);

                        //printf("\n\n\n\n\nfilename : %s\n\n\n\n\n",filename);
                        
                        //regarde si il existe deja pas;
                        fichier_existe(filename);
                        //puis le créé
                        printf("\n\n\n\n\nfilename : %s\n\n\n\n\n",filename);
                        creer_fichier_si_non_existant(filename);

                        
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
