#ifndef ENTRAINEMENT_H // FILENAME
#define ENTRAINEMENT_H

#include "structure.h"

entrainement** lis_un_fichier_d_entrainement(const char* nomFichier, int* nb_entrainement );


void printArrayOfentrainement(entrainement** TAB_DATA, int nbEntrainement);


void writeArrayOftrainingTOfile(const char* nomFichier, entrainement** tab_entrainement, int  nbEntrainement);


void addNewEntrainement(entrainement** tab_entrainement, int* nbEntrainement);


#endif