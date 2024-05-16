#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "structure.h"
#include "athletes.h"
#include "entrainement.h"
#include "read_data_file.h"
#include "trie.h"
#include "Athletes_Selectione_JO.h"


#define FILE_ATHLETES "data/athletes.csv"



int main() {

    int nbTotalEntrainements = 0;

    int nbAthletes = 0;

    int nbEntrainement = 0;

    int num_athlete = 0;

    int choix_temps_ou_perf = 0;

        char nom_epreuve[100];        
    //entrainement** tab_entrainement = lis_un_fichier_d_entrainement(FILE_entrai, &nbEntrainement );
    
    // load athletes from file
    athlete** tab_athletes = readAthletesFromFile(FILE_ATHLETES, &nbAthletes);

    
        int j = 0;

        char nom_athlete[500];
        char filename[1500] ;
        char fichier_nom[1000];
        int nbr = 0;

    
    // 
    while(1)
    {
        printf("\n\n");
        printf("       Interface\n\n");
        int user_choice = displayMenuPrincipal();
        switch( user_choice ){
                
                // performances athletes : 
                case 1 :
                        nbr = demande_a_l_utilisateur_un_entier_sans_affichage("    1 : consulter les entrainement d'un athlte\n\n    2 : ajouter un entrainement ",1,2);
                        if (nbr ==1){
                                                   
                                printf("\n");printf("\n");printf("\n");
                                
                               
                                printArrayOfAthlete(tab_athletes, nbAthletes);
                        
                                // choix de l'athlete
                                printf("\nChoisi un athlète parmi cette liste de %d athlètes pour regarder ses entrainements\n", nbAthletes);
                                scanf("%d", &num_athlete);

                                // generation du nom de fichier
                                sprintf(filename, "data/%s.csv", tab_athletes[num_athlete-1]->prenom_nom);


                                if ( !fichier_existe(filename) ) {
                                        printf("\nfichier introuvable : %s\n", filename);
                                        printf("Par conséquent le fichier a été créé");
                                        creer_fichier_si_non_existant(filename);}
                        

                                entrainement** tab_entrainement = lis_un_fichier_d_entrainement(filename, &nbEntrainement );
                        

                                printf("\nconsulter l'historique des entrainements\n\n");

                                if(nbEntrainement == 0){
                                        printf("\nPas encore d'entrainement enregistré\n\n");
                                }

                                tab_entrainement = lis_un_fichier_d_entrainement(filename, &nbEntrainement);
                        
                                printArrayOfentrainement(tab_entrainement, nbEntrainement);

                                break;
                        }
                        else{
                                            
                                printArrayOfAthlete(tab_athletes, nbAthletes);
                        
                                // choix de l'athlete
                                printf("\nChoisi un athletes parmis cette liste de %d athletes pour ajouter l'entrainement\n", nbAthletes);
                                scanf("%d", &num_athlete);


                                printf("\nnom de l'athlete choisi : '%s'\n\n", tab_athletes[num_athlete-1]->prenom_nom);


                                // generation du nom de fichier
                                sprintf(filename, "data/%s.csv", tab_athletes[num_athlete-1]->prenom_nom);
                        


                                if ( !fichier_existe(filename) ) {
                                        printf("\nfichier introuvable: %s", filename);
                                        creer_fichier_si_non_existant(filename);
                                }
                                

                                entrainement** tab_d_un_entrainement = lis_un_fichier_d_entrainement(filename, &nbEntrainement);


                                addNewEntrainement(tab_d_un_entrainement, &nbEntrainement);
                        
                      
                                writeArrayOftrainingTOfile(filename,tab_d_un_entrainement, nbEntrainement);

                                //affiche le nom de l'athlete
                                printf("%s \n\n",tab_athletes[num_athlete-1]->prenom_nom);

       
                                printArrayOfentrainement(tab_d_un_entrainement, nbEntrainement);


                                break;
                        }
        
      
                        
                case 2 :
                        
                        nbr = demande_a_l_utilisateur_un_entier_sans_affichage(" 1-résumé des performances d’un athlète \n 2-Qui envoyer au JO\n 3-Progression de l’athlète",1,3);

                        switch( nbr ){

                                case 1 :
                                        printArrayOfAthlete(tab_athletes, nbAthletes);
                        
                                        // choix de l'athlete
                                        printf("\nChoisi un athletes parmis cette liste de %d athletes pour ajouter l'avancer de son entrainement par épreuve\n", nbAthletes);
                                        scanf("%d", &num_athlete);


                                        printf("\nnom de l'athlete choisi : '%s'\n\n", tab_athletes[num_athlete-1]->prenom_nom);

                                                                      
                                        // generation du nom de fichier
                                        sprintf(filename, "data/%s.csv", tab_athletes[num_athlete-1]->prenom_nom);

                                        do {
                                        printf("\nEntre le type d'épreuve (ex 100m / 400m / 5000m / marathon / relais): ");
                                        scanf("%s", nom_epreuve);
                                        } while (strcmp(nom_epreuve, "100m") != 0 && strcmp(nom_epreuve, "400m") != 0 && strcmp(nom_epreuve, "5000m") != 0 && strcmp(nom_epreuve, "marathon") != 0 && strcmp(nom_epreuve, "relais") != 0);

                                        entrainement** tab_d_un_entrainement = lis_un_fichier_d_entrainement(filename, &nbEntrainement );

                                        trie_perf(tab_d_un_entrainement, nbEntrainement, nom_epreuve);

                                        entrainement**tab_entrainement_epreuve = print_entrainements_trier(tab_d_un_entrainement, nbEntrainement, nom_epreuve,&j);

                                        choix_temps_ou_perf = demande_a_l_utilisateur_un_entier_sans_affichage("\n\n1- afficher c'est perfomances clés (pire/meilleur/moyenne) \n2- afficher par date ",1,2);
                                        if(choix_temps_ou_perf == 1){
                                                affiche_pire_meilleur_temps(tab_entrainement_epreuve, j);}

                                        else{
                                                affiche_new_tab(tab_entrainement_epreuve, nom_epreuve, &j);

                                        }
        
                                        break;

                                case 2 :

                                       do {
                                        printf("\nEntre le type d'épreuve (ex 100m / 400m / 5000m / marathon / relais): ");
                                        scanf("%s", nom_epreuve);
                                        } while (strcmp(nom_epreuve, "100m") != 0 && strcmp(nom_epreuve, "400m") != 0 && strcmp(nom_epreuve, "5000m") != 0 && strcmp(nom_epreuve, "marathon") != 0 && strcmp(nom_epreuve, "relais") != 0);
                                        printf("\n");printf("\n");
                                        entrainement** tab_tout_les_athletes = genererTableauEntrainements(FILE_ATHLETES,&nbTotalEntrainements,nom_epreuve);

                                        //afficherEntrainements(tab_tout_les_athletes,nbTotalEntrainements);

                                        //afficherEntrainementsTries(tab_tout_les_athletes, nbTotalEntrainements);

                                        printf("\n");
                                        printf("\n");
                                        printf("\n");

                                        StatistiquesAthlete*stats = calculerStatistiques(tab_tout_les_athletes,nbTotalEntrainements, &nbAthletes);

                                        affichetab(stats,nbAthletes);
                                        printf("\n\n\n\n%d\n\n\n\n\n",nbAthletes);

                                        afficherStatistiques(stats, nbAthletes);
                                        break;

                                case 3 :
                                        printf("pas fais");
                                        break;
                    
                        

                        break;
                        }
                        
                case 3 :
                        // print all athletes
                        printf("\n");
                        printf("\n");
                        printArrayOfAthlete(tab_athletes, nbAthletes);  
                        break;
                case 4 :
                        
                        printf("\n");
                        // rewrite all athletes from array to file
                        addNewAthlete(tab_athletes, &nbAthletes);
                        
                        //for debug
                        //printf("\n\nnbAthletes :%d\n",nbAthletes);
                        
                        //for debug
                        //printf("\n\n\ntab_athletes[nbAthletes]->prenom_nom : %s\n\n",tab_athletes[nbAthletes]->prenom_nom);
                        // recupere le nouvel athete


                        sprintf(filename, "data/%s.csv",tab_athletes[nbAthletes-1]->prenom_nom);

                        
                   
                        printf("\n");
                        //regarde si il existe deja pas;
                        fichier_existe(filename);

                        //puis le créé
                        //printf("\n\n\n\n\nfilename : %s\n\n\n\n\n",filename);
                        creer_fichier_si_non_existant(filename);

                       
                        printf("\nVoici ton nouveau tableau : \n\n");
                        writeArrayOfAthleteTOfile(FILE_ATHLETES, tab_athletes, nbAthletes);


                        
                        
                        break;
                case 5 :
                        exit(1);
                        break;
        } 
    }

    


    // free memory
    free(tab_athletes);



    return 0;
}

