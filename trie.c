#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "structure.h"
#include "athletes.h"
#include "entrainement.h"
#include "read_data_file.h"
#include "trie.h"




// trie les entrainements par performance
void trie_entrainement_par_perf(entrainement** tab_entrainement, int nb_entrainement) {
    
    // tri par position relais
    for (int i = 1; i < nb_entrainement; i++) {
       
        // Stocker l'entraînement actuel comme clé
        entrainement* key = tab_entrainement[i];
        int j = i - 1;

        // Déplacer les éléments de tab_entrainement[0..i-1], qui sont plus grands que key->lepreuve.position_relais,
        // d'une position vers l'avant pour créer l'emplacement de l'élément key
        while (j >= 0  && tab_entrainement[j]->lepreuve.position_relais > key->lepreuve.position_relais) {
            tab_entrainement[j + 1] = tab_entrainement[j];
            j--;
        }

        // Placer key à sa position correcte dans le sous-tableau trié 
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

        // Placer key à sa position correcte dans le sous-tableau trié
        tab_entrainement[j + 1] = key;
    }

}



// retourne un tableau d'entrainement tirer
entrainement** print_entrainements_trier(entrainement** tab_entrainement, int nb_entrainement, const char* epreuve, int *nb_filtre) {
    
    // Allouer de la mémoire pour un tableau de pointeurs vers des structures entrainement
    // Ce tableau va stocker les entrainements filtrés selon l'épreuve spécifiée
    entrainement** tab_entrainement_epreuve = malloc(nb_entrainement * sizeof(entrainement*));
    
    // Vérifier si l'allocation mémoire a réussi
    if (!tab_entrainement_epreuve) {
        // Afficher un message d'erreur si l'allocation mémoire a échoué
        printf("Allocation mémoire échouée\n");
        return NULL; // Retourner NULL pour indiquer l'échec
    }

    // Initialiser le compteur de filtrage à 0
    *nb_filtre = 0;
    
    // Afficher l'épreuve pour laquelle les performances vont être triées
    printf("Performances triées pour l'épreuve: %s\n", epreuve);

    // Parcourir tous les entrainements pour filtrer ceux correspondant à l'épreuve spécifiée
    for (int i = 0; i < nb_entrainement; i++) {
        
        // Comparer le nom de l'épreuve de l'entrainement courant avec l'épreuve spécifiée
        if (strcmp(tab_entrainement[i]->lepreuve.nom, epreuve) == 0) {
            
            // Si c'est un match, ajouter l'entrainement au tableau filtré
            tab_entrainement_epreuve[*nb_filtre] = tab_entrainement[i];
            
            // Incrémenter le compteur de filtrage
            (*nb_filtre)++;
        }
    }

    // Trier les entrainements filtrés par performance
    // On appelle une fonction de tri qui doit être définie ailleurs dans le code
    trie_entrainement_par_perf(tab_entrainement_epreuve, *nb_filtre);

    // Retourner le tableau d'entrainements triés
    return tab_entrainement_epreuve;
}



// affiche un nouveau tableau
void affiche_new_tab(entrainement** tab_entrainement_epreuve, const char* epreuve, int *nb_filtre){
   
    // Parcourir tous les entrainements filtrés et triés
    for (int i = 0; i < *nb_filtre; i++) {
        
        // Afficher les détails de chaque entrainement
        printf("Entrainement %d -> Date: %s, Performance: %.2f sec\n",
               i+1,
               get_date_printable(tab_entrainement_epreuve[i]->ladate),
               tab_entrainement_epreuve[i]->laperf.perf);
    }
}



// affiche le pire_meilleur_temps 
void affiche_pire_meilleur_temps(entrainement** tab_entrainement_epreuve, int nb_filtre) {
    
    // Vérifier si le nombre d'entrainements filtrés est 0
    if (nb_filtre == 0) {
        
        // Afficher un message indiquant qu'il n'y a aucun entrainement correspondant à cette épreuve
        printf("Aucun entrainement correspondant à cette épreuve.\n");
        
        return; // Sortir de la fonction
    }

    // Afficher le meilleur temps (supposé être le premier après tri)
    printf("Meilleur temps : %.2f sec\n", tab_entrainement_epreuve[0]->laperf.perf);

    // Afficher le pire temps (supposé être le dernier après tri)
    printf("Pire temps : %.2f sec\n", tab_entrainement_epreuve[nb_filtre - 1]->laperf.perf);

    // Initialiser une variable pour la somme des performances
    double somme_perf = 0;

    // Parcourir tous les entrainements filtrés pour calculer la somme des performances
    for (int i = 0; i < nb_filtre; i++) {
        somme_perf += tab_entrainement_epreuve[i]->laperf.perf;
    }

    // Calculer la moyenne des performances
    double moyenne_perf = somme_perf / nb_filtre;

    // Afficher la moyenne des performances
    printf("Moyenne des performances : %.2f sec\n", moyenne_perf);
}
   
// }



// compare deux dates
int compare_date1_date2(const date *date1, const date *date2) {
    // Comparer les années
    if (date1->annee > date2->annee)
        return 1;
    if (date1->annee < date2->annee)
        return -1; 

    // Si les années sont égales, comparer les mois
    if (date1->mois > date2->mois)
        return 1; 
    if (date1->mois < date2->mois)
        return -1; 

    // Si les mois sont égaux, comparer les jours
    if (date1->jour > date2->jour)
        return 1; 
    if (date1->jour < date2->jour)
        return -1; 

    // Si les jours sont égaux, comparer les heures
    if (date1->heure > date2->heure)
        return 1;
    if (date1->heure < date2->heure)
        return -1; 

    // Si les heures sont égales, comparer les minutes
    if (date1->min > date2->min)
        return 1; 
    if (date1->min < date2->min)
        return -1; 

    // Si toutes les composantes de la date sont égales, les dates sont identiques
    return 0;
}



//fonction qui utilise le trie par insertion pour trier un tableau
void trie_entrainement_par_date(entrainement** tab_entrainement, int nb_entrainement) {
    
    // Parcourir tous les entrainements en commençant par le deuxième élément
    for (int i = 1; i < nb_entrainement; i++) {
        
        // Stocker le pointeur vers l'entrainement actuel
        entrainement* key = tab_entrainement[i];
        int j = i - 1;

        // Déplacer les éléments de tab_entrainement[0..i-1] qui sont plus récents que key à une position plus élevée
        while (j >= 0 && compare_date1_date2(&tab_entrainement[j]->ladate, &key->ladate) > 0) {
            tab_entrainement[j + 1] = tab_entrainement[j];
            j--;
        }

        // Insérer l'entrainement actuel à sa position correcte
        tab_entrainement[j + 1] = key;
    }
}



// affiche les 3 meilleurs groupe de relais à envoyer au JO
void affiche_athletes_relais(entrainement** tab_entrainement) {
    printf("\nvoici les 3 meilleurs groupes d'athlètes\n");

    // Affichage du premier groupe
    printf("\nMeilleur groupe  1- %s,   2- %s,   3- %s,   4 %16s avec un temps de %s\n",
        tab_entrainement[0]->nom,
        tab_entrainement[1]->nom,
        tab_entrainement[2]->nom,
        tab_entrainement[3]->nom,
        get_perf_printable(tab_entrainement[0]->laperf));

    // Affichage du deuxième groupe
    printf("\nDeuxième groupe  1- %s,   2- %s,   3- %s,   4 %16s avec un temps de %s\n",
        tab_entrainement[4]->nom,
        tab_entrainement[5]->nom,
        tab_entrainement[6]->nom,
        tab_entrainement[7]->nom,
        get_perf_printable(tab_entrainement[4]->laperf));

    // Affichage du troisième groupe
    printf("\nTroisième groupe 1- %s,   2- %s,   3- %s,   4 %16s avec un temps de %s\n",
        tab_entrainement[8]->nom,
        tab_entrainement[9]->nom,
        tab_entrainement[10]->nom,
        tab_entrainement[11]->nom,
        get_perf_printable(tab_entrainement[8]->laperf));
}



// affiche un entrainement sur une ligne
// ex: 
// Date: 15/05/2024 11:08, Performance: 1101.36 sec, epreuve: 5000m
void print_un_entrainement(entrainement* p_entrainement) {

    // Afficher la date, la performance et le nom de l'épreuve
    printf("Date: %s, Performance: %7.2f sec, epreuve: %10s",

            get_date_printable(p_entrainement->ladate), // Obtenir la date sous forme de chaîne de caractères
            p_entrainement->laperf.perf, // Performance de l'entraînement
            p_entrainement->lepreuve.nom); // Nom de l'épreuve

    // Vérifier si l'épreuve est un relais
    if (strcmp(p_entrainement->lepreuve.nom, "relais") == 0) {

        // Si c'est un relais, afficher également la position du relais
        printf(" position: %d\n", p_entrainement->lepreuve.position_relais);
    }

    // Ajouter une nouvelle ligne pour la lisibilité
    printf("\n");
}



// Fonction pour afficher les entrainements triés par date pour une épreuve spécifique
void print_entrainements_tries_par_epreuve(entrainement** tab_entrainement, int nb_entrainement) {

     // Trier les entraînements par date
    trie_entrainement_par_date(tab_entrainement, nb_entrainement);

    // Ajouter une ligne vide pour la lisibilité
    printf("\n");

    // Afficher les entraînements pour chaque type d'épreuve
    print_entrainement_par_epreuve(tab_entrainement, nb_entrainement, "100m");
    print_entrainement_par_epreuve(tab_entrainement, nb_entrainement, "400m");
    print_entrainement_par_epreuve(tab_entrainement, nb_entrainement, "5000m");
    print_entrainement_par_epreuve(tab_entrainement, nb_entrainement, "marathon");
    print_entrainement_par_epreuve(tab_entrainement, nb_entrainement, "relais");

}



// Fonction pour afficher les entrainements triés par date pour une épreuve spécifique
void print_entrainement_par_epreuve(entrainement** tab_entrainement, int nb_entrainement, const char* nom_epreuve) {
    
    // Affichage du nom de l'épreuve
    printf("\n\n %s\n", nom_epreuve);
    printf("************\n");

    int j = 1; // Variable pour compter les entraînements pour cette épreuve

    // Parcours de tous les entraînements
    for (int i = 0; i < nb_entrainement; i++) {
        
        // Vérification si l'entraînement correspond à l'épreuve spécifiée
        if (strcmp(tab_entrainement[i]->lepreuve.nom, nom_epreuve) == 0) {
            
            // Affichage de l'entraînement avec un numéro d'ordre
            print1entrainement(tab_entrainement[i], j);
            
            j++; // Incrémentation du compteur d'entraînements
        }
    }
}