#ifndef ATHLETES_H // FILENAME
#define ATHLETES_H

#include "structure.h"




// read all athletes from file to array
athlete** readAthletesFromFile(const char* nomFichier, int* nbAthletes);

// print all athlestes from array
void printArrayOfAthlete(athlete** tab_athletes, int nbAthletes);


// add new athlete to array
// return 1 if OK else 0
int addNewAthlete(athlete** tab_athletes, int* nbAthletes);

// rewrite all athletes from array to file
void writeArrayOfAthleteTOfile(const char* nomFichier, athlete** tab_athletes, int  nbAthletes);


int fichier_existe(const char *nom_fichier);


void creer_fichier_si_non_existant(const char *nom_fichier);

#endif