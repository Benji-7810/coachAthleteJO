#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrainement.h"
#include "structure.h"
#include "read_data_file.h"


void swap(entrainement** a, entrainement** b);


void trie_perf(entrainement** tab_entrainement, int nb_entrainement, char* epreuve);


void print_entrainements_trier(entrainement** tab_entrainement, int nb_entrainement, char* epreuve);

void affiche_pire_meilleur_temps(entrainement** tab_entrainement, int nb_entrainement);