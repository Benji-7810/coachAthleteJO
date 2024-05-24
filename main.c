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


// initialisation des variables nécessaire
    int nbTotalEntrainements = 0;

    int nbAthletes = 0;

    int nbEntrainement = 0;

    int num_athlete = 0;

    char nom_epreuve[100];        
    

    // load athletes from file
    athlete** tab_athletes = readAthletesFromFile(FILE_ATHLETES, &nbAthletes);

    
        int j = 0;

        // char non_athlet[500]
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
                        // Affichage du menu pour choisir une épreuve à saisir
                        displayMenuChoixUneEpreuveATaper(nom_epreuve);

                        
                        // Vérification si l'utilisateur souhaite revenir en arrière
                        if (strcmp(nom_epreuve, "retour") == 0) {
                                break;
                        }

                        // Si l'épreuve n'est pas un relais, alors un seul athlète est impliqué
                        if (strcmp(nom_epreuve, "relais") != 0) {
                                
                                // Affichage de la liste des athlètes disponibles
                                printArrayOfAthlete(tab_athletes, nbAthletes);
                                

                                // Choix de l'athlète
                                num_athlete = demande_a_l_utilisateur_un_entier_sans_affichage
                                ("\nChoisis un athlete parmis cette liste d'athletes pour ajouter l'entrainement\n", 1, nbAthletes);
                        

                                // Affichage du nom de l'athlète choisi
                                printf("\n\nnom de l'athlete choisi : '%s'\n\n", tab_athletes[num_athlete-1]->prenom_nom);


                                // Génération du nom de fichier pour l'athlète choisi
                                sprintf(filename, "data/%s.csv", tab_athletes[num_athlete-1]->prenom_nom);


                                // Vérification de l'existence du fichier, le crée s'il n'existe pas
                                if (!fichier_existe(filename)) {
                                        printf("\nfichier introuvable: '%s'", filename);
                                        creer_fichier_si_non_existant(filename);
                                }


                                // Lecture des entraînements existants de l'athlète depuis le fichier
                                entrainement** tab_d_un_entrainement = lis_un_fichier_d_entrainement(filename, &nbEntrainement);


                                // Ajout d'un nouvel entraînement saisi par l'utilisateur
                                addNewEntrainementSaisiUser(tab_d_un_entrainement, &nbEntrainement, nom_epreuve);


                                // Écriture des entraînements mis à jour dans le fichier
                                writeArrayOftrainingTOfile(filename, tab_d_un_entrainement, nbEntrainement);


                                // Affichage du nom de l'athlète
                                printf("%s \n\n", tab_athletes[num_athlete-1]->prenom_nom);

                                
                                // Affichage de la liste des entraînements mis à jour de l'athlète
                                printArrayOfentrainement(tab_d_un_entrainement, nbEntrainement);
                        }
                                
                        
                        else { 
                                //////////////////////
                                // RELAIS !!!
                                //////////////////////
                                
                              // Déclaration des variables nécessaires pour la gestion du relais
                                int tab_athlete_relais[4];
                                date date_relais;
                                int position_relais = 0;
                                performance laperf;
                                entrainement* p_new_entrainement;


                                // Affichage de la liste des athlètes disponibles
                                printArrayOfAthlete(tab_athletes, nbAthletes);


                                // Allocation dynamique d'un tableau de pointeurs vers des tableaux d'entraînements pour le relais
                                entrainement*** tab_d_entrainements_relais = malloc(sizeof(entrainement**) * 4);


                                // Sélection des athlètes pour le relais
                                // Athlète 1
                                tab_athlete_relais[0] = demande_a_l_utilisateur_un_entier_sans_affichage("\nSaisissez le numéro de l'athlète n°1: ", 1, nbAthletes) - 1;


                                // Athlète 2
                                int i = 0;
                                do {    
                                        // Si l'athlète a déjà été choisi
                                        if (i > 0) { 
                                                printf("\nDéjà choisi !! Choisissez un autre athlète s'il vous plaît."); 
                                        }

                                        tab_athlete_relais[1] = demande_a_l_utilisateur_un_entier_sans_affichage("\nSaisissez le numéro de l'athlète n°2: ", 1, nbAthletes) - 1;
                                        
                                        i++;

                                } while (tab_athlete_relais[1] == tab_athlete_relais[0]);


                                // Athlète 3
                                i = 0;
                                
                                do {
                                        // Si l'athlète a déjà été choisi
                                        if (i > 0) { 
                                                printf("\nDéjà choisi !! Choisissez un autre athlète s'il vous plaît."); 
                                        }
                                        
                                        tab_athlete_relais[2] = demande_a_l_utilisateur_un_entier_sans_affichage("\nSaisissez le numéro de l'athlète n°3: ", 1, nbAthletes) - 1;
                                        
                                        i++;
                                } while (tab_athlete_relais[2] == tab_athlete_relais[0] || tab_athlete_relais[2] == tab_athlete_relais[1]);
                                                                
                                // Athlète 4
                                i = 0;
                                do {
                                        // Si l'athlète a déjà été choisi
                                        if (i > 0) {

                                                printf("\nDéjà choisi !! Choisissez un autre athlète s'il vous plaît."); 
                                        }

                                        tab_athlete_relais[3] = demande_a_l_utilisateur_un_entier_sans_affichage("\nSaisissez le numéro de l'athlète n°4: ", 1, nbAthletes) - 1;
                                        
                                        i++;
                                } while (tab_athlete_relais[3] == tab_athlete_relais[0] || tab_athlete_relais[3] == tab_athlete_relais[1] || tab_athlete_relais[3] == tab_athlete_relais[2]);


                                // Choix de la date du relais
                                demande_a_l_utilisateur_une_date(&date_relais);

                               
                                // Demande de la performance globale du relais
                                printf("Quel a été le chrono du relais ? ");
                                demande_a_l_utilisateur_une_perf(&laperf);

                               
                                // Ajout de la performance pour chaque athlète
                                for (int i = 0; i < 4; i++) {
                                        int indice_athlete = tab_athlete_relais[i];
                                        printf("\nAjout de la performance pour l'athlète %d : '%s'\n", i + 1, tab_athletes[indice_athlete]->prenom_nom);
                                        
                                        position_relais = i + 1;
                                        
                                        p_new_entrainement = getNewEntrainement(date_relais, nom_epreuve, laperf, position_relais);
                                        
                                        addNewEntrainementDansFichier(tab_athletes[indice_athlete]->prenom_nom, p_new_entrainement);
                                }


                                // Libération de la mémoire allouée pour le tableau d'entraînements relais
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
                                                

                                                num_athlete = demande_a_l_utilisateur_un_entier_sans_affichage("\nSaisissez le numéro de l'athlète",1,nbAthletes);

                                                // Génération du nom de fichier
                                                sprintf(filename, "data/%s.csv", tab_athletes[num_athlete - 1]->prenom_nom);

                                                // Vérification de l'existence du fichier
                                                if (!fichier_existe(filename)) {
                                                        printf("\nFichier introuvable : '%s'\n", filename);
                                                        printf("Par conséquent le fichier a été créé.\n");
                                                        creer_fichier_si_non_existant(filename);
                                                }

                                                // Lecture des entraînements à partir du fichier
                                                tab_entrainement_ath = lis_un_fichier_d_entrainement(filename, &nbEntrainement_ath);

                                                
                                                printf("\nHistorique des entraînements :\n\n");

                                                
                                                if (nbEntrainement_ath == 0) {
                                                        printf("Pas encore d'entraînement enregistré.\n\n");
                                                }

                                                
                                                // Tri des entraînements par date
                                                trie_entrainement_par_date(tab_entrainement_ath, nbEntrainement_ath);
                                                
                                                
                                                // Affichage des entraînements
                                                printArrayOfentrainement(tab_entrainement_ath, nbEntrainement_ath);
                                                
                                                break;
                                        
                                        
                                        break;

                               case 2:
                                        // Entraînements par épreuve

                                        // Affiche la liste des athlètes
                                        printArrayOfAthlete(tab_athletes, nbAthletes);


                                        // Choix de l'athlète parmi la liste
                                        num_athlete = demande_a_l_utilisateur_un_entier_sans_affichage("\nSaisissez le numéro de l'athlète",1,nbAthletes);


                                        // Affiche le nom de l'athlète choisi
                                        printf("\nNom de l'athlète choisi : '%s'\n\n", tab_athletes[num_athlete - 1]->prenom_nom);


                                        // Génération du nom de fichier pour l'athlète choisi
                                        sprintf(filename, "data/%s.csv", tab_athletes[num_athlete - 1]->prenom_nom);


                                        // Lis les entraînements de l'athlète à partir du fichier
                                        tab_entrainement_ath = lis_un_fichier_d_entrainement(filename, &nbEntrainement_ath);


                                        // Affiche les entraînements triés par épreuve
                                        print_entrainements_tries_par_epreuve(tab_entrainement_ath, nbEntrainement_ath);

                                        break;

                                

                                case 3:
                                        // Progression de l’athlète

                                        // Affiche la liste des athlètes
                                        printArrayOfAthlete(tab_athletes, nbAthletes);

                                        // Choix de l'athlète parmi la liste
                                        num_athlete = demande_a_l_utilisateur_un_entier_sans_affichage("\nSaisissez le numéro de l'athlète",1,nbAthletes);


                                        // Affiche le nom de l'athlète choisi
                                        printf("\nNom de l'athlète choisi : '%s'\n\n", tab_athletes[num_athlete - 1]->prenom_nom);


                                        // Génère le nom de fichier pour l'athlète choisi
                                        sprintf(filename, "data/%s.csv", tab_athletes[num_athlete - 1]->prenom_nom);


                                        // Lis les entraînements de l'athlète à partir du fichier
                                        tab_entrainement_ath = lis_un_fichier_d_entrainement(filename, &nbEntrainement_ath);


                                        // Affiche le menu pour choisir une épreuve à taper
                                        displayMenuChoixUneEpreuveATaper(nom_epreuve);


                                        // Si l'utilisateur choisit de revenir en arrière, sort de la boucle
                                        if (strcmp(nom_epreuve, "retour") == 0) {
                                                break;
                                        }


                                        // Trie les entraînements de l'athlète par performance
                                        trie_entrainement_par_perf(tab_entrainement_ath, nbEntrainement_ath);


                                        // Affiche les entraînements triés par épreuve
                                        entrainement** tab_entrainement_epreuve = print_entrainements_trier(tab_entrainement_ath, nbEntrainement_ath, nom_epreuve, &j);

                                        printf("\n");


                                        // Affiche le meilleur et le pire temps ainsi que la moyenne des performances pour l'épreuve choisie
                                        affiche_pire_meilleur_temps(tab_entrainement_epreuve, j);

                                        break;

                                
                                case 4 :
                                        
                                        // Qui envoyer aux JO

                                        // Affiche le menu pour choisir une épreuve à taper
                                        displayMenuChoixUneEpreuveATaper(nom_epreuve);


                                        // Si l'utilisateur choisit de revenir en arrière, sort de la boucle
                                        if (strcmp(nom_epreuve, "retour") == 0) {
                                                break;
                                        }

                                        // Génère un tableau d'entraînements pour tous les athlètes pour l'épreuve choisie
                                        entrainement** tab_tout_les_athletes = genererTableauEntrainements(FILE_ATHLETES, &nbTotalEntrainements, nom_epreuve);


                                        // Si l'épreuve n'est pas un relais
                                        if (strcmp(nom_epreuve, "relais") != 0) {

                                                // Calcule et affiche les statistiques des athlètes pour l'épreuve choisie
                                                StatistiquesAthlete* stats = calculerStatistiques(tab_tout_les_athletes, nbTotalEntrainements, &nbAthletes);
                                                afficherStatistiques(stats, nbAthletes);
                                        } 
                                        // Si l'épreuve est un relais
                                        else {

                                                // Affiche les entraînements des athlètes pour l'épreuve de relais et les meilleurs groupes
                                                afficherEntrainements(tab_tout_les_athletes, nbTotalEntrainements);
                                                affiche_athletes_relais(tab_tout_les_athletes);
                                        }

                                        break;

                                case 5:
                                        // Progression de l’athlète

                                        // Affiche la liste des athlètes disponibles
                                        printArrayOfAthlete(tab_athletes, nbAthletes);


                                        // Demande à l'utilisateur de choisir un athlète parmi la liste
                                        num_athlete = demande_a_l_utilisateur_un_entier_sans_affichage("\nSaisissez le numéro de l'athlète",1,nbAthletes);


                                        // Récupère le nom du fichier correspondant à l'athlète choisi
                                        sprintf(filename, "data/%s.csv", tab_athletes[num_athlete - 1]->prenom_nom);


                                        // Demande à l'utilisateur de choisir une épreuve pour suivre la progression
                                        do {
                                                printf("\nEntrez l'épreuve dont vous souhaitez voir la progression (ex: 100m / 400m / 5000m / marathon / relais): ");
                                                scanf("%s", nom_epreuve);
                                                printf("\n\n");
                                        } while (strcmp(nom_epreuve, "100m") != 0 && strcmp(nom_epreuve, "400m") != 0 && strcmp(nom_epreuve, "5000m") != 0 && strcmp(nom_epreuve, "marathon") != 0 && strcmp(nom_epreuve, "relais") != 0);



                                        // Lit les entraînements du fichier correspondant à l'athlète et à l'épreuve choisie
                                        entrainement** tab_entrainement = lis_un_fichier_d_entrainement(filename, &nbEntrainement);
                                        if(nbEntrainement<2){
                                                printf("\n       Pas assez d'entrainement enregistré il en faut minumum 2");
                                                break;
                                        }

                                        // Trie les entraînements par performance
                                        trie_entrainement_par_perf(tab_entrainement, nbEntrainement);


                                        // Affiche les entraînements triés par performance pour l'épreuve choisie
                                        entrainement** tab_epreuve = print_entrainements_trier(tab_entrainement, nbEntrainement, nom_epreuve, &j);
                                        affiche_new_tab(tab_epreuve, nom_epreuve, &j);


                                        // Demande à l'utilisateur de saisir les deux entraînements pour comparer leur progression
                                        printf("\n\n Veuillez saisir les deux entraînements dont vous souhaitez constater la progression\n\n");

                                        int entr1, entr2;
                                        double pro;

                                        // Demande le premier entraînement
                                        entr1 = demande_a_l_utilisateur_un_entier_sans_affichage("\nSaisissez le numéro de l'athlète",1,j);
                                        
                                        // Demande le deuxième entraînement
                                        entr2 = demande_a_l_utilisateur_un_entier_sans_affichage("\nSaisissez le numéro de l'athlète",1,j);


                                        // Calcule la différence de performance entre les deux entraînements
                                        pro = (tab_epreuve[entr1 - 1]->laperf.perf) - (tab_epreuve[entr2 - 1]->laperf.perf);
                                        diff = nombre_jours(tab_epreuve[entr1 - 1]->ladate, tab_epreuve[entr2 - 1]->ladate);

                                        // Assure que la différence de jours est positive
                                        if (diff < 0) {
                                                diff = diff * (-1);
                                        }

                                        // Assure que la différence de performance est positive
                                        if (pro < 0) {
                                                pro = pro * (-1);
                                        }


                                        // Affiche la différence de performance et la différence de jours entre les deux entraînements
                                        printf("%.2f", pro);


                                        // Affiche si l'athlète a gagné ou perdu en performance et la différence de jours
                                        if (entr1 > entr2) {
                                                printf("\nL'athlète a gagné %.2f secondes en performance avec %d jours d'intervalle.", pro, diff);
                                        } 
                                        else {
                                                printf("\nL'athlète a perdu %.2f secondes en performance avec %d jours d'intervalle.", pro, diff);
                                        }
                                        
                                // retour
                                case 6:
                                        printf("\nretour");
                                        break;
                        
                                
                        } // fin switch statistiques des athletes
                        break;
                        
                
                
                
                case 3 :
                        printf("\n");

                        //affiche le tableau d'un athlete
                        printArrayOfAthlete(tab_athletes, nbAthletes);  
                        break;

                
                
                
                case 4 :
                        
                        printf("\n");
                        // rewrite all athletes from array to file
                        int ok = addNewAthlete(tab_athletes, &nbAthletes);
                        if (ok == 1) {

                                // retrouve et stock le nom du fichier 
                                sprintf(filename, "data/%s.csv",tab_athletes[nbAthletes-1]->prenom_nom);

                                
                        
                                printf("\n");

                                //regarde si il existe deja pas;
                                fichier_existe(filename);

                                //puis le créé
                                creer_fichier_si_non_existant(filename);

                        
                                printf("\nVoici la nouvelle liste d'athletes : \n");

                                // reecrit tous les athletes du tableau du fichier
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
