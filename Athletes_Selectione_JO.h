
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "structure.h"
#include "athletes.h"
#include "entrainement.h"
#include "read_data_file.h"
#include "trie.h"



// Génère un tableau d'entraînements pour une épreuve spécifiée en extrayant les données des fichiers CSV des athlètes
entrainement** genererTableauEntrainements(const char* fichierAthletes, int* nbTotalEntrainements, const char* epreuve);



// Affiche les entraînements triés par performance
void afficherEntrainements(entrainement** tabEntrainements, int nbTotalEntrainements);



// Calcule les statistiques des athlètes à partir des entraînements donnés
StatistiquesAthlete* calculerStatistiques(entrainement **tabEntrainements, int nbTotalEntrainements, int* nbAthletes);



// Comparaison de deux athlètes par leur moyenne de temps
int comparerParMoyenne(const void *a, const void *b);



// Comparaison de deux athlètes par leur meilleur temps
int comparerParMeilleurTemps(const void *a, const void *b);



// Trie un tableau de statistiques d'athlètes par leur moyenne de temps
void trierParMoyenne(StatistiquesAthlete *stats, int nbAthletes);



// Trie un tableau de statistiques d'athlètes par leur meilleur temps
void trierParMeilleurTemps(StatistiquesAthlete *stats, int nbAthletes);



// Affiche les statistiques des athlètes en fonction du choix de l'utilisateur
void afficherStatistiques(StatistiquesAthlete *stats, int nbAthletes);