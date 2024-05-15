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

void trie_perf(entrainement** tab_entrainement, int nb_entrainement, const char* epreuve);


void swap(entrainement** a, entrainement** b);

void trie_entrainement_par_date(entrainement** tab_entrainement, int nb_entrainement, const char* epreuve);

void print_entrainements_tries_par_date(entrainement** tab_entrainement, int nb_entrainement, const char* epreuve);

int compare_dates(const date *date1, const date *date2);

void affiche_new_tab(entrainement** tab_entrainement_epreuve, const char* epreuve, int *nb_filtre);