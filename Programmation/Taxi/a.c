#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <float.h>

typedef struct Point
{
    double x;
    double y;
} Point;

typedef struct Maison
{
    Point *cote;
    double loyer;
} Maison;

typedef struct Personne
{
    char nom[100];
    char prenom[100];
    Maison maison;
} Personne;
typedef struct Travail
{
    Point *cote;
    double salaire;
} Travail;

typedef struct Ecole
{
    Point *cote;
    double ecolage;
    char *name;
} Ecole;

typedef struct Chemin
{
    Point *tab_chemin;
    int nbpoint;
    char *nom;
} Chemin;

typedef struct Taxi
{
    double distance;
    char *nom;
    double vitesse;
} Taxi;

typedef struct Ville
{
    Chemin *chemin;
    int nbChemin;
    int nbEcole;
    int nbMaison;
    Maison *maison;
    Ecole *ecole;
    Travail *bureau;
    int nbPersonne;
    Taxi *taxi;
    Personne *personne;

} Ville;

double calculeDistance(Point point1, Point point2)
{
    double deltaX = point2.x - point1.x;
    double deltaY = point2.y - point1.y;
    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

double distance(Ville ville, int cheminIndex, int indexDepart, int indexArriver)
{
    double sum = 0.0;
    Point *points = ville.chemin[cheminIndex].tab_chemin;
    for (int i = indexDepart; i < indexArriver; i++)
    {
        sum += calculeDistance(points[i], points[i + 1]);
    }
    return sum;
}

double durerTaxi(Taxi *taxi, double cheminpluscour)
{
    if (taxi->vitesse == 0)
    {
        printf("La vitesse du taxi est nulle !\n");
        return -1;
    }
    double tempsDepart = taxi->distance / taxi->vitesse;
    double tempsArrivee = cheminpluscour / taxi->vitesse;

    double totaltemptaxi = tempsDepart + tempsArrivee;
    return totaltemptaxi;
}

Taxi *trouverMeilleurTaxi(Taxi **taxis, int nbTaxis, double cheminpluscour, double *temps)
{

    Taxi *meilleurTaxi = NULL;
    double meilleurTemps = -1;

    for (int i = 0; i < nbTaxis; i++)
    {
        if (taxis[i]->vitesse > 0)
        {

            double tempsTotal = durerTaxi(taxis[i], cheminpluscour);

            if (meilleurTemps == -1 || tempsTotal < meilleurTemps)
            {
                meilleurTemps = tempsTotal;
                meilleurTaxi = taxis[i];
            }
        }
    }

    *temps = meilleurTemps;

    return meilleurTaxi;
}
double rechercheCheminPourPlusieursArrivees(Ville ville, Point depart, Point *arrivees, int nbArrivees)
{

    double distanceTotale = 0.0;
    char **cheminsParcourus = malloc(nbArrivees * sizeof(char *));
    int cheminIndex = 0;

    for (int i = 0; i < nbArrivees; i++)
    {
        double distanceMin = -1.0;
        int cheminTrouve = 0;
        char *nomCheminUtilise = NULL;

        for (int j = 0; j < ville.nbChemin; j++)
        {

            Chemin *chemin = &ville.chemin[j];
            int indexDepart = -1, indexArriver = -1;

            for (int k = 0; k < chemin->nbpoint; k++)
            {
                if (chemin->tab_chemin[k].x == depart.x && chemin->tab_chemin[k].y == depart.y)
                {
                    indexDepart = k;
                }
                if (chemin->tab_chemin[k].x == arrivees[i].x && chemin->tab_chemin[k].y == arrivees[i].y)
                {
                    indexArriver = k;
                }
            }

            if (indexDepart != -1 && indexArriver != -1)
            {
                double currentDistance = 0.0;

                if (indexDepart <= indexArriver)
                {
                    for (int k = indexDepart; k < indexArriver; k++)
                    {
                        currentDistance += calculeDistance(chemin->tab_chemin[k], chemin->tab_chemin[k + 1]);
                    }
                }
                else
                {
                    for (int k = indexDepart; k > indexArriver; k--)
                    {
                        currentDistance += calculeDistance(chemin->tab_chemin[k], chemin->tab_chemin[k - 1]);
                    }
                }

                if (distanceMin == -1.0 || currentDistance < distanceMin)
                {

                    distanceMin = currentDistance;
                    cheminTrouve = 1;
                    nomCheminUtilise = chemin->nom; // Stocke le nom du chemin utilisé
                }
            }
        }

        if (cheminTrouve)
        {

            distanceTotale += distanceMin;
            cheminsParcourus[cheminIndex++] = nomCheminUtilise;
            depart = arrivees[i];
        }
        else
        {
            free(cheminsParcourus);
            return -1.0;
        }
    }

    printf("Chemins parcourus : \n ");
    for (int i = 0; i < cheminIndex; i++)
    {

        printf("Le chemin plus court %s\n", cheminsParcourus[i]);
    }

    free(cheminsParcourus);
    return distanceTotale;
}

Point calculermilieu(Point A, Point B)
{
    Point milieu;
    milieu.x = (A.x + B.x) / 2;
    milieu.y = (A.y + B.y) / 2;
    return milieu;
}

void heure(double heure)
{
    int heures = (int)heure;
    double minutes = (heure - heures) * 60;
    int min = (int)minutes;
    double secondes = (minutes - min) * 60;
    int sec = (int)(secondes + 0.5);

    if (sec == 60)
    {
        sec = 0;
        min++;
    }

    if (min == 60)
    {
        min = 0;
        heures++;
    }

    printf("Temps taxi : %02d:%02d:%02d\n", heures, min, sec);
}

void enRetardoupas(double heureDepart, double tempsTrajet)
{
    double heureArrivee = heureDepart + tempsTrajet;

    while (heureArrivee >= 24)
    {
        heureArrivee -= 24;
    }

    if (heureArrivee < 0 || heureArrivee >= 24)
    {
        printf("Erreur : L'heure calculee est invalide (en dehors de 0 à 24).\n");
        return;
    }

    int heures = (int)heureArrivee;
    double minutes = (heureArrivee - heures) * 60;
    int min = (int)minutes;
    double secondes = (minutes - min) * 60;
    int sec = (int)(secondes + 0.5);

    if (sec == 60)
    {
        sec = 0;
        min++;
    }

    if (min == 60)
    {
        min = 0;
        heures++;
    }

    if (heureArrivee <= 8 || (heureArrivee >= 12 && heureArrivee <= 14))
    {
        printf("Vous n'etes pas en retard. Heure d'arrivee : %02d:%02d:%02d\n", heures, min, sec);
    }
    else
    {
        printf("Vous etes en retard. Heure d'arrivee : %02d:%02d:%02d\n", heures, min, sec);
    }
}

double rechercheCheminPlusCourt(Ville ville, Point depart, Point arrivee, char **cheminNom)
{
    double distanceMin = DBL_MAX;

    for (int i = 0; i < ville.nbChemin; i++)
    {
        Chemin *chemin = &ville.chemin[i];
        int indexDepart = -1, indexArriver = -1;

        // Trouver les indices des points de départ et d'arrivée sur le chemin
        for (int j = 0; j < chemin->nbpoint; j++)
        {
            if (chemin->tab_chemin[j].x == depart.x && chemin->tab_chemin[j].y == depart.y)
            {
                indexDepart = j;
            }
            if (chemin->tab_chemin[j].x == arrivee.x && chemin->tab_chemin[j].y == arrivee.y)
            {
                indexArriver = j;
            }
        }

        // Si le chemin contient les deux points
        if (indexDepart != -1 && indexArriver != -1)
        {
            double currentDistance = 0.0;

            // Calcul de la distance totale entre les deux points
            if (indexDepart <= indexArriver)
            {
                for (int j = indexDepart; j < indexArriver; j++)
                {
                    currentDistance += calculeDistance(chemin->tab_chemin[j], chemin->tab_chemin[j + 1]);
                }
            }
            else
            {
                for (int j = indexDepart; j > indexArriver; j--)
                {
                    currentDistance += calculeDistance(chemin->tab_chemin[j], chemin->tab_chemin[j - 1]);
                }
            }

            // Mise à jour de la distance minimale
            if (currentDistance < distanceMin)
            {
                distanceMin = currentDistance;
                *cheminNom = chemin->nom; // Stocker le nom du chemin utilisé
            }
        }
    }

    return distanceMin;
}

// Fonction pour vérifier si une maison est connectée à une école
int estConnecteDirectement(Ville ville, Maison maison, Ecole ecole)
{
    for (int i = 0; i < ville.nbChemin; i++)
    {
        Chemin chemin = ville.chemin[i];
        int maisonConnectee = 0;
        int ecoleConnectee = 0;

        for (int j = 0; j < chemin.nbpoint; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if (chemin.tab_chemin[j].x == maison.cote[k].x && chemin.tab_chemin[j].y == maison.cote[k].y)
                {
                    maisonConnectee = 1;
                }
            }

            for (int k = 0; k < 4; k++)
            {
                if (chemin.tab_chemin[j].x == ecole.cote[k].x && chemin.tab_chemin[j].y == ecole.cote[k].y)
                {
                    ecoleConnectee = 1;
                }
            }
        }

        if (maisonConnectee && ecoleConnectee)
        {
            return 1; // Connexion directe trouvée
        }
    }

    return 0; // Pas de connexion directe
}

// Fonction principale pour trouver l'école la plus proche pour chaque maison
void trouverEcoleProchePourMaisons(Ville ville, Taxi **taxis, int nbTaxis)
{
    for (int i = 0; i < ville.nbMaison; i++)
    {
        Maison maison = ville.maison[i];
        double distanceMin = DBL_MAX;
        char *cheminNomMin = NULL;
        char *ecoleNomMin = NULL;

        printf("Maison : %d\n", i + 1);

        for (int j = 0; j < ville.nbEcole; j++)
        {
            Ecole ecole = ville.ecole[j];
            char *cheminNom = NULL;

            // Vérifier si la maison est connectée directement à l'école
            if (!estConnecteDirectement(ville, maison, ecole))
            {
                continue; // Passer à l'école suivante
            }

            // Trouver le chemin le plus court entre la maison et l'école
            double distance = rechercheCheminPlusCourt(ville, maison.cote[0], ecole.cote[0], &cheminNom);

            if (distance < distanceMin)
            {
                distanceMin = distance;
                cheminNomMin = cheminNom;
                ecoleNomMin = ecole.name;
            }
        }

        // Afficher les résultats pour cette maison
        if (ecoleNomMin != NULL)
        {
            printf("  -> Ecole la plus proche : %s\n", ecoleNomMin);
            printf("     Distance : %.2f\n", distanceMin);
            printf("     Chemin utilise : %s\n", cheminNomMin);

            // Trouver le meilleur taxi pour cette distance
            double temps;
            Taxi *meilleurTaxi = trouverMeilleurTaxi(taxis, nbTaxis, distanceMin, &temps);
            if (meilleurTaxi != NULL)
            {
                printf("     Meilleur taxi est le  %s . vitesse %.02f km/h\n", meilleurTaxi->nom, meilleurTaxi->vitesse);
                heure(temps);
            }
            else
            {
                printf("     Aucun taxi disponible.\n\n");
            }
        }
        else
        {
            printf("  -> Aucune ecole accessible depuis cette maison.\n\n");
        }
    }
}

int main()
{

    Point depart = {0.0, 0.0};
    Point arrivees[] = {{2.0, 5.0}};

    double temps;

    Ville ville;
    ville.nbMaison = 10;
    ville.maison = malloc(ville.nbMaison * sizeof(Maison));
    ville.maison[0].cote = malloc(4 * sizeof(Point));
    ville.maison[0].cote[0] = (Point){0.0, 0.0};
    ville.maison[0].cote[1] = (Point){5.0, 0.0};
    ville.maison[0].cote[2] = (Point){5.0, 5.0};
    ville.maison[0].cote[3] = (Point){0.0, 5.0};

    ville.maison[1].cote = malloc(4 * sizeof(Point));
    ville.maison[1].cote[0] = (Point){1.0, 1.0};
    ville.maison[1].cote[1] = (Point){4.0, 1.0};
    ville.maison[1].cote[2] = (Point){4.0, 4.0};
    ville.maison[1].cote[3] = (Point){1.0, 4.0};

    ville.maison[2].cote = malloc(4 * sizeof(Point));
    ville.maison[2].cote[0] = (Point){2.0, 2.0};
    ville.maison[2].cote[1] = (Point){6.0, 2.0};
    ville.maison[2].cote[2] = (Point){6.0, 6.0};
    ville.maison[2].cote[3] = (Point){2.0, 6.0};

    ville.maison[3].cote = malloc(4 * sizeof(Point));
    ville.maison[3].cote[0] = (Point){3.0, 3.0};
    ville.maison[3].cote[1] = (Point){7.0, 3.0};
    ville.maison[3].cote[2] = (Point){7.0, 7.0};
    ville.maison[3].cote[3] = (Point){3.0, 7.0};

    ville.maison[4].cote = malloc(4 * sizeof(Point));
    ville.maison[4].cote[0] = (Point){4.0, 4.0};
    ville.maison[4].cote[1] = (Point){8.0, 4.0};
    ville.maison[4].cote[2] = (Point){8.0, 8.0};
    ville.maison[4].cote[3] = (Point){4.0, 8.0};

    ville.maison[5].cote = malloc(4 * sizeof(Point));
    ville.maison[5].cote[0] = (Point){5.0, 5.0};
    ville.maison[5].cote[1] = (Point){9.0, 5.0};
    ville.maison[5].cote[2] = (Point){9.0, 9.0};
    ville.maison[5].cote[3] = (Point){5.0, 9.0};

    ville.maison[6].cote = malloc(4 * sizeof(Point));
    ville.maison[6].cote[0] = (Point){6.0, 6.0};
    ville.maison[6].cote[1] = (Point){10.0, 6.0};
    ville.maison[6].cote[2] = (Point){10.0, 10.0};
    ville.maison[6].cote[3] = (Point){6.0, 10.0};

    ville.maison[7].cote = malloc(4 * sizeof(Point));
    ville.maison[7].cote[0] = (Point){7.0, 7.0};
    ville.maison[7].cote[1] = (Point){11.0, 7.0};
    ville.maison[7].cote[2] = (Point){11.0, 11.0};
    ville.maison[7].cote[3] = (Point){7.0, 11.0};

    ville.maison[8].cote = malloc(4 * sizeof(Point));
    ville.maison[8].cote[0] = (Point){8.0, 8.0};
    ville.maison[8].cote[1] = (Point){12.0, 8.0};
    ville.maison[8].cote[2] = (Point){12.0, 12.0};
    ville.maison[8].cote[3] = (Point){8.0, 12.0};

    ville.maison[9].cote = malloc(4 * sizeof(Point));
    ville.maison[9].cote[0] = (Point){9.0, 9.0};
    ville.maison[9].cote[1] = (Point){13.0, 9.0};
    ville.maison[9].cote[2] = (Point){13.0, 13.0};
    ville.maison[9].cote[3] = (Point){9.0, 13.0};

    ville.nbEcole = 4;
    ville.ecole = malloc(ville.nbEcole * sizeof(Ecole));
    ville.ecole[0].cote = malloc(4 * sizeof(Point));
    ville.ecole[0].cote[0] = (Point){10.0, 10.0};
    ville.ecole[0].cote[1] = (Point){15.0, 10.0};
    ville.ecole[0].cote[2] = (Point){15.0, 15.0};
    ville.ecole[0].cote[3] = (Point){10.0, 15.0};
    ville.ecole[0].name = "Ecole A";

    ville.ecole[1].cote = malloc(4 * sizeof(Point));
    ville.ecole[1].cote[0] = (Point){1.0, 1.0};
    ville.ecole[1].cote[1] = (Point){6.0, 1.0};
    ville.ecole[1].cote[2] = (Point){6.0, 6.0};
    ville.ecole[1].cote[3] = (Point){1.0, 6.0};
    ville.ecole[1].name = "Ecole B";

    // Répétez les autres écoles avec des coordonnées variées comme suit:

    ville.ecole[2].cote = malloc(4 * sizeof(Point));
    ville.ecole[2].cote[0] = (Point){2.0, 2.0};
    ville.ecole[2].cote[1] = (Point){7.0, 2.0};
    ville.ecole[2].cote[2] = (Point){7.0, 7.0};
    ville.ecole[2].cote[3] = (Point){2.0, 7.0};
    ville.ecole[2].name = "Ecole C";

    ville.ecole[3].cote = malloc(4 * sizeof(Point));
    ville.ecole[3].cote[0] = (Point){3.0, 3.0};
    ville.ecole[3].cote[1] = (Point){8.0, 3.0};
    ville.ecole[3].cote[2] = (Point){8.0, 8.0};
    ville.ecole[3].cote[3] = (Point){3.0, 8.0};
    ville.ecole[3].name = "Ecole D";

    // Continuez ainsi pour les 10 écoles...

    ville.nbChemin = 5;
    ville.chemin = malloc(ville.nbChemin * sizeof(Chemin));
    ville.chemin[0].nbpoint = 4;
    ville.chemin[0].nom = "Chemin 1";
    ville.chemin[0].tab_chemin = malloc(4 * sizeof(Point));
    ville.chemin[0].tab_chemin[0] = (Point){0.0, 0.0};
    ville.chemin[0].tab_chemin[1] = (Point){1.0, 1.0};
    ville.chemin[0].tab_chemin[2] = (Point){6.0, 1.0};
    ville.chemin[0].tab_chemin[3] = (Point){9.0, 9.0};

    ville.chemin[1].nbpoint = 3;
    ville.chemin[1].nom = "Chemin 2";
    ville.chemin[1].tab_chemin = malloc(3 * sizeof(Point));
    ville.chemin[1].tab_chemin[0] = (Point){1.0, 1.0};
    ville.chemin[1].tab_chemin[1] = (Point){4.0, 4.0};
    ville.chemin[1].tab_chemin[2] = (Point){7.0, 7.0};

    // Répétez les autres chemins avec des points variés comme suit:

    ville.chemin[2].nbpoint = 2;
    ville.chemin[2].nom = "Chemin 3";
    ville.chemin[2].tab_chemin = malloc(2 * sizeof(Point));
    ville.chemin[2].tab_chemin[0] = (Point){2.0, 2.0};
    ville.chemin[2].tab_chemin[1] = (Point){5.0, 5.0};

    ville.chemin[3].nbpoint = 4;
    ville.chemin[3].nom = "Chemin 4";
    ville.chemin[3].tab_chemin = malloc(4 * sizeof(Point));
    ville.chemin[3].tab_chemin[0] = (Point){3.0, 3.0};
    ville.chemin[3].tab_chemin[1] = (Point){6.0, 6.0};
    ville.chemin[3].tab_chemin[2] = (Point){9.0, 9.0};
    ville.chemin[3].tab_chemin[3] = (Point){12.0, 12.0};

    ville.chemin[4].nbpoint = 2;
    ville.chemin[4].nom = "Chemin 5";
    ville.chemin[4].tab_chemin = malloc(2 * sizeof(Point));
    ville.chemin[4].tab_chemin[0] = (Point){0.0, 0.0};
    ville.chemin[4].tab_chemin[1] = (Point){2.0, 5.0};

    ville.nbPersonne = 3;
    ville.personne = malloc(ville.nbPersonne * sizeof(Personne));

    // Personne 1
    strcpy(ville.personne[0].nom, "Dupont");
    strcpy(ville.personne[0].prenom, "Jean");
    ville.personne[0].maison = ville.maison[0]; // Jean vit dans la maison 0

    // Personne 2
    strcpy(ville.personne[1].nom, "Durand");
    strcpy(ville.personne[1].prenom, "Marie");
    ville.personne[1].maison = ville.maison[1]; // Marie vit dans la maison 1

    // Personne 3
    strcpy(ville.personne[2].nom, "Lemoine");
    strcpy(ville.personne[2].prenom, "Luc");
    ville.personne[2].maison = ville.maison[2];

    int nbTaxis = 5;
    Taxi **taxis = malloc(nbTaxis * sizeof(Taxi *));
    if (taxis == NULL)
    {
        printf("Erreur d'allocation mémoire pour les taxis !\n");
        return 1;
    }
    for (int i = 0; i < nbTaxis; i++)
    {
        taxis[i] = malloc(sizeof(Taxi));
        if (taxis[i] == NULL)
        {
            printf("Erreur d'allocation mémoire pour le taxi %d !\n", i + 1);
            return 1;
        }
    }

    taxis[0]->distance = 10.0;
    strcpy(taxis[0]->nom, "Taxi 1");
    // taxis[0]->pointarriver = arriver;
    taxis[0]->vitesse = 15.0;

    taxis[1]->distance = 20.0;
    strcpy(taxis[1]->nom, "Taxi 2");
    // taxis[1]->pointarriver = arriver;
    taxis[1]->vitesse = 50.0;

    taxis[2]->distance = 30.0;
    strcpy(taxis[2]->nom, "Taxi 3");
    // taxis[2]->pointarriver = arriver;
    taxis[2]->vitesse = 75.0;

    taxis[3]->distance = 40.0;
    strcpy(taxis[3]->nom, "Taxi 4");
    // taxis[3]->pointarriver = arriver;
    taxis[3]->vitesse = 65.0;

    taxis[4]->distance = 50.0;
    strcpy(taxis[4]->nom, "Taxi 5");
    // taxis[4]->pointarriver = arriver;
    taxis[4]->vitesse = 60.0;

    // double heuredepard = 10;

    // int nbArrivees = sizeof(arrivees) / sizeof(arrivees[0]);

    // double distanceTotale = rechercheCheminPourPlusieursArrivees(ville, depart, arrivees, nbArrivees);

    // Taxi *meilleurTaxi = trouverMeilleurTaxi(taxis, nbTaxis, distanceTotale, &temps);

    // if (distanceTotale != -1.0)
    // {
    //     printf("La distance totale pour parcourir tous les points est : %f\n", distanceTotale);
    // }
    // else
    // {
    //     printf("Impossible de trouver un chemin valide pour tous les points spécifiés.\n");
    // }

    // if (meilleurTaxi)
    // {
    //     printf("Le meilleur taxi a une vitesse de %.2f  km/h  .\n", meilleurTaxi->vitesse);
    //     heure(temps);
    // }
    // else
    // {
    //     printf("Aucun taxi valide trouve.\n");
    // }

    // // trouve l ecole le plus proche par centre
    // // trouverEcoleProchePourToutesMaisons(ville);
    // enRetardoupas(heuredepard, temps);

    trouverEcoleProchePourMaisons(ville, taxis, nbTaxis);

    for (int i = 0; i < ville.nbMaison; i++)
    {
        free(ville.maison[i].cote);
    }

    for (int i = 0; i < ville.nbEcole; i++)
    {
        free(ville.ecole[i].cote);
    }

    free(ville.maison);
    free(ville.ecole);
    free(ville.personne);

    free(ville.chemin);
    free(ville.maison[0].cote);
    free(ville.ecole[0].cote);
    free(ville.chemin[0].tab_chemin);
    free(ville.maison);
    free(ville.ecole);
    free(ville.chemin);

    return 0;
}