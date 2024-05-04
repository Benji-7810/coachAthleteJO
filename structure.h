
// athlete
typedef struct{
    char prenom_nom[100]; // ex: "Usain Bolt"
} athlete;



// date
typedef struct{
    int annee;
    int mois;
    int jour;
    int heure;
    int min;
} date;


// epreuve
typedef struct{

    char nom[100]; // ex: "100m", "400m", "5000m", "marathon", "relais"
    
}epreuve;



// performance
typedef struct{

    float laperf; // nombre de seconde : ex: "15.06"

} performance;



// entrainement
typedef struct{
    date ladate;
    epreuve lepreuve; 
    performance laperf;
} entrainement;







