#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "read_data_file.h"


void check_error(FILE * file){
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
}


// return the number of lines with at least 1 character
int nbLinesNotEmpty(const char* nomFichier) {
    
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible de lire le fichier: '%s'", nomFichier);
        exit(1);
    }

    int i = 1;
    int nbLignesOK = 0;
    char ligne[MAX_LINE_LENGTH];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        
        // Supprimer le saut de ligne à la fin de la ligne si présent
        size_t longueur = strlen(ligne);
        if (PRINT_DEBUG)
            printf("\nnbLinesNotEmpty() longueur ligne %d: %d", i, (int)longueur);

        if (longueur > 0 && ligne[longueur - 1] == '\n') {
            ligne[longueur - 1] = '\0';
        }

        // Ignorer les lignes vides
        if (strlen(ligne) > 2) {
            nbLignesOK++;
            
            if (PRINT_DEBUG)
                printf(" OK nbLignesOK %d", nbLignesOK);
        }

        i++;
    }

    fclose(fichier);

    return nbLignesOK;
}



// read a "data files" and return an array of lines like this
// separator example : ";"
/*
a;bbb;cccccccccccc                tab_lines[0][0] : a
ddd                               tab_lines[0][1] : bbb   
e;s;                  ==>         tab_lines[0][2] : cccccccccccc      
zzzz                              tab_lines[0][3] : NULL

                                  tab_lines[1][0] : ddd
                                  tab_lines[1][1] : NULL
                                  
                                  tab_lines[2][0] : e
                                  tab_lines[2][1] : s
                                  tab_lines[2][2] : NULL
                                  
                                  tab_lines[3][0] : zzzz
                                  tab_lines[3][1] : NULL
*/
char*** readDataFile(const char* nomFichier, const char* separator, int* nbLines)
{
    *nbLines = nbLinesNotEmpty(nomFichier);

    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible de lire le fichier: '%s'", nomFichier);
        exit(1);
    }


    char*** tableauFinal = malloc ((*nbLines) * NB_MAX_DATA_BY_LINE * sizeof(char*)) ;
    

    if (tableauFinal == NULL) {
        printf("Allocation memoire KO");
        exit(1);
    }

    // read line by line
    char ligne[MAX_LINE_LENGTH];
    int num_ligne = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {

        // for debug
        //printf("\nLigne: '%s'\n", ligne);

        // for debug
        //printf("\nDernier charactere: '%c' '%x'\n", ligne[longueur - 1], ligne[longueur - 1] );


        // Supprimer le saut de ligne à la fin de la ligne si présent
        unsigned short longueur = strlen(ligne);
        int bool_saut_de_ligne;

        int nb_de_caractere_de_fin_de_ligne = 1; // linux
        if (ligne[longueur - 2] == '\r') {
            nb_de_caractere_de_fin_de_ligne = 2; // windows
            //printf("\n rrrrrrrrr -2");
        }


        if (longueur > 0 && ligne[longueur - 1] == '\n')
        {
            ligne[longueur - nb_de_caractere_de_fin_de_ligne] = '\0';
            bool_saut_de_ligne = 1;
        } else {
            bool_saut_de_ligne = 0;
            longueur++;
        }


        // Ignorer les lignes vides
        if (strlen(ligne) == 0)
            continue;


        tableauFinal[num_ligne] = (char**) malloc (NB_MAX_DATA_BY_LINE * sizeof(char*)) ;


        // read line charracter by character
        char c;
        int lg_data           = 0;
        int indice_debut_data = 0;
        int indice_fin_data   = 0;
        int num_data          = 0;
        
        for (int j=0 ; j<longueur ; j++)
        {
            c = ligne[j];
            if (c == (*separator) || j == (longueur-1)) {
                
                indice_fin_data = j-1; // just defore separator
                lg_data = indice_fin_data - indice_debut_data + 1; // length of data

                if (lg_data > 0)
                {

                    // alloc char for data
                    tableauFinal[num_ligne][num_data] = (char*) malloc((lg_data+1) * sizeof(char));


                    // copy data character by character
                    int ii = 0;
                    for (int k = indice_debut_data; k <= indice_fin_data ; k++ )
                    {
                        // for debug
                        // printf("\n%c", ligne[k]);
                        
                        tableauFinal[num_ligne][num_data][ii] = ligne[k];
                        ii++;
                    }
                    
                    // for debug
                    // printf("\nj, (longueur-1) %d %d", j, (longueur-1));

                    if (bool_saut_de_ligne) {
                        // si dernier caracteres de la case
                        if (j == (longueur-1)) {
                            //if (PRINT_DEBUG)
                                //printf("\nii");

                            //printf("\n bool_saut_de_ligne");
                            tableauFinal[num_ligne][num_data][ii] = '\0';
                        } else {
                            //if (PRINT_DEBUG)
                                //printf("\nii+1");
                            
                            tableauFinal[num_ligne][num_data][ii+1] = '\0';
                        }

                    } else {

                        //for debug
                        //printf("\n !bool_saut_de_ligne");

                        tableauFinal[num_ligne][num_data][ii+2] = '\0';
                    }
                    
                    
                    
                    //printf("\ndata=>%s", tableauFinal[num_ligne][num_data]);


                    // start new data
                    indice_debut_data = j+1; // just after separator
                    indice_fin_data   = j+1; // temporary
                    num_data++;
                } 

            } 

        } // end current line
        
        tableauFinal[num_ligne][num_data] = NULL;

        num_ligne++;

    } // fin while

    fclose(fichier);

    return tableauFinal;
}



// print an array of "data Lines"
void printDataLines(char*** tab_lines, int nbLines)
{
    printf("\n\nDebut printDataLines(): Nombre de lignes : %d", nbLines);

    int j;
    for (int i = 0 ; i < nbLines; i++) {

        printf("\ni: %d / %d", i, nbLines);

        j = 0;
        while (tab_lines[i][j] != NULL) {
            
            printf("\ntab[%d][%d] : '%s'", i, j, tab_lines[i][j]);

            j++;
        }
        printf("\ntab[%d][%d] : NULL", i, j);

    }

    printf("\nfin printDataLines()\n");
}

