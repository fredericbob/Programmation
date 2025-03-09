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
    int valeur;
    struct Hira *suivant;
};
typedef struct Hira hira;

struct list_chanteur
{
    hira *list_chanteur;
    struct list_chanteur *suivant;
};
typedef struct list_chanteur List_chanteur;

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

void ajouter_fin(hira **lc, hira *nouveau)
{
    if (*lc == NULL)
    {
        *lc = nouveau;
    }
    hira *courant = *lc;
    while (courant->suivant != NULL)
    {
        courant = courant->suivant;
    }
    courant->suivant = nouveau;
    nouveau->suivant = NULL;
}

void ajout_fin_chanteur(hira **List_chanteur, hira *nv_ch)
{
    if (*List_chanteur == NULL)
    {
        *List_chanteur = nv_ch;
    }
    hira *ch_courant = *List_chanteur;
    while (ch_courant->suivant != NULL)
    {
        ch_courant = ch_courant->suivant;
    }
    ch_courant->suivant = nv_ch;
    nv_ch->suivant = NULL;
}

// void supr(hira **lc, const char *titre)
// {
//     if (*lc == NULL)
//     {
//         printf("La liste est vide, rien à supprimer.\n");
//         return;
//     }

//     hira *courant = *lc;
//     hira *precedent = NULL;

//     while (courant != NULL && strcmp(courant->titre, titre) != 0)
//     {
//         precedent = courant;
//         courant = courant->suivant;
//     }

//     if (courant == NULL)
//     {
//         printf("Chanson '%s' introuvable dans la liste.\n", titre);
//         return;
//     }

//     if (precedent == NULL)
//     {
//         *lc = courant->suivant;
//     }
//     else
//     {
//         precedent->suivant = courant->suivant;
//     }

//     free(courant->titre);
//     free(courant->langue);
//     free(courant);

//     printf("Chanson '%s' supprimee avec succes.\n", titre);
// }

void affichage(hira *lc, hira *List_chanteur)
{
    if (lc == NULL && List_chanteur == NULL)
    {
        printf(" liste est vide.\n");
    }

    hira *courant = lc;
    hira *ch_courant = List_chanteur;
    while (courant != NULL)
    {
        printf("titre : %s\n", courant->titre);
        courant = courant->suivant;
    }

    while (ch_courant != NULL)
    {
        printf("chanteur : %s\n", ch_courant->mpihira.nom);
        ch_courant = ch_courant->suivant;
    }
}

void affiche_separate(hira *lc, hira *List_chanteur)
{
    if (lc == NULL && List_chanteur == NULL)
    {
        printf(" liste est vide.\n");
    }

    hira *courant = lc;
    hira *ch_courant = List_chanteur;

    while (courant != NULL && ch_courant != NULL)
    {
        if (ch_courant->mpihira.nom && courant->mpihira.nom == 0)
        {
            printf("%s %s\n", ch_courant->mpihira.nom, courant->titre);
        }
    }
}
// void permutation(hira *lc)
// {
//     if (lc == NULL)
//         return;

//     int permute;
//     do
//     {
//         permute = 0;
//         hira *courant = lc;

//         while (courant->suivant != NULL)
//         {
//             if (courant->tempo > courant->suivant->tempo)
//             {
//                 char *tempTitre = courant->titre;
//                 courant->titre = courant->suivant->titre;
//                 courant->suivant->titre = tempTitre;

//                 Heure tempDuree = courant->duree;
//                 courant->duree = courant->suivant->duree;
//                 courant->suivant->duree = tempDuree;

//                 char *tempLangue = courant->langue;
//                 courant->langue = courant->suivant->langue;
//                 courant->suivant->langue = tempLangue;

//                 chanteur tempChanteur = courant->mpihira;
//                 courant->mpihira = courant->suivant->mpihira;
//                 courant->suivant->mpihira = tempChanteur;

//                 int tempTempo = courant->tempo;
//                 courant->tempo = courant->suivant->tempo;
//                 courant->suivant->tempo = tempTempo;

//                 int tempAnnee = courant->sortie.annee;
//                 courant->sortie.annee = courant->suivant->sortie.annee;
//                 courant->suivant->sortie.annee = tempAnnee;

//                 permute = 1;
//             }
//             courant = courant->suivant;
//         }
//     } while (permute);
// }

int main()
{
    hira *List_chanteur = NULL;
    hira *mage4 = malloc(sizeof(hira));
    mage4->mpihira.nom = strdup("mage4");
    mage4->mpihira.nom = strcpy(mage4->mpihira.nom, "mage4");
    mage4->mpihira.popularite = 8;
    mage4->suivant = NULL;
    ajout_fin_chanteur(&List_chanteur, mage4);

    hira *ceasar = malloc(sizeof(hira));
    ceasar->mpihira.nom = strdup("ceasar");
    ceasar->mpihira.nom = strcpy(ceasar->mpihira.nom, "ceasar");
    ceasar->mpihira.popularite = 6;
    ceasar->suivant = NULL;
    ajout_fin_chanteur(&List_chanteur, ceasar);

    hira *Ambondrona = malloc(sizeof(hira));
    Ambondrona->mpihira.nom = strdup("Ambondrona");
    Ambondrona->mpihira.nom = strcpy(Ambondrona->mpihira.nom, "Ambondrona");
    Ambondrona->mpihira.popularite = 9;
    Ambondrona->suivant = NULL;
    ajout_fin_chanteur(&List_chanteur, Ambondrona);

    hira *skaiz = malloc(sizeof(hira));
    skaiz->mpihira.nom = strdup("skaiz");
    skaiz->mpihira.nom = strcpy(skaiz->mpihira.nom, "skaiz");
    skaiz->mpihira.popularite = 7;
    skaiz->suivant = NULL;
    ajout_fin_chanteur(&List_chanteur, skaiz);

    hira *lc = NULL;
    hira *chanson1 = malloc(sizeof(hira));
    chanson1->titre = strdup("chanson1");
    chanson1->duree = (Heure){0, 2, 30};
    chanson1->langue = strdup("malagasy");
    chanson1->mpihira = (chanteur){strdup("mage4"), 8};
    chanson1->tempo = 8;
    chanson1->sortie.annee = 2019;
    chanson1->suivant = NULL;
    ajouter_fin(&lc, chanson1);

    hira *chanson2 = malloc(sizeof(hira));
    chanson2->titre = strdup("chanson2");
    chanson2->duree = (Heure){0, 4, 20};
    chanson2->langue = strdup("malagasy");
    chanson2->mpihira = (chanteur){strdup("ceasar"), 6};
    chanson2->tempo = 9;
    chanson2->sortie.annee = 2022;
    chanson2->suivant = NULL;
    ajouter_fin(&lc, chanson2);

    hira *chanson3 = malloc(sizeof(hira));
    chanson3->titre = strdup("chanson3");
    chanson3->duree = (Heure){0, 5, 40};
    chanson3->langue = strdup("malagasy");
    chanson3->mpihira = (chanteur){strdup("mage4"), 8};
    chanson3->tempo = 7;
    chanson3->sortie.annee = 2021;
    chanson3->suivant = NULL;
    ajouter_fin(&lc, chanson3);

    hira *chanson4 = malloc(sizeof(hira));
    chanson4->titre = strdup("chanson4");
    chanson4->duree = (Heure){0, 3, 16};
    chanson4->langue = strdup("malagasy");
    chanson4->mpihira = (chanteur){strdup("Ambondrona"), 9};
    chanson4->tempo = 5;
    chanson4->sortie.annee = 2022;
    chanson4->suivant = NULL;
    ajouter_fin(&lc, chanson4);

    hira *chanson5 = malloc(sizeof(hira));
    chanson5->titre = strdup("chanson5");
    chanson5->duree = (Heure){0, 3, 10};
    chanson5->langue = strdup("malagasy");
    chanson5->mpihira = (chanteur){strdup("skaiz"), 7};
    chanson5->tempo = 7;
    chanson5->sortie.annee = 2021;
    chanson5->suivant = NULL;
    ajouter_fin(&lc, chanson5);

    hira *chanson6 = malloc(sizeof(hira));
    chanson6->titre = strdup("chanson6");
    chanson6->duree = (Heure){0, 3, 10};
    chanson6->langue = strdup("malagasy");
    chanson6->mpihira = (chanteur){strdup("skaiz"), 7};
    chanson6->tempo = 4;
    chanson6->sortie.annee = 2022;
    chanson6->suivant = NULL;
    ajouter_fin(&lc, chanson6);

    hira *chanson7 = malloc(sizeof(hira));
    chanson7->titre = strdup("chanson7");
    chanson7->duree = (Heure){0, 3, 16};
    chanson7->langue = strdup("malagasy");
    chanson7->mpihira = (chanteur){strdup("Ambondrona"), 9};
    chanson7->tempo = 6;
    chanson7->sortie.annee = 2020;
    chanson7->suivant = NULL;
    ajouter_fin(&lc, chanson7);

    hira *chanson8 = malloc(sizeof(hira));
    chanson8->titre = strdup("chanson8");
    chanson8->duree = (Heure){0, 4, 20};
    chanson8->langue = strdup("malagasy");
    chanson8->mpihira = (chanteur){strdup("ceasar"), 6};
    chanson8->tempo = 10;
    chanson8->sortie.annee = 2021;
    chanson8->suivant = NULL;
    ajouter_fin(&lc, chanson8);

    tranche plage;
    plage.langue = malloc(10 * sizeof(char));
    plage.langue = "malagasy";
    plage.critere = malloc(100 * sizeof(char));
    plage.heure_debut.heure = 12;
    plage.heure_debut.mn = 0;
    plage.heure_debut.sec = 0;
    plage.heure_fin.heure = 12;
    plage.heure_fin.mn = 15;
    plage.heure_fin.sec = 0;
    plage.critere = strcpy(plage.critere, "annee > 2020; popularite > 5; tempo > 4; ordre : DESC");

    // tranche now = manaoPlaylist(plage, all, nbhira);
    // printf("ETU 004124\n");
    // printf("%s\n", plage.critere);
    // for (int i = 0; i < now.nbhira; i++)
    // {
    //     printf("Titre : %s\nAnnee : %d\nDuree : %dmn %ds\nChanteur : %s\nPopularite : %d\nTempo : %d\n\n", now.listehira[i].titre, now.listehira[i].sortie.annee, now.listehira[i].duree.mn, now.listehira[i].duree.sec, now.listehira[i].mpihira.nom, now.listehira[i].mpihira.popularite, now.listehira[i].tempo);
    // }
    // Heure lapse = mamadikaHeure(mamadikaSeconde(plage.heure_fin) - mamadikaSeconde(plage.heure_debut)), dur = totalTemps(now);
    // printf("Lapse Tranche : %dh %dmn %ds\n", lapse.heure, lapse.mn, lapse.sec);
    // printf("Duree totale : %dh %dmn %ds\n", dur.heure, dur.mn, dur.sec);

    // Affichage initial
    printf("Liste chaine :\n");
    affichage(lc, List_chanteur);

    printf("liste chaine dans liste chaine:\n");
    affiche_separate(lc, List_chanteur);

    // // Tri
    // permutation(lc);
    // printf("Liste apres tri :\n");
    // affichage(lc);
    // // Suppression d'une chanson
    // printf("Liste avant suppression :\n");
    // affichage(lc);

    // supr(&lc, "chanson5");

    // printf("Liste apres suppression :\n");
    // affichage(lc);

    free(mage4->mpihira.nom);
    free(mage4);
    free(ceasar->mpihira.nom);
    free(ceasar);
    free(Ambondrona->mpihira.nom);
    free(Ambondrona);
    free(skaiz->mpihira.nom);
    free(skaiz);

    return 0;
}