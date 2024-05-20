#ifndef ENTRAINEMENT_H // FILENAME
#define ENTRAINEMENT_H

#include "structure.h"



entrainement** lis_un_fichier_d_entrainement(const char* nomFichier, int* nb_entrainement );


void printArrayOfentrainement(entrainement** TAB_DATA, int nbEntrainement);


void writeArrayOftrainingTOfile(const char* nomFichier, entrainement** tab_entrainement, int  nbEntrainement);


void addNewEntrainementSaisiUser(entrainement** tab_entrainement, int* nbEntrainement, char*epeuve);


// ecris tous les entrainement d'un athlete dans son fichier
void writeAllEntrainementTOfile(const char* nomAthlete, entrainement** tab_entrainement, int nbEntrainement);

// creation nouvel entrainement
// return pointeur dessus
entrainement* getNewEntrainement(date la_date, char* epreuve, performance perf, int position_relais);


// ajout du nouvel entrainement dans le tab de tous les entrainements
void addNewEntrainementDansTab(entrainement** tab_entrainement, int* nbEntrainement, entrainement* p_new_entrainement);


// ajout du nouvel entrainement dans le tab de tous les entrainements !
// 1. lit le fichier de l'athlete
// 2. ajout l'entrainement
// 3. reecris le fichier
void addNewEntrainementDansFichier(const char* nomAthlete, entrainement* p_new_entrainement);


#endif