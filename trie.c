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

void trie_perf(entrainement** tab_entrainement, int nb_entrainement, const char* epreuve) {
    for (int i = 1; i < nb_entrainement; i++) {
        entrainement* key = tab_entrainement[i];
        int j = i - 1;

        while (j >= 0 && tab_entrainement[j]->laperf.perf > key->laperf.perf && strcmp(tab_entrainement[j]->lepreuve.nom, epreuve) == 0) {
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

    trie_perf(tab_entrainement_epreuve, *nb_filtre, epreuve);

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
        printf("Date: %d/%d/%d %d:%d, Performance: %.2f sec\n",
               tab_entrainement_epreuve[i]->ladate.jour,
               tab_entrainement_epreuve[i]->ladate.mois,
               tab_entrainement_epreuve[i]->ladate.annee,
               tab_entrainement_epreuve[i]->ladate.heure,
               tab_entrainement_epreuve[i]->ladate.min,
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
   
// Assume the structures are defined as before

// Comparaison des dates
int compare_dates(const date *date1, const date *date2) {
    if (date1->annee != date2->annee)
        return date1->annee - date2->annee;
    if (date1->mois != date2->mois)
        return date1->mois - date2->mois;
    if (date1->jour != date2->jour)
        return date1->jour - date2->jour;
    if (date1->heure != date2->heure)
        return date1->heure - date2->heure;
    return date1->min - date2->min;
}

// Fonction pour trier les entrainements par date pour une épreuve donnée
void trie_entrainement_par_date(entrainement** tab_entrainement, int nb_entrainement, const char* epreuve) {
    for (int i = 1; i < nb_entrainement; i++) {
        entrainement* key = tab_entrainement[i];
        int j = i - 1;

        // Déplace les éléments de tab_entrainement[0..i-1], qui sont plus récents que key, à une position plus élevée
        while (j >= 0 && compare_dates(&tab_entrainement[j]->ladate, &key->ladate) > 0 && strcmp(tab_entrainement[j]->lepreuve.nom, epreuve) == 0) {
            tab_entrainement[j + 1] = tab_entrainement[j];
            j--;
        }
        tab_entrainement[j + 1] = key;
    }
}

// Fonction pour afficher les entrainements triés par date pour une épreuve spécifique
void print_entrainements_tries_par_date(entrainement** tab_entrainement, int nb_entrainement, const char* epreuve) {
    trie_entrainement_par_date(tab_entrainement, nb_entrainement, epreuve);
    for (int i = 0; i < nb_entrainement; i++) {
        if (strcmp(tab_entrainement[i]->lepreuve.nom, epreuve) == 0) {
            printf("Date: %d/%d/%d %d:%d, Performance: %.2f sec\n",
                   tab_entrainement[i]->ladate.jour,
                   tab_entrainement[i]->ladate.mois,
                   tab_entrainement[i]->ladate.annee,
                   tab_entrainement[i]->ladate.heure,
                   tab_entrainement[i]->ladate.min,
                   tab_entrainement[i]->laperf.perf);
        }
    }
}