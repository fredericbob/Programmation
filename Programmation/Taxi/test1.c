#include "string.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

struct point
{
    double x;
    double y;
};
typedef struct point point;

struct Maison
{
    char *adresse;
    point *pt;
    double loyer;
};
typedef struct Maison maison;

struct Ecole
{
    char *adresse;
    point *pt;
    double ecolage;
};
typedef struct Ecole ecole;

struct Chemin
{
    point *trajet;
    int nbpoint;
    char *nom;
    double distance;
};
typedef struct Chemin chemin;

struct chrono
{
    int heure, mn, sec;
};
typedef struct chrono chrono;

struct taxi
{
    double distanceMaison;
    double vitesse;
};
typedef struct taxi taxi;

struct Ville
{
    char *nom;
    point *frontiere;
    maison *listemaison;
    ecole *listeecole;
    taxi *listetaxi;
    chemin *listechemin;
    int nbM, nbE, nbT, nbC;
};
typedef struct Ville ville;

// fonction
void trierPoint(point *pt)
{
    point origine = pt[0];
    int i0 = 0;
    for (int i = 0; i < 4; i++)
    {
        if (pt[i].x < origine.x && pt[i].y < origine.y)
        {
            origine = pt[i];
            i0 = i;
        }
    }
    pt[i0] = pt[0];
    pt[0] = origine;
    int i1 = 1;
    for (int i = 1; i < 4; i++)
    {
        if (pt[i].x == origine.x && pt[i].y > origine.y)
        {
            origine = pt[i];
            i1 = i;
        }
    }
    pt[i1] = pt[1];
    pt[1] = origine;
    if (pt[2].y < pt[3].y)
    {
        origine = pt[2];
        pt[2] = pt[3];
        pt[3] = origine;
    }
}

double distance(point a, point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int mandaloPoint(point a, point b, point p)
{
    if (a.x == b.x)
    {
        if (p.x == a.x && ((p.y >= a.y && p.y <= b.y) || (p.y <= a.y && p.y >= b.y)))
        {
            return 1;
        }
    }
    else if (a.y == b.y)
    {
        if (p.y == a.y && ((p.x >= a.x && p.x <= b.x) || (p.x <= a.x && p.x >= b.x)))
        {
            return 1;
        }
    }
    return 0;
}

double calculdistance(chemin c)
{
    double total = 0;
    for (int i = 0; i < c.nbpoint - 1; i++)
    {
        total += distance(c.trajet[i], c.trajet[i + 1]);
    }
    return total;
}

chemin modifchemin(point depart, point arrivee, chemin c)
{
    chemin newchemin;
    newchemin.nbpoint = 0;
    newchemin.trajet = malloc((c.nbpoint) * sizeof(point));
    int dep = -1, arriv = -1;

    for (int i = 0; i < c.nbpoint - 1; i++)
    {
        if (mandaloPoint(c.trajet[i], c.trajet[i + 1], depart) == 1)
        {
            dep = i;
        }
        if (mandaloPoint(c.trajet[i], c.trajet[i + 1], arrivee) == 1)
        {
            arriv = i;
            break;
        }
    }

    if (dep == -1 || arriv == -1)
    {
        return c;
    }

    else
    {
        if (dep == arriv)
        {
            newchemin.trajet[0] = depart;
            newchemin.trajet[1] = arrivee;
            newchemin.nbpoint = 2;
        }
        else
        {
            newchemin.nbpoint = arriv + 2 - dep;
            newchemin.trajet[0] = depart;
            for (int i = 1; i < newchemin.nbpoint - 1; i++)
            {
                newchemin.trajet[i] = c.trajet[dep + i];
            }
            newchemin.trajet[newchemin.nbpoint - 1] = arrivee;
        }
        newchemin.distance = calculdistance(newchemin);
        return newchemin;
    }
}

int pointMikasika(point p, point *r)
{
    if (p.x >= r[0].x && p.x <= r[2].x && p.y >= r[0].y && p.y <= r[2].y)
    {
        return 1;
    }
    return 0;
}

int mipetaka(chemin c, point *trano)
{
    trierPoint(trano);
    for (int i = 0; i < c.nbpoint; i++)
    {
        if (pointMikasika(c.trajet[i], trano) == 1)
        {
            return 1;
        }
    }
    return 0;
}

point *vavahady(point *trano)
{
    trierPoint(trano);
    point *v = malloc(4 * sizeof(point));
    for (int i = 0; i < 4; i++)
    {
        v[i].x = (trano[i].x + trano[(i + 1) % 4].x) / 2;
        v[i].y = (trano[i].y + trano[(i + 1) % 4].y) / 2;
    }
    return v;
}

int mandaloTrano(chemin c, point *trano)
{
    if (mipetaka(c, trano) == 1)
    {
        return 1;
    }
    point *v = vavahady(trano);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < c.nbpoint - 1; j++)
        {
            if (mandaloPoint(c.trajet[j], c.trajet[j + 1], v[i]) == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

chemin lalanaFohy(ville v, point *depart, point *arrivee)
{
    trierPoint(depart);
    trierPoint(arrivee);
    chemin fohy;
    fohy.distance = 100000000;
    point a, b;
    for (int i = 0; i < v.nbC; i++)
    {
        if (mandaloTrano(v.listechemin[i], depart) == 1 && mandaloTrano(v.listechemin[i], arrivee) == 1)
        {
            if (mipetaka(v.listechemin[i], depart))
            {
                for (int j = 0; j < v.listechemin[i].nbpoint; j++)
                {
                    if (pointMikasika(v.listechemin[i].trajet[j], depart))
                    {
                        a.x = v.listechemin[i].trajet[j].x;
                        a.y = v.listechemin[i].trajet[j].y;
                    }
                }
            }
            point *vav = vavahady(depart);
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < v.listechemin[i].nbpoint - 1; k++)
                {
                    if (mandaloPoint(v.listechemin[i].trajet[k], v.listechemin[i].trajet[k + 1], vav[j]) == 1)
                    {
                        a.x = vav[j].x;
                        a.y = vav[j].y;
                        break;
                    }
                }
            }

            if (mipetaka(v.listechemin[i], arrivee))
            {
                for (int j = 0; j < v.listechemin[i].nbpoint; j++)
                {
                    if (pointMikasika(v.listechemin[i].trajet[j], arrivee))
                    {
                        b.x = v.listechemin[i].trajet[j].x;
                        b.y = v.listechemin[i].trajet[j].y;
                        break;
                    }
                }
            }
            vav = vavahady(arrivee);
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < v.listechemin[i].nbpoint - 1; k++)
                {
                    if (mandaloPoint(v.listechemin[i].trajet[k], v.listechemin[i].trajet[k + 1], vav[j]) == 1)
                    {
                        b.x = vav[j].x;
                        b.y = vav[j].y;
                        break;
                    }
                }
            }
            chemin new = modifchemin(a, b, v.listechemin[i]);
            new.distance = calculdistance(new);
            if (new.distance < fohy.distance)
            {
                fohy = new;
            }
        }
    }
    return fohy;
}

ecole EcoleProche(ville v, maison m)
{
    ecole akaiky = v.listeecole[0];
    double distance = lalanaFohy(v, m.pt, v.listeecole[0].pt).distance;
    for (int i = 1; i < v.nbE; i++)
    {
        double d = lalanaFohy(v, m.pt, v.listeecole[i].pt).distance;
        if (d < distance)
        {
            distance = d;
            akaiky = v.listeecole[i];
        }
    }
    return akaiky;
}

double_t dureeTrajet(taxi t, chemin c)
{
    return ((t.distanceMaison + c.distance) / t.vitesse);
}

chrono DureeMinimum(ville v, chemin c)
{
    double d = dureeTrajet(v.listetaxi[0], c);
    for (int i = 1; i < v.nbT; i++)
    {
        double temps = dureeTrajet(v.listetaxi[i], c);
        if (temps < d)
        {
            d = temps;
        }
    }
    chrono cr;
    cr.heure = d;
    cr.mn = (d - cr.heure) * 60;
    cr.sec = (d - cr.heure - cr.mn / 60.0) * 3600;
    return cr;
}

void main()
{
    maison trano;
    trano.adresse = malloc(50 * sizeof(char));
    trano.adresse = strcpy(trano.adresse, "Mahamasina");
    trano.pt = malloc(4 * sizeof(point));
    trano.pt[0].x = 5;
    trano.pt[0].y = 5;
    trano.pt[1].x = 5;
    trano.pt[1].y = 8;
    trano.pt[2].x = 9;
    trano.pt[2].y = 8;
    trano.pt[3].x = 9;
    trano.pt[3].y = 5;

    ecole itu, ins;
    itu.adresse = malloc(50 * sizeof(char));
    itu.adresse = strcpy(itu.adresse, "ITU");
    itu.pt = malloc(4 * sizeof(point));
    itu.pt[0].x = 10;
    itu.pt[0].y = 5;
    itu.pt[1].x = 10;
    itu.pt[1].y = 10;
    itu.pt[2].x = 15;
    itu.pt[2].y = 10;
    itu.pt[3].x = 15;
    itu.pt[3].y = 5;

    ins.adresse = malloc(50 * sizeof(char));
    ins.adresse = strcpy(ins.adresse, "INS");
    ins.pt = malloc(4 * sizeof(point));
    ins.pt[0].x = 20;
    ins.pt[0].y = 0;
    ins.pt[1].x = 20;
    ins.pt[1].y = 5;
    ins.pt[2].x = 24;
    ins.pt[2].y = 5;
    ins.pt[3].x = 24;
    ins.pt[3].y = 0;

    chemin c1, c2, c3;

    c1.nbpoint = 2;
    c1.nom = malloc(50 * sizeof(char));
    strcpy(c1.nom, "chemin 1");
    c1.trajet = malloc(c1.nbpoint * sizeof(point));

    c1.trajet[0].x = 0;
    c1.trajet[0].y = 5;
    c1.trajet[1].x = 30;
    c1.trajet[1].y = 5;

    // Initialisation de c2
    c2.nbpoint = 4;
    c2.nom = malloc(50 * sizeof(char));
    strcpy(c2.nom, "chemin 2");
    c2.trajet = malloc(c2.nbpoint * sizeof(point));

    c2.trajet[0].x = 5;
    c2.trajet[0].y = 5;
    c2.trajet[1].x = 5;
    c2.trajet[1].y = 10;
    c2.trajet[2].x = 10;
    c2.trajet[2].y = 10;
    c2.trajet[3].x = 10;
    c2.trajet[3].y = 0;

    // Initialisation de c3
    c3.nbpoint = 3;
    c3.nom = malloc(50 * sizeof(char));
    strcpy(c3.nom, "chemin 3");
    c3.trajet = malloc(c3.nbpoint * sizeof(point));

    c3.trajet[0].x = 5;
    c3.trajet[0].y = 10;
    c3.trajet[1].x = 5;
    c3.trajet[1].y = 0;
    c3.trajet[2].x = 20;
    c3.trajet[2].y = 0;

    taxi t1, t2;
    t1.distanceMaison = 10;
    t1.vitesse = 9.4;

    t2.distanceMaison = 8.4;
    t2.vitesse = 5;

    ville v;
    v.nbM = 1;
    v.nbE = 2;
    v.nbC = 3;
    v.nbT = 2;
    v.listemaison = malloc(v.nbM * sizeof(maison));
    v.listemaison[0] = trano;
    v.listeecole = malloc(v.nbE * sizeof(ecole));
    v.listeecole[0] = itu;
    v.listeecole[1] = ins;
    v.listechemin = malloc(v.nbC * sizeof(chemin));
    v.listechemin[0] = c1;
    v.listechemin[1] = c2;
    v.listechemin[2] = c3;
    v.listetaxi = malloc(2 * sizeof(taxi));
    v.listetaxi[0] = t2;
    v.listetaxi[1] = t1;

    ecole pres = EcoleProche(v, trano);
    chemin lalana = lalanaFohy(v, trano.pt, pres.pt);
    printf("L'ecole la plus proche est %s\n", pres.adresse);

    for (int i = 0; i < lalana.nbpoint; i++)
    {
        printf("Trajet = (%.1f ; %.1f)\n", lalana.trajet[i].x, lalana.trajet[i].y);
    }
    lalana.nom = malloc(50 * sizeof(char));
    strcpy(lalana.nom, "Chemin le plus court"); // Assurez-vous de donner un nom correct au chemin

    printf("Le chemin le plus cour est :%s\n", lalana.nom);
    printf("Distance = %.1f KM\n", lalana.distance);

    chrono dur = DureeMinimum(v, lalana);
    printf("La duree minimum du trajet est %dh %dmn %ds\n", dur.heure, dur.mn, dur.sec);

    free(trano.adresse);
    free(trano.pt);
    free(itu.adresse);
    free(itu.pt);
    free(ins.adresse);
    free(ins.pt);
    free(c1.trajet);
    free(c2.trajet);
    free(c3.trajet);
    free(v.listemaison);
    free(v.listeecole);
    free(v.listechemin);
    free(v.listetaxi);
}