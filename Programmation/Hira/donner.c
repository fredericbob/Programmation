#include "string.h"
#include "stdio.h"
#include "stdlib.h"

struct Chanteur
{
    char *nom;
    int popularite;
};
typedef struct Chanteur chanteur;

struct Heure
{
    int heure, mn, sec;
};
typedef struct Heure Heure;

struct Date
{
    int jour, mois, annee;
};
typedef struct Date date;

struct Hira
{
    char *titre;
    char *langue;
    chanteur mpihira;
    int tempo;
    Heure duree;
    date sortie;
};
typedef struct Hira hira;

struct Tranche
{
    int Jour;
    Heure heure_debut;
    Heure heure_fin;
    char *langue;
    char *critere;
    hira *listehira;
    int nbhira;
};
typedef struct Tranche tranche;

int MakaChiffre(char *phrase)
{
    char *nb = malloc(10 * sizeof(char));
    for (int i = 0; i < 10; i++)
    {
        nb[i] = '0' + i;
    }

    int chiffre = 0;
    for (int i = 0; i < strlen(phrase); i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (phrase[i] == nb[j])
            {
                chiffre = (chiffre * 10) + j;
            }
        }
    }
    return chiffre;
}

char **split(char *phrase)
{
    int count = 1;
    for (int i = 0; phrase[i] != '\0'; i++)
    {
        if (phrase[i] == ';')
        {
            count++;
        }
    }

    char **part = malloc(count * sizeof(char *));
    for (int i = 0; i < count; i++)
    {
        part[i] = malloc(50 * sizeof(char));
    }

    int j = 0, k = 0;
    for (int i = 0; i < strlen(phrase); i++)
    {
        part[j][k] = phrase[i];
        k++;
        if (phrase[i] == ';')
        {
            part[j][k] = '\0';
            k = 0;
            j++;
        }
    }
    return part;
}

int manajaCritere(hira c, char *critere)
{
    char **p = split(critere);
    int annee = MakaChiffre(p[0]);
    int pop = MakaChiffre(p[1]);
    int tempo = MakaChiffre(p[2]);

    int c1 = 0, c2 = 0, c3 = 0;
    for (int i = 0; i < strlen(p[0]); i++)
    {
        if (p[0][i] == '>')
        {
            if (p[0][i + 1] == '=')
            {
                if (c.sortie.annee >= annee)
                {
                    c1 = 1;
                }
            }
            else
            {
                if (c.sortie.annee > annee)
                {
                    c1 = 1;
                }
            }
        }
        else if (p[0][i] == '<')
        {
            if (p[0][i + 1] == '=')
            {
                if (c.sortie.annee <= annee)
                {
                    c1 = 1;
                }
            }
            else
            {
                if (c.sortie.annee < annee)
                {
                    c1 = 1;
                }
            }
        }
    }

    for (int i = 0; i < strlen(p[1]); i++)
    {
        if (p[1][i] == '>')
        {
            if (p[1][i + 1] == '=')
            {
                if (c.mpihira.popularite >= pop)
                {
                    c2 = 1;
                }
            }
            else
            {
                if (c.mpihira.popularite > pop)
                {
                    c2 = 1;
                }
            }
        }
        else if (p[1][i] == '<')
        {
            if (p[1][i + 1] == '=')
            {
                if (c.mpihira.popularite <= pop)
                {
                    c2 = 1;
                }
            }
            else
            {
                if (c.mpihira.popularite < pop)
                {
                    c2 = 1;
                }
            }
        }
    }

    for (int i = 0; i < strlen(p[2]); i++)
    {
        if (p[2][i] == '>')
        {
            if (p[2][i + 1] == '=')
            {
                if (c.tempo >= tempo)
                {
                    c3 = 1;
                }
            }
            else
            {
                if (c.tempo > tempo)
                {
                    c3 = 1;
                }
            }
        }
        else if (p[2][i] == '<')
        {
            if (p[2][i + 1] == '=')
            {
                if (c.tempo <= tempo)
                {
                    c3 = 1;
                }
            }
            else
            {
                if (c.tempo < tempo)
                {
                    c3 = 1;
                }
            }
        }
    }

    if (c1 == 1 && c2 == 1 && c3 == 1)
    {
        return 1;
    }
    return 0;
}

int mamadikaSeconde(Heure duree)
{
    return (duree.heure * 3600 + duree.mn * 60 + duree.sec);
}

Heure mamadikaHeure(int seconde)
{
    Heure t;
    t.heure = seconde / 3600;
    t.mn = (seconde - t.heure * 3600) / 60;
    t.sec = seconde - (t.heure * 3600 + t.mn * 60);
    return t;
}

tranche manaoPlaylist(tranche t, hira *all, int nbHira)
{

    tranche play;
    play.listehira = malloc(nbHira * sizeof(hira));
    int count = 0;

    for (int i = 0; i < nbHira; i++)
    {
        if (manajaCritere(all[i], t.critere) == 1)
        {
            if (t.langue != NULL)
            {
                if (strcmp(t.langue, all[i].langue) == 0)
                {
                    play.listehira[count] = all[i];
                    count++;
                }
            }
            else
            {
                play.listehira[count] = all[i];
                count++;
            }
        }
    }
    play.nbhira = count;

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (mamadikaSeconde(play.listehira[j].duree) < mamadikaSeconde(play.listehira[j + 1].duree))
            {
                hira temp = play.listehira[j];
                play.listehira[j] = play.listehira[j + 1];
                play.listehira[j + 1] = temp;
            }
        }
    }

    int fotoana = mamadikaSeconde(t.heure_fin) - mamadikaSeconde(t.heure_debut);
    int total_duration = 0;
    int nb = 0;
    tranche retour;
    retour.listehira = malloc(play.nbhira * sizeof(hira));
    for (int i = 0; i < count; i++)
    {
        if (fotoana - total_duration >= mamadikaSeconde(play.listehira[i].duree))
        {
            total_duration += mamadikaSeconde(play.listehira[i].duree);
            retour.listehira[nb] = play.listehira[i];
            nb++;
        }
    }
    retour.nbhira = nb;

    char *ordre = split(t.critere)[3];
    for (int j = 0; j < strlen(ordre); j++)
    {
        if (ordre[j] == 'A' && ordre[j + 1] == 'S' && ordre[j + 2] == 'C')
        {
            for (int i = 0; i < nb - 1; i++)
            {
                for (int k = 0; k < nb - 1 - i; k++)
                {
                    if (retour.listehira[k].mpihira.popularite > retour.listehira[k + 1].mpihira.popularite)
                    {
                        hira temp = retour.listehira[k];
                        retour.listehira[k] = retour.listehira[k + 1];
                        retour.listehira[k + 1] = temp;
                    }
                }
            }
        }
        else if (ordre[j] == 'D' && ordre[j + 1] == 'E' && ordre[j + 2] == 'S')
        {
            for (int i = 0; i < nb - 1; i++)
            {
                for (int k = 0; k < nb - 1 - i; k++)
                {
                    if (retour.listehira[k].mpihira.popularite < retour.listehira[k + 1].mpihira.popularite)
                    {
                        hira temp = retour.listehira[k];
                        retour.listehira[k] = retour.listehira[k + 1];
                        retour.listehira[k + 1] = temp;
                    }
                }
            }
        }
    }

    return retour;
}

Heure totalTemps(tranche p)
{
    int seconde = 0;
    for (int i = 0; i < p.nbhira; i++)
    {
        seconde += mamadikaSeconde(p.listehira[i].duree);
    }
    Heure total_duree = mamadikaHeure(seconde);
    return total_duree;
}

void main()
{
    chanteur Oboy;
    Oboy.nom = malloc(10 * sizeof(char));
    Oboy.nom = strcpy(Oboy.nom, "Oboy");
    Oboy.popularite = 9;

    chanteur Rini;
    Rini.nom = malloc(10 * sizeof(char));
    Rini.nom = strcpy(Rini.nom, "Rini");
    Rini.popularite = 8;

    chanteur Mahaleo;
    Mahaleo.nom = malloc(10 * sizeof(char));
    Mahaleo.nom = strcpy(Mahaleo.nom, "Mahaleo");
    Mahaleo.popularite = 7;

    chanteur Ziak;
    Ziak.nom = malloc(10 * sizeof(char));
    Ziak.nom = strcpy(Ziak.nom, "Ziak");
    Ziak.popularite = 6;

    chanteur MariahCarey;
    MariahCarey.nom = malloc(15 * sizeof(char));
    MariahCarey.nom = strcpy(MariahCarey.nom, "Mariah Carey");
    MariahCarey.popularite = 10;

    chanteur Farakely;
    Farakely.nom = malloc(10 * sizeof(char));
    Farakely.nom = strcpy(Farakely.nom, "Farakely");
    Farakely.popularite = 7;

    chanteur Amir;
    Amir.nom = malloc(10 * sizeof(char));
    Amir.nom = strcpy(Amir.nom, "Amir");
    Amir.popularite = 8;

    chanteur D4vd;
    D4vd.nom = malloc(10 * sizeof(char));
    D4vd.nom = strcpy(D4vd.nom, "D4vd");
    D4vd.popularite = 6;

    chanteur NateTex;
    NateTex.nom = malloc(10 * sizeof(char));
    NateTex.nom = strcpy(NateTex.nom, "Nate Tex");
    NateTex.popularite = 5;

    chanteur Laufey;
    Laufey.nom = malloc(10 * sizeof(char));
    Laufey.nom = strcpy(Laufey.nom, "Laufey");
    Laufey.popularite = 7;

    hira TDB;
    TDB.titre = malloc(10 * sizeof(char));
    TDB.titre = strcpy(TDB.titre, "TDB");
    TDB.duree.heure = 0;
    TDB.duree.mn = 3;
    TDB.duree.sec = 0;
    TDB.langue = malloc(10 * sizeof(char));
    TDB.langue = strcpy(TDB.langue, "francais");
    TDB.mpihira = Oboy;
    TDB.sortie.annee = 2024;
    TDB.tempo = 8;

    hira MyFavorite;
    MyFavorite.titre = malloc(15 * sizeof(char));
    MyFavorite.titre = strcpy(MyFavorite.titre, "My Favorite");
    MyFavorite.duree.heure = 0;
    MyFavorite.duree.mn = 4;
    MyFavorite.duree.sec = 30;
    MyFavorite.langue = malloc(10 * sizeof(char));
    MyFavorite.langue = strcpy(MyFavorite.langue, "anglais");
    MyFavorite.mpihira = Rini;
    MyFavorite.sortie.annee = 2023;
    MyFavorite.tempo = 7;

    hira Ravoravo;
    Ravoravo.titre = malloc(10 * sizeof(char));
    Ravoravo.titre = strcpy(Ravoravo.titre, "Ravoravo");
    Ravoravo.duree.heure = 0;
    Ravoravo.duree.mn = 3;
    Ravoravo.duree.sec = 45;
    Ravoravo.langue = malloc(10 * sizeof(char));
    Ravoravo.langue = strcpy(Ravoravo.langue, "malgache");
    Ravoravo.mpihira = Mahaleo;
    Ravoravo.sortie.annee = 2022;
    Ravoravo.tempo = 6;

    hira Fixette;
    Fixette.titre = malloc(10 * sizeof(char));
    Fixette.titre = strcpy(Fixette.titre, "Fixette");
    Fixette.duree.heure = 0;
    Fixette.duree.mn = 2;
    Fixette.duree.sec = 50;
    Fixette.langue = malloc(10 * sizeof(char));
    Fixette.langue = strcpy(Fixette.langue, "francais");
    Fixette.mpihira = Ziak;
    Fixette.sortie.annee = 2021;
    Fixette.tempo = 5;

    hira Hero;
    Hero.titre = malloc(10 * sizeof(char));
    Hero.titre = strcpy(Hero.titre, "Hero");
    Hero.duree.heure = 0;
    Hero.duree.mn = 4;
    Hero.duree.sec = 0;
    Hero.langue = malloc(10 * sizeof(char));
    Hero.langue = strcpy(Hero.langue, "anglais");
    Hero.mpihira = MariahCarey;
    Hero.sortie.annee = 2020;
    Hero.tempo = 7;

    hira Fitiamangina;
    Fitiamangina.titre = malloc(15 * sizeof(char));
    Fitiamangina.titre = strcpy(Fitiamangina.titre, "Fitia mangina");
    Fitiamangina.duree.heure = 0;
    Fitiamangina.duree.mn = 3;
    Fitiamangina.duree.sec = 20;
    Fitiamangina.langue = malloc(10 * sizeof(char));
    Fitiamangina.langue = strcpy(Fitiamangina.langue, "malgache");
    Fitiamangina.mpihira = Farakely;
    Fitiamangina.sortie.annee = 2019;
    Fitiamangina.tempo = 6;

    hira Jaimetrop;
    Jaimetrop.titre = malloc(15 * sizeof(char));
    Jaimetrop.titre = strcpy(Jaimetrop.titre, "J'aime trop");
    Jaimetrop.duree.heure = 0;
    Jaimetrop.duree.mn = 3;
    Jaimetrop.duree.sec = 10;
    Jaimetrop.langue = malloc(10 * sizeof(char));
    Jaimetrop.langue = strcpy(Jaimetrop.langue, "francais");
    Jaimetrop.mpihira = Amir;
    Jaimetrop.sortie.annee = 2018;
    Jaimetrop.tempo = 7;

    hira RomanticHomicide;
    RomanticHomicide.titre = malloc(20 * sizeof(char));
    RomanticHomicide.titre = strcpy(RomanticHomicide.titre, "Romantic Homicide");
    RomanticHomicide.duree.heure = 0;
    RomanticHomicide.duree.mn = 4;
    RomanticHomicide.duree.sec = 15;
    RomanticHomicide.langue = malloc(10 * sizeof(char));
    RomanticHomicide.langue = strcpy(RomanticHomicide.langue, "anglais");
    RomanticHomicide.mpihira = D4vd;
    RomanticHomicide.sortie.annee = 2017;
    RomanticHomicide.tempo = 5;

    hira Mahatalanjona;
    Mahatalanjona.titre = malloc(10 * sizeof(char));
    Mahatalanjona.titre = strcpy(Mahatalanjona.titre, "Mahatalanjona");
    Mahatalanjona.duree.heure = 0;
    Mahatalanjona.duree.mn = 3;
    Mahatalanjona.duree.sec = 5;
    Mahatalanjona.langue = malloc(10 * sizeof(char));
    Mahatalanjona.langue = strcpy(Mahatalanjona.langue, "malgache");
    Mahatalanjona.mpihira = NateTex;
    Mahatalanjona.sortie.annee = 2016;
    Mahatalanjona.tempo = 6;

    hira Valentine;
    Valentine.titre = malloc(10 * sizeof(char));
    Valentine.titre = strcpy(Valentine.titre, "Valentine");
    Valentine.duree.heure = 0;
    Valentine.duree.mn = 3;
    Valentine.duree.sec = 55;
    Valentine.langue = malloc(10 * sizeof(char));
    Valentine.langue = strcpy(Valentine.langue, "anglais");
    Valentine.mpihira = Laufey;
    Valentine.sortie.annee = 2015;
    Valentine.tempo = 7;

    int nbhira = 10;
    hira *all = malloc(nbhira * sizeof(hira));
    all[0] = TDB;
    all[1] = MyFavorite;
    all[2] = Ravoravo;
    all[3] = Fixette;
    all[4] = Hero;
    all[5] = Fitiamangina;
    all[6] = Jaimetrop;
    all[7] = RomanticHomicide;
    all[8] = Mahatalanjona;
    all[9] = Valentine;

    tranche emission;
    emission.langue = malloc(10 * sizeof(char));
    emission.langue = NULL;
    emission.critere = malloc(100 * sizeof(char));
    emission.heure_debut.heure = 0;
    emission.heure_debut.mn = 0;
    emission.heure_debut.sec = 0;
    emission.heure_fin.heure = 24;
    emission.heure_fin.mn = 0;
    emission.heure_fin.sec = 0;
    emission.critere = strcpy(emission.critere, "annee >= 2000; popularite > 1; tempo >= 1; ordre : DESC");

    tranche now = manaoPlaylist(emission, all, nbhira);
    printf("%s\n", emission.critere);
    for (int i = 0; i < now.nbhira; i++)
    {
        printf("Titre : %s\nAnnee : %d\nDuree : %dmn %ds\nChanteur : %s\nPopularite : %d\nTempo : %d\n\n", now.listehira[i].titre, now.listehira[i].sortie.annee, now.listehira[i].duree.mn, now.listehira[i].duree.sec, now.listehira[i].mpihira.nom, now.listehira[i].mpihira.popularite, now.listehira[i].tempo);
    }
    Heure lapse = mamadikaHeure(mamadikaSeconde(emission.heure_fin) - mamadikaSeconde(emission.heure_debut)), dur = totalTemps(now);
    printf("Lapse Tranche : %dh %dmn %ds\n", lapse.heure, lapse.mn, lapse.sec);
    printf("Duree totale : %dh %dmn %ds\n", dur.heure, dur.mn, dur.sec);
}