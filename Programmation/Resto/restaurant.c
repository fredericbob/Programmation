#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct Categorie
{
    char *nom;
};
typedef struct Categorie cat;

struct Aliment
{
    char *nom;
    cat catAliment;
    double prixAchat;
    int calAliment;
};
typedef struct Aliment Aliment;

struct Plat
{
    char *nom;
    int nbAliment;
    Aliment *listeAl;
    double *poidsAl;
    double prixVente;
    int tsirony;
    cat CatPlat;
};
typedef struct Plat Plat;

struct Date
{
    int jour;
    int mois;
    int annee;
};
typedef struct Date Date;

struct Vente
{
    Plat plat;
    Date date;
};
typedef struct Vente Vente;

struct Resto
{
    char *nom;
    int nbPlat;
    Plat *listePlat;
    int nbVente;
    Vente *listeVente;
};
typedef struct Resto Resto;

int sommeCal(Plat p)
{
    int retour = 0;
    for (int i = 0; i < p.nbAliment; i++)
    {
        double calories = p.listeAl[i].calAliment * (p.poidsAl[i]);

        retour += calories;
    }

    return retour;
}

double CalculPrixAchat(Plat p)
{
    double retour = 0;
    for (int i = 0; i < p.nbAliment; i++)
    {
        retour = retour + p.listeAl[i].prixAchat * p.poidsAl[i];
    }
    return retour;
}

double Benefice(Plat p)
{
    double retour = p.prixVente - CalculPrixAchat(p);
    return retour;
}

Plat meilleurPlat(Resto r)
{
    Plat *classement = malloc(r.nbPlat * sizeof(Plat));
    for (int i = 0; i < r.nbPlat; i++)
    {
        classement[i] = r.listePlat[i];
    }
    for (int i = 0; i < r.nbPlat - 1; i++)
    {
        for (int j = 0; j < r.nbPlat - 1 - i; j++)
        {
            if (classement[j].tsirony - 4 * sommeCal(classement[j]) < classement[j + 1].tsirony - 4 * sommeCal(classement[j + 1]))
            {
                Plat temp = classement[j];
                classement[j] = classement[j + 1];
                classement[j + 1] = temp;
            }
        }
    }
    Plat meilleur = classement[0];
    free(classement);
    return meilleur;
}

Plat meilleurParCat(Resto r, cat c)
{
    Plat *classement = malloc(r.nbPlat * sizeof(Plat));
    for (int i = 0; i < r.nbPlat; i++)
    {
        classement[i] = r.listePlat[i];
    }
    for (int i = 0; i < r.nbPlat - 1; i++)
    {
        for (int j = 0; j < r.nbPlat - 1 - i; j++)
        {
            if (classement[j].tsirony - 4 * sommeCal(classement[j]) < classement[j + 1].tsirony - 4 * sommeCal(classement[j + 1]))
            {
                Plat temp = classement[j];
                classement[j] = classement[j + 1];
                classement[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < r.nbPlat; i++)
    {
        if (strcmp(classement[i].CatPlat.nom, c.nom) == 0)
        {
            Plat meilleur = classement[i];
            free(classement);
            return meilleur;
        }
    }
    free(classement);
    return (Plat){0};
}

double BeneficeparCat(Resto r, cat c)
{
    double total = 0;
    for (int i = 0; i < r.nbPlat; i++)
    {
        if (strcmp(r.listePlat[i].CatPlat.nom, c.nom) == 0)
        {
            total = total + Benefice(r.listePlat[i]);
        }
    }
    return total;
}

void ventesParDateEtCat(Resto r, Date d, cat c)
{
    printf("Ventes pour la categorie '%s' le %02d/%02d/%04d:\n", c.nom, d.jour, d.mois, d.annee);
    for (int i = 0; i < r.nbVente; i++)
    {
        if (strcmp(r.listeVente[i].plat.CatPlat.nom, c.nom) == 0 &&
            r.listeVente[i].date.jour == d.jour &&
            r.listeVente[i].date.mois == d.mois &&
            r.listeVente[i].date.annee == d.annee)
        {
            printf("- %s\n", r.listeVente[i].plat.nom);
        }
    }
}

void main()
{
    Aliment hena, patte, crevette, riz, rano, huile;
    hena.nom = malloc(100);
    strcpy(hena.nom, "Hena");
    hena.prixAchat = 22;
    patte.nom = malloc(100);
    strcpy(patte.nom, "patte");
    patte.prixAchat = 2.5;
    crevette.nom = malloc(100);
    strcpy(crevette.nom, "crevette");
    crevette.prixAchat = 30;
    riz.nom = malloc(100);
    strcpy(riz.nom, "riz");
    riz.prixAchat = 4.2;
    rano.nom = malloc(100);
    strcpy(rano.nom, "rano");
    rano.prixAchat = 0.2;
    huile.nom = malloc(100);
    strcpy(huile.nom, "huile");
    huile.prixAchat = 10;

    cat plat, soupe;
    plat.nom = malloc(100);
    strcpy(plat.nom, "plat");
    soupe.nom = malloc(100);
    strcpy(soupe.nom, "soupe");

    Plat rizcantonnais, soupe_chinois, riz_crevette;
    rizcantonnais.nom = malloc(100);
    strcpy(rizcantonnais.nom, "riz cantonnais");
    rizcantonnais.nbAliment = 3;
    rizcantonnais.listeAl = malloc(rizcantonnais.nbAliment * sizeof(Aliment));
    rizcantonnais.poidsAl = malloc(rizcantonnais.nbAliment * sizeof(double));
    rizcantonnais.listeAl[0] = riz;
    rizcantonnais.poidsAl[0] = 100;
    rizcantonnais.listeAl[1] = hena;
    rizcantonnais.poidsAl[1] = 100;
    rizcantonnais.listeAl[2] = crevette;
    rizcantonnais.poidsAl[2] = 100;
    rizcantonnais.prixVente = 15000;
    rizcantonnais.CatPlat = plat;
    rizcantonnais.tsirony = 10;

    soupe_chinois.nom = malloc(100);
    strcpy(soupe_chinois.nom, "soupe chinoise");
    soupe_chinois.nbAliment = 3;
    soupe_chinois.listeAl = malloc(soupe_chinois.nbAliment * sizeof(Aliment));
    soupe_chinois.poidsAl = malloc(soupe_chinois.nbAliment * sizeof(double));
    soupe_chinois.listeAl[0] = patte;
    soupe_chinois.poidsAl[0] = 150;
    soupe_chinois.listeAl[1] = crevette;
    soupe_chinois.poidsAl[1] = 100;
    soupe_chinois.listeAl[2] = rano;
    soupe_chinois.poidsAl[2] = 150;
    soupe_chinois.prixVente = 16000;
    soupe_chinois.CatPlat = soupe;
    soupe_chinois.tsirony = 8;

    riz_crevette.nom = malloc(100);
    strcpy(riz_crevette.nom, "riz au crevette");
    riz_crevette.nbAliment = 2;
    riz_crevette.listeAl = malloc(riz_crevette.nbAliment * sizeof(Aliment));
    riz_crevette.poidsAl = malloc(riz_crevette.nbAliment * sizeof(double));
    riz_crevette.listeAl[0] = riz;
    riz_crevette.poidsAl[0] = 100;
    riz_crevette.listeAl[1] = crevette;
    riz_crevette.poidsAl[1] = 200;
    riz_crevette.prixVente = 20000;
    riz_crevette.CatPlat = plat;
    riz_crevette.tsirony = 15;

    Vente v1, v2, v3;
    v1.plat = rizcantonnais;
    v1.date.jour = 10;
    v1.date.mois = 1;
    v1.date.annee = 2025;

    v2.plat = soupe_chinois;
    v2.date.jour = 10;
    v2.date.mois = 1;
    v2.date.annee = 2025;

    v3.plat = riz_crevette;
    v3.date.jour = 11;
    v3.date.mois = 1;
    v3.date.annee = 2025;

    Resto ITU;
    ITU.nom = malloc(100);
    strcpy(ITU.nom, "Restaurant ITU");
    ITU.nbPlat = 3;
    ITU.listePlat = malloc(ITU.nbPlat * sizeof(Plat));
    ITU.listePlat[0] = rizcantonnais;
    ITU.listePlat[1] = soupe_chinois;
    ITU.listePlat[2] = riz_crevette;
    ITU.nbVente = 3;
    ITU.listeVente = malloc(ITU.nbVente * sizeof(Vente));
    ITU.listeVente[0] = v1;
    ITU.listeVente[1] = v2;
    ITU.listeVente[2] = v3;

    Plat meilleur = meilleurPlat(ITU);
    printf("Le meilleur plat est : %s\n", meilleur.nom);

    Plat meilleur_soupe = meilleurParCat(ITU, soupe);
    if (meilleur_soupe.nom)
    {
        printf("Le meilleur plat dans la categorie '%s' est : %s\n", soupe.nom, meilleur_soupe.nom);
    }
    else
    {
        printf("Aucun plat trouve dans la categorie '%s'.\n", soupe.nom);
    }

    Date recherche_date = {10, 1, 2025};
    printf("\nVentes pour la date %02d/%02d/%04d dans la categorie '%s':\n",
           recherche_date.jour, recherche_date.mois, recherche_date.annee, soupe.nom);
    ventesParDateEtCat(ITU, recherche_date, soupe);

    printf("Le benefice du %s est : %.0f  Ar\n", rizcantonnais.nom, (Benefice(rizcantonnais) + Benefice(riz_crevette)));
    printf("Le benefice du %s est : %.0f Ar\n", soupe_chinois.nom, Benefice(soupe_chinois));
}