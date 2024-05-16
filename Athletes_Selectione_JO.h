
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "structure.h"
#include "athletes.h"
#include "entrainement.h"
#include "read_data_file.h"
#include "trie.h"




void afficherEntrainements(entrainement** tabEntrainements, int nbTotalEntrainements);

//entrainement** genererTableauEntrainements(const char* fichierAthletes, int* nbTotalEntrainements, const char* epreuve);

entrainement** genererTableauEntrainements(const char* fichierAthletes, int* nbTotalEntrainements, const char* epreuve);


// Fonction hypothétique pour lire les athlètes depuis un fichier
athlete** readAthletesFromFile(const char* fichierAthletes, int* nbAthletes);

// Fonction hypothétique pour lire les entraînements d'un athlète depuis un fichier
entrainement** lis_un_fichier_d_entrainement(const char* nomFichier, int* nbEntrainements);

void trierEntrainementsParPerformance(entrainement **tabEntrainements, int nbTotalEntrainements);

int comparePerformances(const void *a, const void *b) ;

void afficherEntrainementsTries(entrainement **tabEntrainements, int nbTotalEntrainements);

void afficherStatistiques(StatistiquesAthlete *stats, int nbAthletes);

StatistiquesAthlete* calculerStatistiques(entrainement **tabEntrainements, int nbTotalEntrainements, int* nbAthletes);

void affichetab(StatistiquesAthlete *stats, int nbAthletes);

int comparerParMoyenne(const void *a, const void *b);

int comparerParMeilleurTemps(const void *a, const void *b);

void trierParMoyenne(StatistiquesAthlete *stats, int nbAthletes);


void trierParMeilleurTemps(StatistiquesAthlete *stats, int nbAthletes);