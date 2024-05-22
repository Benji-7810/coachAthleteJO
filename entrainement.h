#ifndef ENTRAINEMENT_H // FILENAME
#define ENTRAINEMENT_H

#include "structure.h"


//Lecture d'un entraiement
entrainement** lis_un_fichier_d_entrainement(const char* nomFichier, int* nb_entrainement );

//Affiche le tableau des entrainement
void printArrayOfentrainement(entrainement** TAB_DATA, int nbEntrainement);

//Affiche le tableau d'un entrainement
void print1entrainement(entrainement* p_entrainement, int i);

//Ajout de l'entrainement dans le fichier
void writeArrayOftrainingTOfile(const char* nomFichier, entrainement** tab_entrainement, int  nbEntrainement);

//Ajouter un nouvel entrainement
void addNewEntrainementSaisiUser(entrainement** tab_entrainement, int* nbEntrainement, char*epeuve);


// Creation nouvel entrainement
entrainement* getNewEntrainement(date la_date, char* epreuve, performance perf, int position_relais);


// Ajout du nouvel entrainement dans le tab de tous les entrainements ainsi que dans le fichier
void addNewEntrainementDansTab(entrainement** tab_entrainement, int* nbEntrainement, entrainement* p_new_entrainement);
void addNewEntrainementDansFichier(const char* nomAthlete, entrainement* p_new_entrainement);



#endif