#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "structure.h"
#include "athletes.h"
#include "entrainement.h"
#include "read_data_file.h"
#include "trie.h"






// Fonction pour échanger deux pointeurs vers entrainement
void swap(entrainement** a, entrainement** b) {
    entrainement* temp = *a;
    *a = *b;
    *b = temp;
}


// Fonction pour trier les performances pour une épreuve donnée par insertion
void trie_perf(entrainement** tab_entrainement, int nb_entrainement, char* epreuve) {
    int i, j;
    entrainement* key;
    for (i = 1; i < nb_entrainement; i++) {
        key = tab_entrainement[i];
        j = i - 1;

        // Insertion sort: déplacer les éléments qui sont plus grands que key->perf et qui sont de la même épreuve
        while (j >= 0 && tab_entrainement[j]->laperf.perf > key->laperf.perf && strcmp(tab_entrainement[j]->lepreuve.nom, epreuve) == 0) {
            tab_entrainement[j + 1] = tab_entrainement[j];
            j--;
        }
        tab_entrainement[j + 1] = key;
    }
}


// Fonction pour afficher les résultats triés pour une épreuve spécifique
void print_entrainements_trier(entrainement** tab_entrainement, int nb_entrainement, char* epreuve) {
    printf("Performances triées pour l'épreuve: %s\n", epreuve);
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



void affiche_pire_meilleur_temps(entrainement** tab_entrainement, int nb_entrainement){
    printf("\nVoici son meilleur temps : %f\n",tab_entrainement[0]->laperf.perf);
    printf("\nVoici son pire temps : %f\n",tab_entrainement[nb_entrainement-1]->laperf.perf);
    float compteur_moyenne =0 ;

    for(int i =0 ;i<nb_entrainement;i++){
        compteur_moyenne+=tab_entrainement[i]->laperf.perf;
    }

    printf("\nVoici sa moyenne de temps : %f",compteur_moyenne/nb_entrainement);
}