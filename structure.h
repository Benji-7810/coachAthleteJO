#ifndef STRUCTURES_H  // FILENAME
#define STRUCTURES_H




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



typedef struct {
    char nom[100];        // Nom de l'athlète
    double meilleur_temps; // Meilleur temps réalisé
    double moyenne_temps;  // Moyenne des temps réalisés
    int compteur;          // Nombre d'entrainements pour cet athlète
    double somme_temps;    // Somme des temps pour calculer la moyenne
} StatistiquesAthlete;



#include "interface.h"

#endif



