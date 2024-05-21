#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrainement.h"
#include "structure.h"
#include "read_data_file.h"


// void swap(entrainement** a, entrainement** b);


// void trie_perf(entrainement** tab_entrainement, int nb_entrainement, char* epreuve);


// entrainement** print_entrainements_trier(entrainement** tab_entrainement, int nb_entrainement, char* epreuve,  int*j);

// void affiche_pire_meilleur_temps(entrainement** tab_entrainement, int nb_entrainement);

void affiche_pire_meilleur_temps(entrainement** tab_entrainement_epreuve, int nb_filtre);


entrainement** print_entrainements_trier(entrainement** tab_entrainement, int nb_entrainement, const char* epreuve, int *nb_filtre) ;

void trie_entrainement_par_perf(entrainement** tab_entrainement, int nb_entrainement);

void swap(entrainement** a, entrainement** b);

int compare_date1_date2(const date *date1, const date *date2);

void trie_entrainement_par_date(entrainement** tab_entrainement, int nb_entrainement) ;

int compare_dates(const date *date1, const date *date2);

void affiche_new_tab(entrainement** tab_entrainement_epreuve, const char* epreuve, int *nb_filtre);

void print_entrainements_tries_par_date(entrainement** tab_entrainement, int nb_entrainement);

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