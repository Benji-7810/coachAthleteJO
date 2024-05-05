#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"
#include "athletes.h"



int main() {
    int nbAthletes = 0;

    // load athletes from file
    athlete* tab_athletes = lireAthletesDepuisFichier("data/athletes.csv", &nbAthletes);

    // print all athletes
    printArrayOfAthlete(tab_athletes, nbAthletes);

    // free memory
    free(tab_athletes);

    return 0;
}
