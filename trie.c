#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "structure.h"
#include "athletes.h"
#include "entrainement.h"
#include "read_data_file.h"
#include "trie.h"




void swap(entrainement** a, entrainement** b) {
    entrainement* temp = *a;
    *a = *b;
    *b = temp;
}

void trie_entrainement_par_perf(entrainement** tab_entrainement, int nb_entrainement) {
    
    // tri par position relais
    for (int i = 1; i < nb_entrainement; i++) {
       
        entrainement* key = tab_entrainement[i];
        int j = i - 1;

        // Vérifie si l'épreuve correspond et que la performance est inférieure (meilleure)
        while (j >= 0  && tab_entrainement[j]->lepreuve.position_relais > key->lepreuve.position_relais) {
            tab_entrainement[j + 1] = tab_entrainement[j];
            j--;
        }

        tab_entrainement[j + 1] = key;
    }

    // tri par position relais
    for (int i = 1; i < nb_entrainement; i++) {
       
        entrainement* key = tab_entrainement[i];
        int j = i - 1;

        // Vérifie si l'épreuve correspond et que la performance est inférieure (meilleure)
        while (j >= 0  && tab_entrainement[j]->laperf.perf > key->laperf.perf) {
            tab_entrainement[j + 1] = tab_entrainement[j];
            j--;
        }
        tab_entrainement[j + 1] = key;
    }

}

entrainement** print_entrainements_trier(entrainement** tab_entrainement, int nb_entrainement, const char* epreuve, int *nb_filtre) {
    entrainement** tab_entrainement_epreuve = malloc(nb_entrainement * sizeof(entrainement*));
    if (!tab_entrainement_epreuve) {
        printf("Allocation mémoire échouée\n");
        return NULL;
    }

    *nb_filtre = 0; // Initialiser le compteur de filtrage
    printf("Performances triées pour l'épreuve: %s\n", epreuve);

    for (int i = 0; i < nb_entrainement; i++) {
        if (strcmp(tab_entrainement[i]->lepreuve.nom, epreuve) == 0) {
            tab_entrainement_epreuve[*nb_filtre] = tab_entrainement[i];
            (*nb_filtre)++;
        }
    }

    //trie_perf(tab_entrainement_epreuve, *nb_filtre, epreuve);
    trie_entrainement_par_perf(tab_entrainement_epreuve, *nb_filtre);

    // for (int i = 0; i < *nb_filtre; i++) {
    //     printf("Date: %d/%d/%d %d:%d, Performance: %.2f sec\n",
    //            tab_entrainement_epreuve[i]->ladate.jour,
    //            tab_entrainement_epreuve[i]->ladate.mois,
    //            tab_entrainement_epreuve[i]->ladate.annee,
    //            tab_entrainement_epreuve[i]->ladate.heure,
    //            tab_entrainement_epreuve[i]->ladate.min,
    //            tab_entrainement_epreuve[i]->laperf.perf);
    //}

    return tab_entrainement_epreuve;
}



void affiche_new_tab(entrainement** tab_entrainement_epreuve, const char* epreuve, int *nb_filtre){
    for (int i = 0; i < *nb_filtre; i++) {
        printf("Entrainement %d -> Date: %s, Performance: %.2f sec\n",

               i+1,
               get_date_printable(tab_entrainement_epreuve[i]->ladate),
               tab_entrainement_epreuve[i]->laperf.perf);
    }
}




void affiche_pire_meilleur_temps(entrainement** tab_entrainement_epreuve, int nb_filtre){
    if (nb_filtre == 0) {
        printf("Aucun entrainement correspondant à cette épreuve.\n");
        return;
    }

    printf("Meilleur temps : %.2f sec\n", tab_entrainement_epreuve[0]->laperf.perf);
    printf("Pire temps : %.2f sec\n", tab_entrainement_epreuve[nb_filtre - 1]->laperf.perf);
    
    double somme_perf = 0;
    for (int i = 0; i < nb_filtre; i++) {
        somme_perf += tab_entrainement_epreuve[i]->laperf.perf;
    }
    double moyenne_perf = somme_perf / nb_filtre; // Calcul de la moyenne des performances
    printf("Moyenne des performances : %.2f sec\n", moyenne_perf); // Affichage de la moyenne
}
   
// }

int compare_date1_date2(const date *date1, const date *date2) {
    if (date1->annee > date2->annee)
        return 1;
    if (date1->annee < date2->annee)
        return -1;

    if (date1->mois > date2->mois)
        return 1;
    if (date1->mois < date2->mois)
        return -1;

    if (date1->jour > date2->jour)
        return 1;
    if (date1->jour < date2->jour)
        return -1;

    if (date1->heure > date2->heure)
        return 1;
    if (date1->heure < date2->heure)
        return -1;

    if (date1->min > date2->min)
        return 1;
    if (date1->min < date2->min)
        return -1;

    return 0;
}

// OK
void trie_entrainement_par_date(entrainement** tab_entrainement, int nb_entrainement) {
    for (int i = 1; i < nb_entrainement; i++) {
        entrainement* key = tab_entrainement[i];
        int j = i - 1;

        // Déplace les éléments de tab_entrainement[0..i-1] qui sont plus récents que key, à une position plus élevée
        while (j >= 0 && compare_date1_date2(&tab_entrainement[j]->ladate, &key->ladate) > 0) {
            tab_entrainement[j + 1] = tab_entrainement[j];
            j--;
        }
        tab_entrainement[j + 1] = key;
    }
}

void affiche_athletes_relais(entrainement** tab_entrainement){
    printf("\nvoici les 3 meilleur groupe d'atheltes\n");

    //premier groupe
    printf("\nMeilleur groupe  1- %s,   2- %s,   3- %s,   4 %16s avec un temps de %s\n",
    tab_entrainement[0]->nom,
    tab_entrainement[1]->nom,
    tab_entrainement[2]->nom,
    tab_entrainement[3]->nom,
    //tab_entrainement[0]->laperf.perf);
    get_perf_printable(tab_entrainement[0]->laperf));

    // deuxieme groupe
    printf("\nDeuxieme groupe  1- %s,   2- %s,   3- %s,   4 %16s avec un temps de %s\n",
    tab_entrainement[4]->nom,
    tab_entrainement[5]->nom,
    tab_entrainement[6]->nom,
    tab_entrainement[7]->nom,
    //tab_entrainement[0]->laperf.perf);
    get_perf_printable(tab_entrainement[4]->laperf));

    //troisieme groupe
     printf("\nTroisieme groupe 1- %s,   2- %s,   3- %s,   4 %16s avec un temps de %s\n",
    tab_entrainement[8]->nom,
    tab_entrainement[9]->nom,
    tab_entrainement[10]->nom,
    tab_entrainement[11]->nom,
    //tab_entrainement[0]->laperf.perf);
    get_perf_printable(tab_entrainement[8]->laperf));

}

// affiche un entrainement sur une ligne
// ex: 
// Date: 15/05/2024 11:08, Performance: 1101.36 sec, epreuve: 5000m
void print_un_entrainement(entrainement* p_entrainement) {

    printf("Date: %s, Performance: %7.2f sec, epreuve: %10s",
            get_date_printable(p_entrainement->ladate),
            p_entrainement->laperf.perf,
            p_entrainement->lepreuve.nom);

    if (strcmp(p_entrainement->lepreuve.nom, "relais") == 0)
    {
        printf(" position: %d\n", p_entrainement->lepreuve.position_relais);    
    }

    printf("\n");
}


/*
NE PAS UTILISER
// Fonction pour afficher les entrainements triés par date pour une épreuve spécifique
void print_entrainements_tries_par_date(entrainement** tab_entrainement, int nb_entrainement) {

    // tri  par date  
    trie_entrainement_par_date(tab_entrainement, nb_entrainement);

    printf("\n");

    // affiche tous les entrainements
    for (int i = 0; i < nb_entrainement; i++) {
        print_un_entrainement(tab_entrainement[i]);
    }

}
*/


// Fonction pour afficher les entrainements triés par date pour une épreuve spécifique
void print_entrainements_tries_par_epreuve(entrainement** tab_entrainement, int nb_entrainement) {

    // tri  par date  
    trie_entrainement_par_date(tab_entrainement, nb_entrainement);

    printf("\n");

    print_entrainement_par_epreuve(tab_entrainement, nb_entrainement, "100m");
    print_entrainement_par_epreuve(tab_entrainement, nb_entrainement, "400m");
    print_entrainement_par_epreuve(tab_entrainement, nb_entrainement, "5000m");
    print_entrainement_par_epreuve(tab_entrainement, nb_entrainement, "marathon");
    print_entrainement_par_epreuve(tab_entrainement, nb_entrainement, "relais");

}


// Fonction pour afficher les entrainements triés par date pour une épreuve spécifique
void print_entrainement_par_epreuve(entrainement** tab_entrainement, int nb_entrainement, const char* nom_epreuve) {

 
    printf("\n\n %s\n", nom_epreuve);
    printf("************\n");

    int j = 1;

    // affiche tous les entrainements
    for (int i = 0; i < nb_entrainement; i++) {

        if (strcmp(tab_entrainement[i]->lepreuve.nom, nom_epreuve) == 0) {
            
            print1entrainement(tab_entrainement[i], j);
            j++;
            
            //print_un_entrainement(tab_entrainement[i]);
        }

    }

}