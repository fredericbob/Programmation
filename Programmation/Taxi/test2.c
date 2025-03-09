#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

typedef struct
{
    double x, y;
} Point;

typedef struct
{
    Point *tab_chemin;
    int nbpoint;
    char *nom;
} Chemin;

typedef struct
{
    Point *cote;
    int nb_cotes;
    char *name;
} Ecole;
typedef struct
{
    Point *cote;
    int nb_cotes;
    char *name;
} Maison;
typedef struct
{
    Chemin *chemins;
    Maison *maison;
    Ecole *ecole;
    int nb_chemins;
    int nbMaison;
    int nb_ecoles;
} Ville;
double calculeDistance(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Fonction pour trouver le point milieu d'un segment
Point trouverMilieu(Point a, Point b)
{
    Point milieu;
    milieu.x = (a.x + b.x) / 2.0;
    milieu.y = (a.y + b.y) / 2.0;
    return milieu;
}

// Fonction pour trouver le milieu du côté d'une maison où passe le chemin
Point trouverMilieuCoteMaison(Maison maison, Chemin chemin)
{
    for (int i = 0; i < maison.nb_cotes; i++)
    {
        Point a = maison.cote[i];
        Point b = maison.cote[(i + 1) % maison.nb_cotes]; // Le côté suivant (en boucle)

        // Parcourir les points du chemin pour voir s'il intersecte ce côté
        for (int j = 0; j < chemin.nbpoint - 1; j++)
        {
            Point c = chemin.tab_chemin[j];
            Point d = chemin.tab_chemin[j + 1];

            // Vérifier si le chemin passe par le côté (simple vérification : coordonnées proches)
            if ((c.x == a.x && c.y == a.y && d.x == b.x && d.y == b.y) ||
                (c.x == b.x && c.y == b.y && d.x == a.x && d.y == a.y))
            {
                // Trouver le point milieu du côté
                return trouverMilieu(a, b);
            }
        }
    }

    // Si aucun côté correspondant n'est trouvé, renvoyer un point invalide
    return (Point){-1, -1};
}

// Fonction pour trouver le chemin le plus court entre une maison et une école
double rechercheCheminPlusCourt(Ville ville, Point depart, Point arrivee, char **cheminNom)
{
    double distanceMin = DBL_MAX;

    for (int i = 0; i < ville.nb_chemins; i++)
    {
        Chemin *chemin = &ville.chemins[i];
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

// Fonction principale pour trouver l'école la plus proche pour chaque maison
void trouverEcoleProchePourMaisons(Ville ville)
{
    for (int i = 0; i < ville.nbMaison; i++)
    {
        Maison maison = ville.maison[i];
        double distanceMin = DBL_MAX;
        char *cheminNomMin = NULL;
        char *ecoleNomMin = NULL;

        printf("Maison : %s\n", maison.name);

        for (int j = 0; j < ville.nb_ecoles; j++)
        {
            Ecole ecole = ville.ecole[j];
            char *cheminNom = NULL;

            // Trouver le milieu du côté de la maison où passe le chemin
            Point milieuCoteMaison = trouverMilieuCoteMaison(maison, ville.chemins[j]);

            if (milieuCoteMaison.x == -1 && milieuCoteMaison.y == -1)
            {
                continue; // Aucun côté trouvé, passer à l'école suivante
            }

            // Trouver le chemin le plus court entre le milieu et l'école
            double distance = rechercheCheminPlusCourt(ville, milieuCoteMaison, ecole.cote[0], &cheminNom);

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
            printf("     Chemin utilisé : %s\n\n", cheminNomMin);
        }
        else
        {
            printf("  -> Aucune école accessible depuis cette maison.\n\n");
        }
    }
}

int main()
{
    Ville ville;

    // Initialisation des données
    ville.nb_chemins = 2;

    // Allocation des chemins
    ville.chemins = malloc(ville.nb_chemins * sizeof(Chemin));
    ville.chemins[0] = (Chemin){.nom = "Chemin A", .nbpoint = 3, .tab_chemin = malloc(3 * sizeof(Point))};
    ville.chemins[0].tab_chemin[0] = (Point){0, 0};
    ville.chemins[0].tab_chemin[1] = (Point){5, 5};
    ville.chemins[0].tab_chemin[2] = (Point){10, 10};

    ville.chemins[1] = (Chemin){.nom = "Chemin B", .nbpoint = 3, .tab_chemin = malloc(3 * sizeof(Point))};
    ville.chemins[1].tab_chemin[0] = (Point){2, 2};
    ville.chemins[1].tab_chemin[1] = (Point){6, 6};
    ville.chemins[1].tab_chemin[2] = (Point){12, 12};

    ville.nbMaison = 3;
    ville.maison = malloc(ville.nbMaison * sizeof(Maison));
    ville.maison[0].name = "Maison A";
    ville.maison[0].nb_cotes = 4;
    ville.maison[0].cote = malloc(4 * sizeof(Point));
    ville.maison[0].cote[0] = (Point){0.0, 0.0};
    ville.maison[0].cote[1] = (Point){5.0, 0.0};
    ville.maison[0].cote[2] = (Point){5.0, 5.0};
    ville.maison[0].cote[3] = (Point){0.0, 5.0};

    ville.maison[1].cote = malloc(4 * sizeof(Point));
    ville.maison[1].name = "Maison B";
    ville.maison[1].cote[0] = (Point){1.0, 1.0};
    ville.maison[1].cote[1] = (Point){4.0, 1.0};
    ville.maison[1].cote[2] = (Point){4.0, 4.0};
    ville.maison[1].cote[3] = (Point){1.0, 4.0};

    ville.maison[2].cote = malloc(4 * sizeof(Point));

    ville.maison[2].name = "Maison C";
    ville.maison[2].cote[0] = (Point){2.0, 2.0};
    ville.maison[2].cote[1] = (Point){6.0, 2.0};
    ville.maison[2].cote[2] = (Point){6.0, 6.0};
    ville.maison[2].cote[3] = (Point){2.0, 6.0};

    ville.nb_ecoles = 4;
    ville.ecole = malloc(ville.nb_ecoles * sizeof(Ecole));

    ville.ecole[0].nb_cotes = 4;
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
    // Trouver les écoles les plus proches
    trouverEcoleProchePourMaisons(ville);

    // Libération de la mémoire (à compléter si nécessaire)

    return 0;
}
