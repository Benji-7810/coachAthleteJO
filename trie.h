#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrainement.h"
#include "structure.h"
#include "read_data_file.h"



// affiche le pire_meilleur_temps 
void affiche_pire_meilleur_temps(entrainement** tab_entrainement_epreuve, int nb_filtre);


// retourne un tableau d'entrainement tirer
entrainement** print_entrainements_trier(entrainement** tab_entrainement, int nb_entrainement, const char* epreuve, int *nb_filtre) ;


// trie les entrainements par performance
void trie_entrainement_par_perf(entrainement** tab_entrainement, int nb_entrainement);


// compare deux dates
int compare_date1_date2(const date *date1, const date *date2);


//fonction qui utilise le trie par insertion pour trier un tableau
void trie_entrainement_par_date(entrainement** tab_entrainement, int nb_entrainement) ;



// affiche un nouveau tableau
void affiche_new_tab(entrainement** tab_entrainement_epreuve, const char* epreuve, int *nb_filtre);



// Fonction pour afficher les entrainements triés par date pour une épreuve spécifique
void print_entrainement_par_epreuve(entrainement** tab_entrainement, int nb_entrainement, const char* nom_epreuve);



// Fonction pour afficher les entrainements triés par date pour une épreuve spécifique
void print_entrainements_tries_par_epreuve(entrainement** tab_entrainement, int nb_entrainement);



// affiche un entrainement sur une ligne
// ex: 
// Date: 15/05/2024 11:08, Performance: 1101.36 sec, epreuve: 5000m
void print_un_entrainement(entrainement* p_entrainement);



//affiche les meilleur groupe de relais
void affiche_athletes_relais(entrainement** tab_entrainement);