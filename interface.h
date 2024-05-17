

#include "structure.h"


int displayMenu(char tab_option[]);

int demande_a_l_utilisateur_un_entier(char* question, int min, int max);

// ne pas utiliser : bug si un espace est saisi
void demande_a_l_utilisateur_une_chaine_de_caractere_ne_pas_utiliser(char* question, char* p_txt, int longueur_min, int longueur_max);
 
void demande_a_l_utilisateur_une_chaine_de_caractere_fgets(char* question, char* p_txt, int taille_max);

int demande_a_l_utilisateur_un_entier_sans_affichage(char* question, int min, int max);

int displayMenuGeneric(char * tab_option[], int nb_option);


int displayMenuPrincipal();


// format: JJ/MM/AAAA HH:MM
void print_date(date ladate);

// return format: JJ/MM/AAAA HH:MM
char* get_date_printable(date ladate);