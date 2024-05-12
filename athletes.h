#ifndef ATHLETES_H // FILENAME
#define ATHLETES_H

#include "structure.h"




// read all athletes from file to array
athlete** readAthletesFromFile(const char* nomFichier, int* nbAthletes);

// print all athlestes from array
void printArrayOfAthlete(athlete** tab_athletes, int nbAthletes);


// add new athlete to array
void addNewAthlete(athlete** tab_athletes, int* nbAthletes);


// rewrite all athletes from array to file
void writeArrayOfAthleteTOfile(const char* nomFichier, athlete** tab_athletes, int  nbAthletes);



#endif