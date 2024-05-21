#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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

    //int choix_temps_ou_perf = 0;

    char nom_epreuve[100];        
    //entrainement** tab_entrainement = lis_un_fichier_d_entrainement(FILE_entrai, &nbEntrainement );
    
    // load athletes from file
    athlete** tab_athletes = readAthletesFromFile(FILE_ATHLETES, &nbAthletes);

    
        int j = 0;

        // char nom_athlete[500];
        char filename[500];
        int nbr = 0;
        int diff=0;

    
    // 
    while(1)
    {
        printf("\n\n");
        printf("     ********************\n");
        printf("     *  Menu Principal  *\n");
        printf("     ********************\n\n");
        int user_choice = displayMenuPrincipal();
        switch( user_choice ){
                
                // ajouter un entrainement : 
                case 1 :
                        // choix epreuve
                        displayMenuChoixUneEpreuveATaper(nom_epreuve);

                        if (strcmp(nom_epreuve, "retour") == 0) {
                                break;
                        }


                        // si different de "relais" => 1 seul athlete
                        if (strcmp(nom_epreuve, "relais") != 0)
                        {
                                
                                printArrayOfAthlete(tab_athletes, nbAthletes);
                        
                                // choix de l'athlete
                                //printArrayOfAthlete(tab_athletes, nbAthletes);
                                num_athlete = demande_a_l_utilisateur_un_entier_sans_affichage
                                ("\nChoisis un athlete parmis cette liste d'athletes pour ajouter l'entrainement\n", 1, nbAthletes);
                                

                                printf("\nnom de l'athlete choisi : '%s'\n\n", tab_athletes[num_athlete-1]->prenom_nom);


                                // generation du nom de fichier
                                sprintf(filename, "data/%s.csv", tab_athletes[num_athlete-1]->prenom_nom);

                                if ( !fichier_existe(filename) ) {
                                        printf("\nfichier introuvable: '%s'", filename);
                                        creer_fichier_si_non_existant(filename);
                                }
                                

                                entrainement** tab_d_un_entrainement = lis_un_fichier_d_entrainement(filename, &nbEntrainement);
                                

                                addNewEntrainementSaisiUser(tab_d_un_entrainement, &nbEntrainement,nom_epreuve);

                
                                writeArrayOftrainingTOfile(filename,tab_d_un_entrainement, nbEntrainement);


                                //affiche le nom de l'athlete
                                printf("%s \n\n",tab_athletes[num_athlete-1]->prenom_nom);


                                printArrayOfentrainement(tab_d_un_entrainement, nbEntrainement);
                                
                        }
                        else { 
                                //////////////////////
                                // RELAIS !!!
                                //////////////////////
                                
                                int tab_athlete_relais[4];
                                date date_relais;
                                int position_relais = 0;
                                performance laperf;
                                entrainement* p_new_entrainement;

                                printArrayOfAthlete(tab_athletes, nbAthletes);

                                entrainement*** tab_d_entrainements_relais = malloc(sizeof(entrainement**) * 4);
                                
                        
                                //athlete 1
                                tab_athlete_relais[0] = demande_a_l_utilisateur_un_entier_sans_affichage("\nChoisi l'athlete n°1: ", 1, nbAthletes)-1;
                                
                                //athlete 2
                                int i=0;
                                do {
                                        if (i > 0) { 
                                        printf("\nDeja choisi !! un autre stp"); 
                                        }
                                        tab_athlete_relais[1] = demande_a_l_utilisateur_un_entier_sans_affichage("\nChoisi l'athlete n°2: ", 1, nbAthletes)-1;
                                        i++;
                                } while (tab_athlete_relais[1]==tab_athlete_relais[0]);
                                
                                
                                //athlete 3
                                i=0;
                                do {
                                        if (i > 0) { 
                                        printf("\nDeja choisi !! un autre stp"); 
                                        }
                                        
                                        tab_athlete_relais[2] = demande_a_l_utilisateur_un_entier_sans_affichage("\nChoisi l'athlete n°3: ", 1, nbAthletes)-1;
                                        i++;

                                } while (tab_athlete_relais[2]==tab_athlete_relais[0] 
                                        || tab_athlete_relais[2]==tab_athlete_relais[1]);

                                
                                //athlete 4
                                i=0;
                                do {
                                        if (i > 0) { 
                                        printf("\nDeja choisi !! un autre stp"); 
                                        }
                                        
                                        tab_athlete_relais[3] = demande_a_l_utilisateur_un_entier_sans_affichage("\nChoisi l'athlete n°4: ", 1, nbAthletes)-1;
                                        i++;

                                } while (tab_athlete_relais[3]==tab_athlete_relais[0]
                                        || tab_athlete_relais[3]==tab_athlete_relais[1]
                                        || tab_athlete_relais[3]==tab_athlete_relais[2]);

                                // choix date
                                demande_a_l_utilisateur_une_date(&date_relais);

                                // perf globale
                                printf("Quel a été le chrono du relais ? ");
                                demande_a_l_utilisateur_une_perf(&laperf);


                                // ajout de la perf pour chaque athlete
                                for (int i = 0; i < 4; i++) {

                                        int indice_athlete = tab_athlete_relais[i];

                                        // for debug
                                        printf("\najout de la perf pour chaque athlete : %d : '%s'\n", i+1, tab_athletes[indice_athlete]->prenom_nom);

                                        
                                        position_relais = i + 1;
                                        p_new_entrainement = getNewEntrainement(date_relais, nom_epreuve, laperf, position_relais);


                                        addNewEntrainementDansFichier(tab_athletes[indice_athlete]->prenom_nom, p_new_entrainement);





                                        //for debug
                                        //print_un_entrainement(p_new_entrainement);

                                        // for debug
                                        //printf("\najout de la perf pour chaque athlete : %d", i);

                                        //addNewEntrainementDansTab(tab_d_entrainements_relais[i], &nbEntrainement_relais[i], p_new_entrainement);

                                        //printf("\nDEBUG ligne : %d OK\n", __LINE__);


                                        // for debug
                                        //printf("\najout de la perf pour chaque athlete : %i OK", i);

                                        
                                        // nom de fichier
                                        //sprintf(filename, "data/%s.csv", tab_athletes[indice_athlete]->prenom_nom);


                                        // lit le fichier d'entrainement de l'athlete
                                        // ajout le relais dans le tableau d'entrainement de l'athlete


                                        // reecris le fichier 
                                        //writeArrayOftrainingTOfile(filename, tab_d_entrainements_relais[i], nbEntrainement_relais[i]);
                                        //printf("\nMon relais %d: %s\n", (i +1 ), tab_athletes[indice_athlete]->prenom_nom);
                                }

                                
                                for (int i = 0; i < 4; i++) {
                                        free(tab_d_entrainements_relais[i]);
                                }
                                free(tab_d_entrainements_relais);
                                

                        }
                break;
      

      
                 // consulter les statistiques des athletes         
                case 2 :
                        
                        printf("\n\n");
                        printf("\n\n");
                        printf("     ********************\n");
                        printf("     *  Menu Athlete    *\n");
                        printf("     ********************\n\n");                        
                        nbr = displayMenuStatistiquesAthlete();

                        entrainement** tab_entrainement_ath;
                        int nbEntrainement_ath = 0;

                        switch( nbr ){

                                // consulter les entrainement d'un athlete par date
                                case 1:
                                
                                        printf("\n\n");
                               
                                        printArrayOfAthlete(tab_athletes, nbAthletes);
                                
                                        // choix de l'athlete
                                        do{
                                                printf("\nQuel Athlete ? ");
                                                scanf("%d", &num_athlete);
                                        }while(num_athlete<0 || num_athlete> nbAthletes);

                                        // generation du nom de fichier
                                        sprintf(filename, "data/%s.csv", tab_athletes[num_athlete-1]->prenom_nom);


                                        if ( !fichier_existe(filename) ) {
                                                printf("\nfichier introuvable : '%s'\n", filename);
                                                printf("Par conséquent le fichier a été créé");
                                                creer_fichier_si_non_existant(filename);
                                        }
                                
                                        
                                        tab_entrainement_ath = lis_un_fichier_d_entrainement(filename, &nbEntrainement_ath);


                                        printf("\nhistorique des entrainements\n\n");

                                        if( nbEntrainement_ath == 0 ) {
                                                printf("\nPas encore d'entrainement enregistré\n\n");
                                        }
                                
                                        // tri par date
                                        trie_entrainement_par_date(tab_entrainement_ath, nbEntrainement_ath);
                                        
                                        // affichage
                                        printArrayOfentrainement  (tab_entrainement_ath, nbEntrainement_ath);
                                        
                                        
                                        break;

                               case 2:
                                        // entrainement par epreuve
                                        printArrayOfAthlete(tab_athletes, nbAthletes);
                        
                                        // choix de l'athlete
                                        do{
                                                printf("\nChoisis un athlete parmis cette liste de %d athletes pour ajouter l'avancer de son entrainement par épreuve\n", nbAthletes);
                                                scanf("%d", &num_athlete);
                                        }while(num_athlete<0 || num_athlete> nbAthletes);


                                        printf("\nnom de l'athlete choisi : '%s'\n\n", tab_athletes[num_athlete-1]->prenom_nom);

                                                                      
                                        // generation du nom de fichier
                                        sprintf(filename, "data/%s.csv", tab_athletes[num_athlete-1]->prenom_nom);

                                        
                                        tab_entrainement_ath = lis_un_fichier_d_entrainement(filename, &nbEntrainement_ath );
                                        print_entrainements_tries_par_epreuve(tab_entrainement_ath, nbEntrainement_ath);

                                        break;

                                

                                case 3:
                                        // Progression de l’athlète
                                        printArrayOfAthlete(tab_athletes, nbAthletes);
                        
                                        // choix de l'athlete
                                        do{
                                                printf("\nChoisis un athlete parmis cette liste de %d athletes pour ajouter l'avancer de son entrainement par épreuve\n", nbAthletes);
                                                scanf("%d", &num_athlete);
                                        }while(num_athlete<0 || num_athlete> nbAthletes);


                                        printf("\nnom de l'athlete choisi : '%s'\n\n", tab_athletes[num_athlete-1]->prenom_nom);

                                                                      
                                        // generation du nom de fichier
                                        sprintf(filename, "data/%s.csv", tab_athletes[num_athlete-1]->prenom_nom);

                                        
                                        tab_entrainement_ath = lis_un_fichier_d_entrainement(filename, &nbEntrainement_ath );


                                        displayMenuChoixUneEpreuveATaper(nom_epreuve);
                                        if (strcmp(nom_epreuve, "retour") == 0) {
                                                break;
                                        }
                                        printf("\n");
                                        printf("\n");
                                        
                                        //trie_perf(tab_entrainement_ath, nbEntrainement_ath, nom_epreuve);
                                        trie_entrainement_par_perf(tab_entrainement_ath, nbEntrainement_ath);

                                        entrainement**tab_entrainement_epreuve = print_entrainements_trier(tab_entrainement_ath, nbEntrainement_ath, nom_epreuve,&j);
                                        
                                        printf("\n");

                                        affiche_pire_meilleur_temps(tab_entrainement_epreuve, j);
        
                                        break;

                                
                                case 4 :
                                        
                                        // Qui envoyer au JO
                                        displayMenuChoixUneEpreuveATaper(nom_epreuve);
                                        if (strcmp(nom_epreuve, "retour") == 0) {
                                                break;
                                        }
                                        printf("\n");printf("\n");
                                        entrainement** tab_tout_les_athletes = genererTableauEntrainements(FILE_ATHLETES,&nbTotalEntrainements,nom_epreuve);

                                        //afficherEntrainements(tab_tout_les_athletes,nbTotalEntrainements);

                                        //afficherEntrainementsTries(tab_tout_les_athletes, nbTotalEntrainements);
                                        
                                        // si pas relais
                                        if (strcmp(nom_epreuve, "relais") != 0){
                                        printf("\n");
                                        printf("\n");
                                        printf("\n");

                                     

                                        StatistiquesAthlete*stats = calculerStatistiques(tab_tout_les_athletes,nbTotalEntrainements, &nbAthletes);

                                        //affichetab(stats,nbAthletes);
                                        //printf("\n\n\n\n%d\n\n\n\n\n",nbAthletes);
                                        //trie_entrainement_par_perf(stats)
                                     
                                        afficherStatistiques(stats, nbAthletes);
                                        }
                                        // choix relais
                                        else{   
                                                // j'ai mis en commentaire l'affichage mais elle continue de trier par perf d'ou son utilité
                                                afficherEntrainements(tab_tout_les_athletes,nbTotalEntrainements);
                                                affiche_athletes_relais(tab_tout_les_athletes);
                                                
                                        }
                                        break;

                                case 5:
                                        // Progression de l’athlète
                                        printArrayOfAthlete(tab_athletes, nbAthletes);

                                        do{
                                        printf("\nChoisis un athlete parmis cette liste de %d athletes pour ajouter l'avancer de son entrainement par épreuve\n", nbAthletes);
                                        scanf("%d", &num_athlete);
                                        }while(num_athlete<0 || num_athlete> nbAthletes);

                                        sprintf(filename, "data/%s.csv", tab_athletes[num_athlete-1]->prenom_nom);

                                       
                                        do {
                                                printf("\nEntrez l'epreuve dont vous souhaitez voir la progression (ex 100m / 400m / 5000m / marathon / relais): ");
                                                scanf("%s", nom_epreuve);
                                                printf("\n\n");
                                        
                                        } while (strcmp(nom_epreuve, "100m") != 0 && strcmp(nom_epreuve, "400m") != 0 && strcmp(nom_epreuve, "5000m") != 0 && strcmp(nom_epreuve, "marathon") != 0 && strcmp(nom_epreuve, "relais") != 0);

                                        entrainement** tab_entrainement = lis_un_fichier_d_entrainement(filename, &nbEntrainement );

                                        //trie_perf(tab_entrainement, nbEntrainement, nom_epreuve);
                                        trie_entrainement_par_perf(tab_entrainement, nbEntrainement);

                                        entrainement** tab_epreuve= print_entrainements_trier(tab_entrainement, nbEntrainement, nom_epreuve,&j);
                                        affiche_new_tab(tab_epreuve, nom_epreuve, &j);

                                        printf("\n\n Veuillez saisir les 2 entrainements dont vous voulez constater la progression\n\n");
                                        int entr1, entr2;
                                        double pro;

                                        do
                                        {
                                                printf("Saisi le premier entrainement:");
                                                scanf("%d",&entr1);
                                        } while (entr1>j || entr1<1);

                                        //for debug
                                        //printf("\nj : %d\n\n",j);


                                        do
                                        {
                                                printf("Saisi le deuxieme entrainement:");
                                                scanf("%d",&entr2);
                                        } while (entr2>j|| entr1<1);
                                        
                                        pro=(tab_epreuve[entr1-1]->laperf.perf)-(tab_epreuve[entr2-1]->laperf.perf);
                                        //pro=(tab_epreuve[entr1]->laperf.perf)-(tab_epreuve[entr2]->laperf.perf);

                                        diff=nombre_jours(tab_epreuve[entr1-1]->ladate,tab_epreuve[entr2-1]->ladate);

                                        if (diff<0)
                                        {
                                                diff=diff*(-1);
                                        }
                                        
                                        

                                        if (pro<0)
                                        {
                                                pro=pro*(-1);
                                        }

                                        printf("%.2f",pro);

                                        if (entr1>entr2)
                                        {
                                                printf("\nl'athlete a gagne %.2f secondes en performance avec %d jours d'intervalle",pro,diff);
                                        }
                                        
                                        else{
                                                printf("\nl'athlete a perdu %.2f secondes en performance avec %d jours d'intervalle",pro,diff);
                                        }
                                        

                                
                                        

                                        break;

                                // retour
                                case 6:
                                        printf("\nretour");
                                        break;
                        
                                
                        } // fin switch statistiques des athletes
                        break;
                        
                case 3 :
                        // print all athletes
                        printf("\n");
                        printArrayOfAthlete(tab_athletes, nbAthletes);  
                        break;

                case 4 :
                        
                        printf("\n");
                        // rewrite all athletes from array to file
                        int ok = addNewAthlete(tab_athletes, &nbAthletes);
                        if (ok == 1) {
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

                        
                                printf("\nVoici la nouvelle liste d'athletes : \n");
                                writeArrayOfAthleteTOfile(FILE_ATHLETES, tab_athletes, nbAthletes);
                        }        
                        
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
