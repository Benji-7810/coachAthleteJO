
#ifndef INTERFACE_H  // FILENAME
#define INTERFACE_H

#include "interface.h"

#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int demande_a_l_utilisateur_un_entier(char* question, int min, int max) {
    int nombre;
    do{
        printf("%s  (entre %d et %d) : ", question, min ,max);
        scanf("%d", &nombre);
    }while(nombre<min || max<nombre);


    return nombre;
}

int demande_a_l_utilisateur_un_entier_sans_affichage(char* question, int min, int max) {
    int nombre;
    do{
        printf("%s\n ", question);
        scanf("%d", &nombre);
    }while(nombre<min || max<nombre);


    return nombre;
}

// ne pas utiliser : bug si un espace est saisi
void demande_a_l_utilisateur_une_chaine_de_caractere_ne_pas_utiliser(char* question, char* p_txt, int longueur_min, int longueur_max) {
    do{
         printf("%s (taille min %d, taille max %d)", question, longueur_min, longueur_max);
        scanf("%s", p_txt);
    } while( strlen(p_txt)<longueur_min || longueur_max<strlen(p_txt));
}



void demande_a_l_utilisateur_une_chaine_de_caractere_fgets(char* question, char* p_txt, int taille_max)
{
    printf("\n%s", question);
    
    // 2x pour eviter le boucle infinie...
    fgets(p_txt, taille_max-1, stdin);
    fgets(p_txt, taille_max-1, stdin);

    int length = (int)strlen(p_txt);
    p_txt[length-1] = '\0';


}


// en entrée : char* tab_option[], int nb_option
// return    : l'indice +1 choisi par l'utilisateur												 
												   
int displayMenuGeneric(char* tab_option[], int nb_option){

    //printf("print displayMenuGeneric %d\n", nb_option);  
    for(int i = 1 ; i<=nb_option ; i++){

        printf("%d : %s\n", i, tab_option[i-1]);  
      

    }
    return demande_a_l_utilisateur_un_entier("\nquel choix veux tu choisir ?", 1, nb_option);

    
}
    



int displayMenuPrincipal(){

    int nb_option=5;

    char *tab[] = { 
        "ajouter un entrainement",
        "consulter les statistiques des athletes",
        "afficher la liste des athletes",
        "ajouter un athlete",
        "QUITTER"
    };
	
    
    return displayMenuGeneric(tab, nb_option);
}


int displayMenuStatistiquesAthlete(){

    int nb_option=5;

    char *tab[] = { 
        "consulter les entrainements d'un athlete par date",
        "consulter les entrainements d'un athlete par epreuve",
        "performances clés d’un athlète",
        "Qui envoyer au JO",
        "Progression de l’athlète",
        "RETOUR"
    };
	
    
    return displayMenuGeneric(tab, nb_option);
}


int displayMenuChoixUneEpreuve(){

    int nb_option=5;

    char *tab[] = { 
        "100m",
        "400m",
        "5000m"
    };											  
		   
	  
    
    return displayMenuGeneric(tab, nb_option);
}

void displayMenuChoixUneEpreuveATaper(char* epreuve)
{
    do {
        printf("\nEntre le type d'épreuve (ex 100m / 400m / 5000m / marathon / relais / 'retour'): ");
        scanf("%s", epreuve);
    } while (strcmp(epreuve, "100m") != 0 
    && strcmp(epreuve, "400m") != 0 
    && strcmp(epreuve, "5000m") != 0 
    && strcmp(epreuve, "marathon") != 0 
    && strcmp(epreuve, "relais") != 0
    && strcmp(epreuve, "retour") != 0);

}											  
									
									 
																			 
// format: JJ/MM/AAAA HH:MM
// void print_date(date ladate)
// {
//     printf("%02d/%02d/%04d %02d:%02d", 
//     ladate.jour, ladate.mois, ladate.annee, ladate.heure, ladate.min); 
// }


// return format: JJ/MM/AAAA HH:MM
char* get_date_printable(date ladate)
{
    char* date_printable = (char*) malloc(sizeof(char) * (16+1));

    sprintf(date_printable, "%02d/%02d/%04d %02d:%02d", 
    ladate.jour, ladate.mois, ladate.annee, ladate.heure, ladate.min); 

    return date_printable;
}

int numero_jour( date d){
    int m= (d.mois+9)%12;
    int a= d.annee-(m>=10);
     return 1461*a/4-a/100+a/100+(m*306+5)/10+d.jour;
			  
			  
			  
}
// return format: 20'30''
/*
'        9.00'
'       12.32'
'    1m 02.00'
'1h 21m 02.00'

*/ 
char* get_perf_printable(performance laperf)
{
    // for debug
    //printf("\nperf_printable: %lf\n", laperf.perf);


    char* perf_printable = (char*) malloc(sizeof(char) * (40));

    double nb_sec = laperf.perf;
    
    int nb_min    = 0;
    char str_min[20];

    int    nb_heu = 0;
    char str_heu[20];


    // > 1h
    if (nb_sec > 3600){
        nb_heu=nb_sec/3600;
        sprintf(str_heu, "%2dh", nb_heu);
        nb_sec = nb_sec - (nb_heu*3600);
    } else {
        strcpy(str_heu, "   ");
    }

    // > 1m
    if (nb_sec > 60){
        nb_min=nb_sec/60;
        sprintf(str_min, "%2dm", nb_min);
        nb_sec = nb_sec - (nb_min*60);
    } else {
        strcpy(str_min, "   ");
    }


    sprintf(perf_printable, "%s %s %5.2f",
        str_heu, 
        str_min,
        nb_sec
    ); 

    return perf_printable;
}



void transforme_en_date(int jour, int mois, int annee, int heure, int min, date* ladate)
{
    ladate->jour  = jour;
    ladate->mois  = mois;
    ladate->annee = annee;
    ladate->heure = heure;
    ladate->min   = min;
}

// void transforme_en_perf(double perf, performance* laperf)
// {
//     laperf->perf = perf;
// }


void demande_a_l_utilisateur_une_date(date* date_relais) {
    date_relais->jour  = demande_a_l_utilisateur_un_entier("\nrentre le jour", 1, 31);
    date_relais->mois  = demande_a_l_utilisateur_un_entier("rentre le mois", 1, 12);
    date_relais->annee = demande_a_l_utilisateur_un_entier("rentre l'année", 2000, 2024);
    date_relais->heure = demande_a_l_utilisateur_un_entier("rentre les heures", 0, 24);
    date_relais->min   = demande_a_l_utilisateur_un_entier("rentre les minutes", 0, 60);
}


void demande_a_l_utilisateur_une_perf(performance* laperf) {
    
    int min;
    float seconde;

    printf("\ntemps de le perf:");

    do{
        printf("\nmin (ex: '0', '1', '13', '12') ? ");
        scanf("%d",&min);
    }while(min<0 || min>59);

    do{
        printf("\nsec (ex: '9.32', '12.00' ? ");
        scanf("%f", &(seconde)); // On lit un double au lieu d'un entier  
    }while(seconde<0 || seconde>59);

    laperf->perf =(min*60)+seconde;
    // for debug
    // printf("\ndemande_a_l_utilisateur_une_perf : OK\n");
}

void demande_a_l_utilisateur_une_perf_marathon(performance* laperf) {
    int min ;
    float seconde;
    int heure;

    printf("\ntemps de le perf:");

    do{
        printf("\nheure (ex: '1', '2' ? )");
        scanf("%d",&heure);
    }while(heure<0);


    do{
        printf("\nmin (ex: '0', '1', '13', '12') ? ");
        scanf("%d",&min);
    }while(min<0 || min>59);

    do{
        printf("\nsec (ex: '9.32', '12.00' ? ");
        scanf("%f", &(seconde)); // On lit un double au lieu d'un entier  
    }while(seconde<0 || seconde>59);


    laperf->perf = (heure*3600) + (min*60) + seconde;

    // for debug
    // printf("\ndemande_a_l_utilisateur_une_perf : OK\n");
}
											
 
															   

								
	
					  
					 

					  
					 


		   
					   
						   
										 
										
			
							   
	 

		   
					 
						 
										 
									  
			
							   
	 


										  
				 
				
			  
	   

						  


int nombre_jours(date d1, date d2){
    return numero_jour(d1)-numero_jour(d2);
																						
 
						 
						 
						  
						  
						
}

														 
 
						
 


														  
																				   
																				   
																						  
																					   
																					  
 


															
													
																		
 

#endif