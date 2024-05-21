

#include "structure.h"


int displayMenu(char tab_option[]);

int demande_a_l_utilisateur_un_entier(char* question, int min, int max);

// ne pas utiliser : bug si un espace est saisi
void demande_a_l_utilisateur_une_chaine_de_caractere_ne_pas_utiliser(char* question, char* p_txt, int longueur_min, int longueur_max);
 
void demande_a_l_utilisateur_une_chaine_de_caractere_fgets(char* question, char* p_txt, int taille_max);

int demande_a_l_utilisateur_un_entier_sans_affichage(char* question, int min, int max);

int displayMenuGeneric(char * tab_option[], int nb_option);
int numero_jour( date d);
int nombre_jours(date d1, date d2);

int displayMenuPrincipal();
int displayMenuStatistiquesAthlete();

// format: JJ/MM/AAAA HH:MM
void print_date(date ladate);

// return format: JJ/MM/AAAA HH:MM
char* get_date_printable(date ladate);

void transforme_en_date(int jour, int mois, int annee, int heure, int min, date* ladate);

void demande_a_l_utilisateur_une_date( date*date_relais);

void demande_a_l_utilisateur_une_perf(performance* laperf);

void demande_a_l_utilisateur_une_perf_marathon(performance* laperf);

void transforme_en_perf(double perf, performance* laperf);

char* get_perf_printable(performance laperf);

void displayMenuChoixUneEpreuveATaper(char* epreuve);