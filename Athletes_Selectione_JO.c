#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "structure.h"
#include "athletes.h"
#include "entrainement.h"
#include "read_data_file.h"
#include "trie.h"



#define MAX_ATHLETES 100
#define FILE_ATHLETES "data/athletes.csv"

#define NB_ATHLETES_PAR_GROUPE 4
#define NB_MEILLEURS_GROUPES 3




// Génère un tableau d'entraînements pour une épreuve spécifiée en extrayant les données des fichiers CSV des athlètes
entrainement** genererTableauEntrainements(const char* fichierAthletes, int* nbTotalEntrainements, const char* epreuve) {
    
    // Lecture des athlètes depuis le fichier CSV
    int nbAthletes;
    athlete** tabAthletes = readAthletesFromFile(fichierAthletes, &nbAthletes);
    if (nbAthletes == 0 || tabAthletes == NULL) {
        printf("Aucun athlète trouvé.\n");
        return NULL;
    }

    // Allocation de mémoire pour le tableau d'entraînements
    entrainement** tabEntrainements = malloc(MAX_ATHLETES * sizeof(entrainement*));
    
    if (tabEntrainements == NULL) {
        printf("Erreur lors de l'allocation mémoire pour le tableau d'entraînements.\n");
        return NULL;
    }

    int totalEntrainements = 0; // Compteur pour le nombre total d'entraînements

    // Parcours de tous les athlètes
    for (int i = 0; i < nbAthletes; i++) {

        // Construction du nom du fichier d'entraînements de l'athlète
        char nomFichierEntrainements[1000];
        sprintf(nomFichierEntrainements, "data/%s.csv", tabAthletes[i]->prenom_nom);
        
        // Lecture des entraînements à partir du fichier CSV de l'athlète
        int nbEntrainements;
        entrainement** entrainementsAthlete = lis_un_fichier_d_entrainement(nomFichierEntrainements, &nbEntrainements);

        // Parcours de tous les entraînements de l'athlète
        for (int j = 0; j < nbEntrainements; j++) {

            // Vérification si l'entraînement correspond à l'épreuve spécifiée
            if (strcmp(entrainementsAthlete[j]->lepreuve.nom, epreuve) == 0) {
                
                // Allocation de mémoire pour un nouvel entraînement
                entrainement *nouvelEntrainement = malloc(sizeof(entrainement));
                
                if (nouvelEntrainement == NULL) {
                    continue; // En cas d'échec d'allocation, passer à l'entraînement suivant
                }

                // Copie des informations dans la structure nouvelEntrainement
                nouvelEntrainement->ladate = entrainementsAthlete[j]->ladate;
                strcpy(nouvelEntrainement->lepreuve.nom, entrainementsAthlete[j]->lepreuve.nom);
                nouvelEntrainement->lepreuve.position_relais = entrainementsAthlete[j]->lepreuve.position_relais;
                nouvelEntrainement->laperf = entrainementsAthlete[j]->laperf;
                strcpy(nouvelEntrainement->nom, tabAthletes[i]->prenom_nom);

                // Ajout du nouvel entraînement au tableau d'entraînements
                tabEntrainements[totalEntrainements++] = nouvelEntrainement;
            }
        }

        // Libération de la mémoire allouée pour les entraînements de cet athlète
        free(entrainementsAthlete);
    }

    // Mise à jour du nombre total d'entraînements et retour du tableau d'entraînements
    *nbTotalEntrainements = totalEntrainements;
    return tabEntrainements;
}



// Affiche les entraînements triés par performance
void afficherEntrainements(entrainement** tabEntrainements, int nbTotalEntrainements) {
    
    char epreuve[20]; // Variable pour stocker le nom de l'épreuve

    // Vérifie s'il y a des entraînements à afficher
    if (tabEntrainements == NULL || nbTotalEntrainements == 0) {
        printf("Aucun entraînement à afficher.\n");
        return;
    }
    
    // Tri des entraînements par performance
    trie_entrainement_par_perf(tabEntrainements, nbTotalEntrainements);

    // Parcours de tous les entraînements pour les afficher
    for (int i = 0; i < nbTotalEntrainements; i++) {
        if (tabEntrainements[i] == NULL) continue; // Ignore les pointeurs NULL
        
        // Vérifie s'il s'agit d'un relais et marque sa position dans le relais ex( relais(1) )
        if (strcmp(tabEntrainements[i]->lepreuve.nom, "relais") == 0) {
            sprintf(epreuve, "relais(%d)", tabEntrainements[i]->lepreuve.position_relais);
        } else {
            strcpy(epreuve, tabEntrainements[i]->lepreuve.nom);
        }
        
        // Affiche les détails de l'entraînement
        printf("Date: %s, Performance: %.2f sec, Épreuve: %s, Athlète: %s\n",
               get_date_printable(tabEntrainements[i]->ladate),
               tabEntrainements[i]->laperf.perf,
               epreuve,
               tabEntrainements[i]->nom);
    }
}



// Calcule les statistiques des athlètes à partir des entraînements donnés
StatistiquesAthlete* calculerStatistiques(entrainement** tabEntrainements, int nbTotalEntrainements, int* nbAthletes) {
    
    // Allocation de mémoire pour les statistiques des athlètes
    StatistiquesAthlete *stats = malloc(nbTotalEntrainements * sizeof(StatistiquesAthlete));
    if (!stats) {
        printf("Erreur d'allocation mémoire.\n");
        return NULL;
    }

    int nbAthletesFound = 0; // Nombre d'athlètes trouvés

    // Parcours de tous les entraînements pour calculer les statistiques des athlètes
    for (int i = 0; i < nbTotalEntrainements; i++) {
        if (tabEntrainements[i] == NULL) continue; // Ignore les pointeurs NULL
        
        bool found = false;

        // Recherche de l'athlète dans les statistiques déjà calculées
        for (int j = 0; j < nbAthletesFound; j++) {
            
            if (strcmp(stats[j].nom, tabEntrainements[i]->nom) == 0) { // Utilisation du nom de l'athlète
                found = true;
                
                // Mise à jour des statistiques de l'athlète
                stats[j].somme_temps += tabEntrainements[i]->laperf.perf;
                stats[j].compteur++;
                if (tabEntrainements[i]->laperf.perf < stats[j].meilleur_temps) {
                    stats[j].meilleur_temps = tabEntrainements[i]->laperf.perf;
                }
                break;
            }
        }

        // Si l'athlète n'a pas été trouvé dans les statistiques précédentes, l'ajouter
        if (!found) {
            // Ajout des statistiques pour un nouvel athlète
            strcpy(stats[nbAthletesFound].nom, tabEntrainements[i]->nom); // Utilisation du nom de l'athlète
            stats[nbAthletesFound].meilleur_temps = tabEntrainements[i]->laperf.perf;
            stats[nbAthletesFound].somme_temps = tabEntrainements[i]->laperf.perf;
            stats[nbAthletesFound].compteur = 1;
            nbAthletesFound++;
        }
    }

    // Calcul de la moyenne des temps pour chaque athlète
    for (int i = 0; i < nbAthletesFound; i++) {
        stats[i].moyenne_temps = stats[i].somme_temps / stats[i].compteur;
    }

    // Mise à jour du nombre d'athlètes trouvés et retour des statistiques
    *nbAthletes = nbAthletesFound;
    return stats;
}



// Comparaison de deux athlètes par leur moyenne de temps
int comparerParMoyenne(const void *a, const void *b) {

    // Conversion des pointeurs génériques en pointeurs vers StatistiquesAthlete
    StatistiquesAthlete *athleteA = (StatistiquesAthlete *)a;
    StatistiquesAthlete *athleteB = (StatistiquesAthlete *)b;
    
    // Comparaison des moyennes de temps des athlètes
    if (athleteA->moyenne_temps < athleteB->moyenne_temps) return -1;
    if (athleteA->moyenne_temps > athleteB->moyenne_temps) return 1;
    
    return 0; // Les moyennes de temps sont égales
}



// Comparaison de deux athlètes par leur meilleur temps
int comparerParMeilleurTemps(const void *a, const void *b) {

    // Conversion des pointeurs génériques en pointeurs vers StatistiquesAthlete
    StatistiquesAthlete *athleteA = (StatistiquesAthlete *)a;
    StatistiquesAthlete *athleteB = (StatistiquesAthlete *)b;
    
    // Comparaison des meilleurs temps des athlètes
    if (athleteA->meilleur_temps < athleteB->meilleur_temps) return -1;
    if (athleteA->meilleur_temps > athleteB->meilleur_temps) return 1;

    return 0; // Les meilleurs temps sont égaux
}



// Trie un tableau de statistiques d'athlètes par leur moyenne de temps
void trierParMoyenne(StatistiquesAthlete *stats, int nbAthletes) {

    // Utilisation de la fonction qsort de la bibliothèque pour trier le tableau
    qsort(stats, nbAthletes, sizeof(StatistiquesAthlete), comparerParMoyenne);
}



// Trie un tableau de statistiques d'athlètes par leur meilleur temps
void trierParMeilleurTemps(StatistiquesAthlete *stats, int nbAthletes) {

    // Utilisation de la fonction qsort de la bibliothèque pour trier le tableau
    qsort(stats, nbAthletes, sizeof(StatistiquesAthlete), comparerParMeilleurTemps);
}



// Affiche les statistiques des athlètes en fonction du choix de l'utilisateur
// choix : 1 : meilleur temps,       2:moyenne des temps
void afficherStatistiques(StatistiquesAthlete *stats, int nbAthletes, int choix) {
    
    // Vérifie s'il y a des statistiques à afficher
    if (stats == NULL || nbAthletes == 0) {
        printf("Aucune statistique à afficher.\n");
        return;
    }
    
    
    // Trie les statistiques en fonction du choix de l'utilisateur
    if (choix == 1) {
        
        trierParMeilleurTemps(stats, nbAthletes);
        
        // Affiche les 3 meilleurs athlètes par meilleur temps
        printf("        Le meilleur athlète  : %20s   avec pour meilleur temps  : %s\n", stats[0].nom, get_nb_sec_printable(stats[0].meilleur_temps));
        printf("        Le deuxième athlète  : %20s   avec pour meilleur temps  : %s\n", stats[1].nom, get_nb_sec_printable(stats[1].meilleur_temps));
        printf("        Le troisième athlète : %20s   avec pour meilleur temps  : %s\n", stats[2].nom, get_nb_sec_printable(stats[2].meilleur_temps));
    } else {
        
        trierParMoyenne(stats, nbAthletes);
        
        // Affiche les 3 meilleurs athlètes par moyenne des temps
        printf("        Le meilleur athlète  : %20s   avec pour moyenne temps  : %s\n", stats[0].nom, get_nb_sec_printable(stats[0].moyenne_temps));
        printf("        Le deuxième athlète  : %20s   avec pour moyenne temps  : %s\n", stats[1].nom, get_nb_sec_printable(stats[1].moyenne_temps));
        printf("        Le troisième athlète : %20s   avec pour moyenne temps  : %s\n", stats[2].nom, get_nb_sec_printable(stats[2].moyenne_temps));
    }
}

