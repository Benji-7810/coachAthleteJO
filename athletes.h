#ifndef ATHLETES_H // FILENAME
#define ATHLETES_H

#include "structure.h"




int nbLinesOK(const char* nomFichier);

athlete* lireAthletesDepuisFichier(const char* nomFichier, int* nbAthletes);

void printArrayOfAthlete(athlete* tab_athletes, int nbAthletes);





#endif