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

            k = 0;
            j++;
        }
    }
    part[j][k] = '\0';
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
    chanteur Ambondrona;
    Ambondrona.nom = malloc(10 * sizeof(char));
    Ambondrona.nom = strcpy(Ambondrona.nom, "Ambondrona");
    Ambondrona.popularite = 9;

    chanteur Mage4;
    Mage4.nom = malloc(10 * sizeof(char));
    Mage4.nom = strcpy(Mage4.nom, "Mage4");
    Mage4.popularite = 8;

    chanteur Ceasar;
    Ceasar.nom = malloc(10 * sizeof(char));
    Ceasar.nom = strcpy(Ceasar.nom, "Ceasar");
    Ceasar.popularite = 6;

    chanteur Skaiz;
    Skaiz.nom = malloc(10 * sizeof(char));
    Skaiz.nom = strcpy(Skaiz.nom, "Skaiz");
    Skaiz.popularite = 7;

    hira TDB;
    TDB.titre = malloc(10 * sizeof(char));
    strcpy(TDB.titre, "Chanson 1");
    TDB.duree.heure = 0;
    TDB.duree.mn = 2;
    TDB.duree.sec = 30;
    TDB.langue = malloc(10 * sizeof(char));
    TDB.langue = strcpy(TDB.langue, "Malagasy");
    TDB.mpihira = Mage4;
    TDB.sortie.annee = 2019;
    TDB.tempo = 8;

    hira MyFavorite;
    MyFavorite.titre = malloc(15 * sizeof(char));
    strcpy(MyFavorite.titre, "Chanson 2");
    MyFavorite.duree.heure = 0;
    MyFavorite.duree.mn = 4;
    MyFavorite.duree.sec = 20;
    MyFavorite.langue = malloc(10 * sizeof(char));
    MyFavorite.langue = strcpy(MyFavorite.langue, "Malagasy");
    MyFavorite.mpihira = Ceasar;
    MyFavorite.sortie.annee = 2022;
    MyFavorite.tempo = 9;

    hira Ravoravo;
    Ravoravo.titre = malloc(10 * sizeof(char));
    strcpy(Ravoravo.titre, "Chanson 3");
    Ravoravo.duree.heure = 0;
    Ravoravo.duree.mn = 5;
    Ravoravo.duree.sec = 40;
    Ravoravo.langue = malloc(10 * sizeof(char));
    Ravoravo.langue = strcpy(Ravoravo.langue, "Malagasy");
    Ravoravo.mpihira = Mage4;
    Ravoravo.sortie.annee = 2021;
    Ravoravo.tempo = 7;

    hira Fixette;
    Fixette.titre = malloc(10 * sizeof(char));
    strcpy(Fixette.titre, "Chanson 4");
    Fixette.duree.heure = 0;
    Fixette.duree.mn = 3;
    Fixette.duree.sec = 16;
    Fixette.langue = malloc(10 * sizeof(char));
    Fixette.langue = strcpy(Fixette.langue, "Malagasy");
    Fixette.mpihira = Ambondrona;
    Fixette.sortie.annee = 2022;
    Fixette.tempo = 5;

    hira Hero;
    Hero.titre = malloc(10 * sizeof(char));
    strcpy(Hero.titre, "Chanson 5");
    Hero.duree.heure = 0;
    Hero.duree.mn = 3;
    Hero.duree.sec = 10;
    Hero.langue = malloc(10 * sizeof(char));
    Hero.langue = strcpy(Hero.langue, "Malagasy");
    Hero.mpihira = Skaiz;
    Hero.sortie.annee = 2021;
    Hero.tempo = 3;

    int nbhira = 5;
    hira *all = malloc(nbhira * sizeof(hira));
    all[0] = TDB;
    all[1] = MyFavorite;
    all[2] = Ravoravo;
    all[3] = Hero;
    all[4] = Fixette;

    tranche emission;
    emission.langue = malloc(10 * sizeof(char));
    emission.langue = "Malagasy";
    emission.critere = malloc(100 * sizeof(char));
    emission.heure_debut.heure = 12;
    emission.heure_debut.mn = 0;
    emission.heure_debut.sec = 0;
    emission.heure_fin.heure = 12;
    emission.heure_fin.mn = 15;
    emission.heure_fin.sec = 0;
    emission.critere = strcpy(emission.critere, "annee >= 2000; popularite > 1; tempo >= 1; ordre : ASC");

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