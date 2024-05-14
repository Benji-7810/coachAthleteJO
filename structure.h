#ifndef STRUCTURES_H  // FILENAME
#define STRUCTURES_H

#include "interface.h"


// athlete
typedef struct{
    char prenom_nom[100]; // ex: "Usain Bolt"
} athlete;



// date
typedef struct{
    int jour;
    int mois;
    int annee;
    int heure;
    int min;
   
} date;


// epreuve
typedef struct{
    char nom[100]; // ex: "100m", "400m", "5000m", "marathon", "relais"
    int position_relais;
}epreuve;



// performance
typedef struct{
    double  perf; // nombre de seconde : ex: "15.06"
} performance;



// entrainement
typedef struct{
    date ladate;
    epreuve lepreuve; 
    performance laperf;
} entrainement;



#endif



