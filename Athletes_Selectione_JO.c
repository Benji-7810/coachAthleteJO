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



// Fonction hypothétique pour lire les athlètes depuis un fichier
athlete** readAthletesFromFile(const char* fichierAthletes, int* nbAthletes);

// Fonction hypothétique pour lire les entraînements d'un athlète depuis un fichier
entrainement** lis_un_fichier_d_entrainement(const char* nomFichier, int* nbEntrainements);

// Fonction pour générer un tableau avec tous les entraînements correspondant à une épreuve donnée pour chaque athlète
entrainement** genererTableauEntrainements(const char* fichierAthletes, int* nbTotalEntrainements, const char* epreuve) {
    int nbAthletes;
    athlete** tabAthletes = readAthletesFromFile(fichierAthletes, &nbAthletes);
    if (nbAthletes == 0 || tabAthletes == NULL) {
        printf("Aucun athlète trouvé.\n");
        return NULL;
    }

    entrainement** tabEntrainements = malloc(MAX_ATHLETES * sizeof(entrainement*));
    if (tabEntrainements == NULL) {
        printf("Erreur lors de l'allocation mémoire pour le tableau d'entraînements.\n");
        return NULL;
    }

    int totalEntrainements = 0;

    for (int i = 0; i < nbAthletes; i++) {
        char nomFichierEntrainements[1000];
        sprintf(nomFichierEntrainements, "data/%s.csv", tabAthletes[i]->prenom_nom);
        int nbEntrainements;
        entrainement** entrainementsAthlete = lis_un_fichier_d_entrainement(nomFichierEntrainements, &nbEntrainements);

        for (int j = 0; j < nbEntrainements; j++) {
            if (strcmp(entrainementsAthlete[j]->lepreuve.nom, epreuve) == 0) {
                entrainement *nouvelEntrainement = malloc(sizeof(entrainement));
                if (nouvelEntrainement == NULL) {
                    continue; // En cas d'échec d'allocation
                }

                // Copie des informations dans la structure nouvelEntrainement, en utilisant le nom de l'athlète
                nouvelEntrainement->ladate = entrainementsAthlete[j]->ladate;
                strncpy(nouvelEntrainement->lepreuve.nom, tabAthletes[i]->prenom_nom, sizeof(nouvelEntrainement->lepreuve.nom) - 1);  // Utiliser le nom de l'athlète
                nouvelEntrainement->lepreuve.position_relais = entrainementsAthlete[j]->lepreuve.position_relais;
                nouvelEntrainement->laperf = entrainementsAthlete[j]->laperf;

                tabEntrainements[totalEntrainements++] = nouvelEntrainement;
            }
        }
        

        // Libérer la mémoire allouée pour les entraînements de cet athlète
        free(entrainementsAthlete);
    }

    *nbTotalEntrainements = totalEntrainements;
    return tabEntrainements;
}

void afficherEntrainements(entrainement** tabEntrainements, int nbTotalEntrainements) {
    if (tabEntrainements == NULL || nbTotalEntrainements == 0) {
        printf("Aucun entraînement à afficher.\n");
        return;
    }

    printf("Liste complète des entraînements filtrés :\n\n");
    for (int i = 0; i < nbTotalEntrainements; i++) {
        if (tabEntrainements[i] == NULL) continue; // Ignore les pointeurs NULL

        // Affichage de l'entraînement - l'information est supposée être en format de chaîne unique avec tous les détails
        printf("Athlète: %s, Date: %02d/%02d/%04d, Heure: %02d:%02d, Épreuve: %s, Performance: %.2f secondes\n\n",
               tabEntrainements[i]->lepreuve.nom, // Nom de l'athlète et autres détails
               tabEntrainements[i]->ladate.jour,
               tabEntrainements[i]->ladate.mois,
               tabEntrainements[i]->ladate.annee,
               tabEntrainements[i]->ladate.heure,
               tabEntrainements[i]->ladate.min,
               tabEntrainements[i]->lepreuve.nom,
               tabEntrainements[i]->laperf.perf);
    }
}





// Fonction de comparaison pour les performances (ordre croissant)
int comparePerformances(const void *a, const void *b) {
    const entrainement *entra1 = *(const entrainement **)a;
    const entrainement *entra2 = *(const entrainement **)b;
    if (entra1->laperf.perf > entra2->laperf.perf) return 1;
    if (entra1->laperf.perf < entra2->laperf.perf) return -1;
    return 0;
}

void trierEntrainementsParPerformance(entrainement **tabEntrainements, int nbTotalEntrainements) {
    qsort(tabEntrainements, nbTotalEntrainements, sizeof(entrainement *), comparePerformances);
}


void afficherEntrainementsTries(entrainement **tabEntrainements, int nbTotalEntrainements) {
    if (tabEntrainements == NULL || nbTotalEntrainements == 0) {
        printf("Aucun entraînement à afficher.\n");
        return;
    }

    // Trier les entrainements par performance (temps le plus court en premier)
    trierEntrainementsParPerformance(tabEntrainements, nbTotalEntrainements);

    printf("Liste complète des entraînements filtrés, triés du plus performant au moins performant :\n\n");
    for (int i = 0; i < nbTotalEntrainements; i++) {
        if (tabEntrainements[i] == NULL) continue; // Ignore les pointeurs NULL

        // Affichage de l'entraînement
        printf("Athlète: %s, Date: %02d/%02d/%04d, Heure: %02d:%02d, Épreuve: %s, Performance: %.2f secondes\n",
               tabEntrainements[i]->lepreuve.nom,
               tabEntrainements[i]->ladate.jour,
               tabEntrainements[i]->ladate.mois,
               tabEntrainements[i]->ladate.annee,
               tabEntrainements[i]->ladate.heure,
               tabEntrainements[i]->ladate.min,
               tabEntrainements[i]->lepreuve.nom,
               tabEntrainements[i]->laperf.perf);
    }
}



StatistiquesAthlete* calculerStatistiques(entrainement **tabEntrainements, int nbTotalEntrainements, int* nbAthletes) {
    StatistiquesAthlete *stats = malloc(nbTotalEntrainements * sizeof(StatistiquesAthlete));
    if (!stats) {
        printf("Erreur d'allocation mémoire.\n");
        return NULL;
    }

    int nbAthletesFound = 0;

    for (int i = 0; i < nbTotalEntrainements; i++) {
        if (tabEntrainements[i] == NULL) continue; // Ignore les pointeurs NULL
        
        bool found = false;
        for (int j = 0; j < nbAthletesFound; j++) {
            if (strcmp(stats[j].nom, tabEntrainements[i]->lepreuve.nom) == 0) {
                found = true;
                stats[j].somme_temps += tabEntrainements[i]->laperf.perf;
                stats[j].compteur++;
                if (tabEntrainements[i]->laperf.perf < stats[j].meilleur_temps) {
                    stats[j].meilleur_temps = tabEntrainements[i]->laperf.perf;
                }
                break;
            }
        }

        if (!found) {
            strcpy(stats[nbAthletesFound].nom, tabEntrainements[i]->lepreuve.nom);
            stats[nbAthletesFound].meilleur_temps = tabEntrainements[i]->laperf.perf;
            stats[nbAthletesFound].somme_temps = tabEntrainements[i]->laperf.perf;
            stats[nbAthletesFound].compteur = 1;
            nbAthletesFound++;
        }
    }

    for (int i = 0; i < nbAthletesFound; i++) {
        stats[i].moyenne_temps = stats[i].somme_temps / stats[i].compteur;
    }

    *nbAthletes = nbAthletesFound;
    return stats;
}


int comparerParMoyenne(const void *a, const void *b) {
    StatistiquesAthlete *athleteA = (StatistiquesAthlete *)a;
    StatistiquesAthlete *athleteB = (StatistiquesAthlete *)b;
    if (athleteA->moyenne_temps < athleteB->moyenne_temps) return -1;
    if (athleteA->moyenne_temps > athleteB->moyenne_temps) return 1;
    return 0;
}

int comparerParMeilleurTemps(const void *a, const void *b) {
    StatistiquesAthlete *athleteA = (StatistiquesAthlete *)a;
    StatistiquesAthlete *athleteB = (StatistiquesAthlete *)b;
    if (athleteA->meilleur_temps < athleteB->meilleur_temps) return -1;
    if (athleteA->meilleur_temps > athleteB->meilleur_temps) return 1;
    return 0;
}

void trierParMoyenne(StatistiquesAthlete *stats, int nbAthletes) {
    qsort(stats, nbAthletes, sizeof(StatistiquesAthlete), comparerParMoyenne);
}

void trierParMeilleurTemps(StatistiquesAthlete *stats, int nbAthletes) {
    qsort(stats, nbAthletes, sizeof(StatistiquesAthlete), comparerParMeilleurTemps);
}


void affichetab(StatistiquesAthlete *stats, int nbAthletes) {
    printf("Voici le tableau des statistiques des athlètes :\n");
    printf("%-20s %-10s %-10s %-10s %-10s\n", "Nom", "Somme", "Compteur", "Meilleur", "Moyenne");
    for (int i = 0; i < nbAthletes; i++) {
        printf("%-20s %-10.2f %-10d %-10.2f %-10.2f\n", 
               stats[i].nom, 
               stats[i].somme_temps, 
               stats[i].compteur, 
               stats[i].meilleur_temps, 
               stats[i].moyenne_temps);
    }
}

void afficherStatistiques(StatistiquesAthlete *stats, int nbAthletes) {
    if (stats == NULL || nbAthletes == 0) {
        printf("Aucune statistique à afficher.\n");
        return;
    }
    printf("Statistiques des athlètes :\n");
    int i =0;
  
        int nbr = demande_a_l_utilisateur_un_entier_sans_affichage("Vous voulez afficher les 3 meilleurs athletes par quel moyens \n1- Meilleur temps\n2- Moyenne des temps",1,2);
        if(nbr==1){
        trierParMeilleurTemps(stats,nbAthletes);
        printf("        Le meilleur athlète: %s avec pour meilleur temps : %.2f secondes\n", stats[0].nom, stats[0].meilleur_temps);
        printf("        Le deuxieme athlète: %s avec pour meilleur temps : %.2f secondes\n", stats[1].nom, stats[1].meilleur_temps);
        printf("        Le troisieme athlète: %s avec pour meilleur temps : %.2f secondes\n", stats[2].nom, stats[2].meilleur_temps);
    }
    else{
        trierParMoyenne(stats,nbAthletes);
        printf("        Le meilleur athlète: %s avec pour meilleur temps : %.2f secondes\n", stats[0].nom, stats[0].moyenne_temps);
        printf("        Le deuxieme athlète: %s avec pour meilleur temps : %.2f secondes\n", stats[1].nom, stats[1].moyenne_temps);
        printf("        Le troisieme athlète: %s avec pour moyenne : %.2f secondes\n", stats[2].nom, stats[2].moyenne_temps);

    }
    
    
}

