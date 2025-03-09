#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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
} Chemin;

typedef struct Taxi
{
    Point actuelle;
    Point pointdepart;
    Point pointarriver;
    double vitesse;
} Taxi;

typedef struct Ville
{
    Chemin *chemin;
    Maison *maison;
    Ecole *ecole;
    Travail *bureau;
    Taxi *taxi;
    Personne *personne;
} Ville;

double calculeDistance(Point point1, Point point2)
{

    double deltaX = point2.x - point1.x;
    double deltaY = point2.y - point1.y;
    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    return distance;
}

double distance(Chemin *chemin)
{
    double sum = 0.0;
    for (int i = 0; i < chemin->nbpoint - 1; i++)
    {
        sum += calculeDistance(chemin->tab_chemin[i], chemin->tab_chemin[i + 1]);
    }

    return sum;
}

double minutesEnSecondes(double minutes)
{
    return minutes * 60.0;
}

double heuresEnMinutes(double heures)
{
    return heures * 60.0;
}

double durerTaxi(Taxi *taxi, double cheminpluscour)
{
    if (taxi->vitesse == 0)
    {
        printf("La vitesse du taxi est nulle !\n");
        return -1;
    }
    double tempsDepart = calculeDistance(taxi->actuelle, taxi->pointdepart) / taxi->vitesse;
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

// int rechercheChemins(Chemin *chemins, Point depart, Point arriver, Chemin **resultats, int *nbResultats, int nbChemins)
// {
//     *nbResultats = 0;
//     for (int i = 0; i < nbChemins; i++)
//     {
//         Chemin *chemin = &chemins[i];
//         int contientDepart = 0, contientArriver = 0;
//         for (int j = 0; j < chemin->nbpoint; j++)
//         {
//             if (chemin->tab_chemin[j].x == depart.x && chemin->tab_chemin[j].y == depart.y)
//             {
//                 contientDepart = 1;
//             }
//             if (chemin->tab_chemin[j].x == arriver.x && chemin->tab_chemin[j].y == arriver.y)
//             {
//                 contientArriver = 1;
//             }
//         }
//         if (contientDepart && contientArriver)
//         {

//             if (*nbResultats < nbChemins)
//             {
//                 resultats[*nbResultats] = chemin;
//                 (*nbResultats)++;
//             }
//         }
//     }
//     return *nbResultats > 0;
// }

int rechercheChemins(Chemin *chemins, Point depart, Point arriver, Chemin **resultats, int *nbResultats, int nbChemins, int *indicesOrigine)
{
    *nbResultats = 0;
    int i = 0;

    for (i = 0; i < nbChemins; i++)
    {
        Chemin *chemin = &chemins[i];
        int contientDepart = 0, contientArriver = 0;
        int indexDepart = -1, indexArriver = -1;

        for (int j = 0; j < chemin->nbpoint; j++)
        {
            if (chemin->tab_chemin[j].x == depart.x && chemin->tab_chemin[j].y == depart.y)
            {
                contientDepart = 1;
                indexDepart = j;
            }
            if (chemin->tab_chemin[j].x == arriver.x && chemin->tab_chemin[j].y == arriver.y)
            {
                contientArriver = 1;
                indexArriver = j;
            }
        }

        if (contientDepart && contientArriver && indexDepart <= indexArriver)
        {

            int longueurSousChemin = indexArriver - indexDepart + 1;
            Chemin *nouveauChemin = malloc(sizeof(Chemin));
            nouveauChemin->nbpoint = longueurSousChemin;
            nouveauChemin->tab_chemin = malloc(longueurSousChemin * sizeof(Point));

            if (!nouveauChemin->tab_chemin)
            {
                printf("Erreur d'allocation mémoire pour un sous-chemin\n");
                return 0;
            }

            for (int k = 0; k < longueurSousChemin; k++)
            {
                nouveauChemin->tab_chemin[k] = chemin->tab_chemin[indexDepart + k];
            }

            resultats[*nbResultats] = nouveauChemin;
            indicesOrigine[*nbResultats] = i;
            (*nbResultats)++;
        }
    }

    return *nbResultats > 0;
}

int plusCourteDistanceavecdepart(Chemin **chemins, int nbChemins, double *minDistance)
{
    *minDistance = distance(chemins[0]);

    int indexMin = 0;
    for (int i = 1; i < nbChemins; i++)
    {

        double dist = distance(chemins[i]);

        if (dist < *minDistance)
        {
            *minDistance = dist;
            indexMin = i;
        }
    }

    return indexMin;
}

int plusCourteDistance(Chemin *chemins, int nbChemins)
{
    double minDistance = distance(&chemins[0]);

    int indexMin = 0;
    for (int i = 1; i < nbChemins; i++)
    {

        double dist = distance(&chemins[i]);

        if (dist < minDistance)
        {
            minDistance = dist;
            indexMin = i;
        }
    }

    return minDistance;
}

int plusCourteDistanceAllerRetour(Chemin *chemin, Point nouveauPointarriver, Taxi taxi, int nbChemins)
{
    double minDistance = distance(chemin);

    int indexMin = 0;
    for (int i = 1; i < nbChemins; i++)
    {

        double dist = distance(chemin);

        if (dist < minDistance)
        {
            minDistance = dist;
            indexMin = i;
        }
    }

    return minDistance;
}

// int pluslongDistance(Chemin *chemins[], int nbChemins, double *maxdistance)
// {
//     int indexMax = 0;
//     *maxdistance = distance(chemins[0]);

//     for (int i = 1; i < nbChemins; i++)
//     {
//         double dist = distance(chemins[i]);
//         if (dist > *maxdistance)
//         {
//             *maxdistance = dist;
//             indexMax = i;
//         }
//     }
//     return indexMax;
// }

Point trouverCentreRectangle(Point A, Point B, Point C, Point D)
{
    Point centre;
    centre.x = (A.x + B.x + C.x + D.x) / 4;
    centre.y = (A.y + B.y + C.y + D.y) / 4;

    return centre;
}

Point calculerMilieu(Point A, Point B)
{
    Point milieu;
    milieu.x = (A.x + B.x) / 2;
    milieu.y = (A.y + B.y) / 2;
    return milieu;
}

Personne trouverPersonneProche(Point milieu, Personne personnes[], int nbPersonnes)
{
    double distanceMin = calculeDistance(milieu, personnes[0].maison.cote[0]);
    Personne personneProche = personnes[0];

    for (int i = 1; i < nbPersonnes; i++)
    {
        Point centreAutreMaison = trouverCentreRectangle(personnes[i].maison.cote[0], personnes[i].maison.cote[1], personnes[i].maison.cote[2], personnes[i].maison.cote[3]);
        double distance = calculeDistance(milieu, centreAutreMaison);

        if (distance < distanceMin)
        {
            distanceMin = distance;
            personneProche = personnes[i];
        }
    }

    return personneProche;
}
Ecole trouverEcoleProche(Point centreMaison, Ecole ecole[], int nbEcole)
{

    Point centreEcole0 = trouverCentreRectangle(ecole[0].cote[0], ecole[0].cote[1], ecole[0].cote[2], ecole[0].cote[3]);
    double distanceMin = calculeDistance(centreMaison, centreEcole0);
    Ecole ecoleProche = ecole[0];

    for (int i = 1; i < nbEcole; i++)
    {
        Point centreAutreEcole = trouverCentreRectangle(ecole[i].cote[0], ecole[i].cote[1], ecole[i].cote[2], ecole[i].cote[3]);
        double distance = calculeDistance(centreMaison, centreAutreEcole);

        if (distance < distanceMin)
        {

            distanceMin = distance;
            ecoleProche = ecole[i];
        }
    }

    return ecoleProche;
}

Point deplacer_taxi(Taxi *taxi)
{

    double distance_x = taxi->pointarriver.x - taxi->actuelle.x;
    double distance_y = taxi->pointarriver.y - taxi->actuelle.y;

    double distance_totale = sqrt(distance_x * distance_x + distance_y * distance_y);

    if (distance_totale <= taxi->vitesse)
    {
        taxi->actuelle = taxi->pointarriver;
        return taxi->actuelle;
    }

    double ratio = taxi->vitesse / distance_totale;
    taxi->actuelle.x += distance_x * ratio;
    taxi->actuelle.y += distance_y * ratio;

    return taxi->actuelle;
}

void trajetTaxi(Taxi *taxi)
{
    printf("Début du trajet...\n");

    while (taxi->actuelle.x != taxi->pointarriver.x || taxi->actuelle.y != taxi->pointarriver.y)
    {
        taxi->actuelle = deplacer_taxi(taxi);

        printf("Taxi se déplace à (%.2f, %.2f)\n", taxi->actuelle.x, taxi->actuelle.y);
    }

    printf("Le taxi est arrivé à destination : (%.2f, %.2f)\n", taxi->pointarriver.x, taxi->pointarriver.y);
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

int main()
{

    Point depart = {1.0, 2.0};
    Point arriver = {5.0, 6.0};

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

    taxis[0]->actuelle.x = 0.0;
    taxis[0]->actuelle.y = 0.0;
    taxis[0]->pointdepart = depart;
    // taxis[0]->pointarriver = arriver;
    taxis[0]->vitesse = 40.0;

    taxis[1]->actuelle.x = 2.0;
    taxis[1]->actuelle.y = 3.0;
    taxis[1]->pointdepart = depart;
    // taxis[1]->pointarriver = arriver;
    taxis[1]->vitesse = 3.0;

    taxis[2]->actuelle.x = 5.0;
    taxis[2]->actuelle.y = 5.0;
    taxis[2]->pointdepart = depart;
    // taxis[2]->pointarriver = arriver;
    taxis[2]->vitesse = 5.0;

    taxis[3]->actuelle.x = 8.0;
    taxis[3]->actuelle.y = 8.0;
    taxis[3]->pointdepart = depart;
    // taxis[3]->pointarriver = arriver;
    taxis[3]->vitesse = 1.0;

    taxis[4]->actuelle.x = 1.0;
    taxis[4]->actuelle.y = 3.0;
    taxis[4]->pointdepart = depart;
    // taxis[4]->pointarriver = arriver;
    taxis[4]->vitesse = 2.0;

    int taille = 6;

    Chemin *chemins = malloc(taille * sizeof(Chemin));

    int nb_points[] = {3, 2, 4, 6, 3, 5};
    for (int i = 0; i < 6; i++)
    {
        chemins[i].nbpoint = nb_points[i];
        chemins[i].tab_chemin = malloc(chemins[i].nbpoint * sizeof(Point));
        if (chemins[i].tab_chemin == NULL)
        {
            fprintf(stderr, "Erreur d'allocation mémoire pour les points des chemins\n");
            for (int j = 0; j < i; j++)
            {
                free(chemins[j].tab_chemin);
            }
            free(chemins);
            return 1;
        }
    }
    // Points du chemin 1
    chemins[0].tab_chemin[0].x = 1.0;
    chemins[0].tab_chemin[0].y = 2.0;
    chemins[0].tab_chemin[1].x = 5.0;
    chemins[0].tab_chemin[1].y = 6.0;
    chemins[0].tab_chemin[2].x = 8.0;
    chemins[0].tab_chemin[2].y = 6.0;
    // Points du chemin 2
    chemins[1].tab_chemin[0].x = 1.0;
    chemins[1].tab_chemin[0].y = 2.0;
    chemins[1].tab_chemin[1].x = 5.0;
    chemins[1].tab_chemin[1].y = 2.0;
    // Points du chemin 3
    chemins[2].tab_chemin[0].x = 2.0;
    chemins[2].tab_chemin[0].y = 3.0;
    chemins[2].tab_chemin[1].x = 1.0;
    chemins[2].tab_chemin[1].y = 2.0;
    chemins[2].tab_chemin[2].x = 4.0;
    chemins[2].tab_chemin[2].y = 8.0;
    chemins[2].tab_chemin[3].x = 5.0;
    chemins[2].tab_chemin[3].y = 7.0;
    // Points du chemin 4
    chemins[3].tab_chemin[0].x = 1.0;
    chemins[3].tab_chemin[0].y = 2.0;
    chemins[3].tab_chemin[1].x = 2.0;
    chemins[3].tab_chemin[1].y = 2.0;
    chemins[3].tab_chemin[2].x = 6.0;
    chemins[3].tab_chemin[2].y = 9.0;
    chemins[3].tab_chemin[3].x = 7.0;
    chemins[3].tab_chemin[3].y = 10.0;
    chemins[3].tab_chemin[4].x = 2.0;
    chemins[3].tab_chemin[4].y = 3.0;
    chemins[3].tab_chemin[5].x = 5.0;
    chemins[3].tab_chemin[5].y = 6.0;
    // Points du chemin 5
    chemins[4].tab_chemin[0].x = 1.0;
    chemins[4].tab_chemin[0].y = 2.0;
    chemins[4].tab_chemin[1].x = 3.0;
    chemins[4].tab_chemin[1].y = 4.5;
    chemins[4].tab_chemin[2].x = 5.0;
    chemins[4].tab_chemin[2].y = 7.0;

    // Points du chemin 6
    chemins[5].tab_chemin[0].x = 1.0;
    chemins[5].tab_chemin[0].y = 2.0;
    chemins[5].tab_chemin[1].x = 4.0;
    chemins[5].tab_chemin[1].y = 5.0;
    chemins[5].tab_chemin[2].x = 6.0;
    chemins[5].tab_chemin[2].y = 7.0;
    chemins[5].tab_chemin[3].x = 7.5;
    chemins[5].tab_chemin[3].y = 8.0;
    chemins[5].tab_chemin[4].x = 9.0;
    chemins[5].tab_chemin[4].y = 11.0;

    Chemin *resultats[6];
    int nbResultats = 0;
    double temps;
    double heuredepard = 10;
    int indexmin;
    int indicesOrigine[6];
    double mindistance;
    if (rechercheChemins(chemins, depart, arriver, resultats, &nbResultats, taille, indicesOrigine))
    {

        printf("Nombre de chemins trouves : %d\n", nbResultats);
        for (int i = 0; i < nbResultats; i++)
        {
            printf("Chemin %d du tableau original est egale a la chemin %d du nouveau tableau : \n", indicesOrigine[i] + 1, i + 1);
            for (int j = 0; j < resultats[i]->nbpoint; j++)
            {
                printf("Point %d : (%.1f, %.1f)\n",
                       j, resultats[i]->tab_chemin[j].x, resultats[i]->tab_chemin[j].y);
            }

            printf("\n");
        }
        indexmin = plusCourteDistanceavecdepart(resultats, nbResultats, &mindistance);

        printf(" Le chemin le plus cours est %d distance la plus cours %f\n", indexmin + 1, mindistance);

        Taxi *meilleurTaxi = trouverMeilleurTaxi(taxis, nbTaxis, mindistance, &temps);

        if (meilleurTaxi)
        {
            printf("Le meilleur taxi a une vitesse de %.2f  km/h  temps jusqu a arriver %f.\n", meilleurTaxi->vitesse, temps);
        }
        else
        {
            printf("Aucun taxi valide trouve.\n");
        }
    }

    enRetardoupas(heuredepard, temps);

    Point A = {0, 0}, B = {4, 0}, C = {4, 4}, D = {0, 4};
    Point E = {5, 5}, F = {9, 5}, G = {9, 9}, H = {5, 9};
    Point I = {1, 1}, J = {6, 1}, K = {6, 6}, L = {1, 6};
    Point M = {0, 0}, N = {2, 0}, O = {2, 3}, P = {0, 3};
    Point Q = {-3, -2}, R = {2, -2}, S = {2, 1}, T = {-3, 1};
    Point U = {10, 10}, V = {15, 10}, W = {15, 15}, X = {10, 15};
    Point Y = {-5, -5}, Z = {-2, -5}, A1 = {-2, -3}, A2 = {-5, -3};

    Maison maison1 = {&A, 1200};
    Maison maison2 = {&E, 1300};
    Maison maison3 = {&I, 1200};
    Maison maison4 = {&M, 1300};
    Maison maison5 = {&Q, 1500};
    Maison maison6 = {&U, 1700};
    Maison maison7 = {&Y, 1700};

    Point A6 = {2, 3}, B6 = {6, 3}, C6 = {6, 7}, D6 = {2, 7};
    Point E6 = {5, 5}, F6 = {9, 5}, G6 = {9, 9}, H6 = {5, 9};
    Point I6 = {1, 1}, J6 = {6, 1}, K6 = {6, 6}, L6 = {1, 6};
    Point M6 = {0, 0}, N6 = {2, 0}, O6 = {2, 3}, P6 = {0, 3};
    Point Q6 = {-3, -2}, R6 = {2, -2}, S6 = {2, 1}, T6 = {-3, 1};
    Point U6 = {10, 10}, V6 = {15, 10}, W6 = {15, 15}, X6 = {10, 15};
    Point Y6 = {-5, -5}, Z6 = {-2, -5}, A8 = {-2, -3}, A7 = {-5, -3};

    Personne personnes[7] = {
        {"Dupont", "Jean", maison1},
        {"Martin", "Paul", maison2},
        {"Micka", "Jean", maison3},
        {"Kami", "Paul", maison4},
        {"Lemoine", "Claire", maison5},
        {"Robert", "Luc", maison6},
        {"Robertoka", "Luc", maison7},
    };

    Ecole ecole[7] = {
        {&A6, 1000, "Ecole Alpha"},
        {&E6, 1200, "Ecole Beta"},
        {&I6, 900, "Ecole Gamma"},
        {&M6, 800, "Ecole Delta"},
        {&Q6, 1500, "Ecole Epsilon"},
        {&U6, 1800, "Ecole Zeta"},
        {&V6, 2000, "Ecole Eta"},
    };

    Point centreMaison1 = trouverCentreRectangle(A, B, C, D);
    Point centreEcole = trouverCentreRectangle(A6, B6, C6, D6);

    Personne personneProche = trouverPersonneProche(centreMaison1, personnes, 7);

    Ecole ecoleProche = trouverEcoleProche(centreMaison1, ecole, 7);

    trouverEcoleProchePourToutesMaisons(personnes, 7, ecole, 7);
    for (int i = 0; i < nbResultats; i++)
    {
        free(resultats[i]->tab_chemin);
        free(resultats[i]);
    }

    for (int i = 0; i < taille; i++)
    {
        free(chemins[i].tab_chemin);
    }
    free(chemins);

    return 0;
}
