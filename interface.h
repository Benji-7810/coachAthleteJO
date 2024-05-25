

#include "structure.h"

// Différents menus traversées

//Menu Principal
int displayMenu(char tab_option[]);
int displayMenuPrincipal();

//Menu Stat Athlete
int displayMenuStatistiquesAthlete();

//Menu d'epreuve
void displayMenuChoixUneEpreuveATaper(char* epreuve);

//Aide à l'affichage des différents menus
int displayMenuGeneric(char * tab_option[], int nb_option);



//Fonction pratique souvent demandées dans le programme

//Demande un entier
int demande_a_l_utilisateur_un_entier(char* question, int min, int max);


//Demande une chaine de caractère
void demande_a_l_utilisateur_une_chaine_de_caractere_ne_pas_utiliser(char* question, char* p_txt, int longueur_min, int longueur_max);

//Demande une chaine de caractère(fichier)
void demande_a_l_utilisateur_une_chaine_de_caractere_fgets(char* question, char* p_txt, int taille_max);

//Demande un entier (sans l'afficher)
int demande_a_l_utilisateur_un_entier_sans_affichage(char* question, int min, int max);




//Permet de verifier si une date entrée est valide
int numero_jour( date d);

//Nombre de jour entre deux date
int nombre_jours(date d1, date d2);


//Affiche une date
char* get_date_printable(date ladate);
void transforme_en_date(int jour, int mois, int annee, int heure, int min, date* ladate);

//Demande d'une date(précisément pour un jour de relais)
void demande_a_l_utilisateur_une_date( date*date_relais);

//Deamnde des perfs
void demande_a_l_utilisateur_une_perf(performance* laperf);

//Demande des perfs(spécial marathon)
void demande_a_l_utilisateur_une_perf_marathon(performance* laperf);

//Affiche les perf
char* get_perf_printable(performance laperf);
char* get_nb_sec_printable(double nb_sec);
