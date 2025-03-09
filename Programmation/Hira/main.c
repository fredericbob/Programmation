#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct chanteur
{
    char *noms;
    int popularite;
};
typedef struct chanteur Chanteur;

struct duree
{
    int heure;
    int minute;
    int seconde;
};
typedef struct duree Duree;

struct date
{
    int annee;
    int mois;
    int jour;
};
typedef struct date Date;

struct hira
{
    char *titre;
    char *langue;
    Chanteur CHANTEUR;
    int tempo;
    Duree dureeduree;
    Date date_sortie;
};
typedef struct hira Hira;

struct tranche
{
    int jour; // 1...7 (lundi...dimanche)
    Duree heure_debut;
    Duree heure_fin;
    char *langue;
    char *critere; // " annee<2020; popularite>=4; tempo<2 " --> type phrase
};
typedef struct tranche Tranche;

int cast(char *nombre)
{
    int resultat = 0;
    int i = 0;
    while (nombre[i] != '\0')
    {
        resultat = resultat * 10 + (nombre[i] - '0');
        i++;
    }
    return resultat;
}

int convertion_seconde(Duree duree)
{
    return duree.heure * 3600 + duree.minute * 60 + duree.seconde;
}

Duree convertion_heure(int secondes)
{

    Duree result;
    result.heure = secondes / 3600;

    secondes = secondes % 3600;

    result.minute = secondes / 60;

    result.seconde = secondes % 60;

    return result;
}
Hira hira[100]; // Tableau global d'exemple
                // Tableau d'indices

// Fonctions de comparaison
int compare_asc(const void *a, const void *b)
{
    int index_a = *(const int *)a;
    int index_b = *(const int *)b;

    return hira[index_a].CHANTEUR.popularite - hira[index_b].CHANTEUR.popularite;
}

int compare_desc(const void *a, const void *b)
{
    int index_a = *(const int *)a;
    int index_b = *(const int *)b;

    return hira[index_b].CHANTEUR.popularite - hira[index_a].CHANTEUR.popularite;
}
void traitementPhrase(char *nouveauphrase, int *annee, int *popularite, int *tempo, char *cond_annee, char *cond_popularite, char *cond_tempo, char *ordre)
{

    int i = 0;
    while (nouveauphrase[i] != '\0')
    {
        if (strncmp(&nouveauphrase[i], "ordre:", 6) == 0)
        {
            i += 6;                         // Avancer après "ordre:"
            while (nouveauphrase[i] == ' ') // Ignorer les espaces
                i++;

            if (strncmp(&nouveauphrase[i], "Asc", 3) == 0)
            {
                strcpy(ordre, "Asc");
                i += 3;
            }
            else if (strncmp(&nouveauphrase[i], "Desc", 4) == 0)
            {
                strcpy(ordre, "Desc");
                i += 4;
            }
            continue;
        }
        if (nouveauphrase[i] == '>' || nouveauphrase[i] == '<')
        {
            int j = i;

            if (nouveauphrase[i + 1] == '=')
            {
                i += 2;
            }
            else
            {
                i++;
            }

            int k = j - 1;
            while (k >= 0 && !isspace(nouveauphrase[k]) && nouveauphrase[k] != ';')
            {
                k--;
            }

            char motAvantOperateur[100];
            int m = 0;
            for (int l = k + 1; l < j; l++)
            {
                motAvantOperateur[m++] = nouveauphrase[l];
            }
            motAvantOperateur[m] = '\0';

            while (nouveauphrase[i] == ' ')
                i++;

            if (isdigit(nouveauphrase[i]))
            {
                char nombre[100];
                int n = 0;

                while (nouveauphrase[i] != '\0' && isdigit(nouveauphrase[i]))
                {
                    nombre[n++] = nouveauphrase[i++];
                }
                nombre[n] = '\0';

                int val = atoi(nombre);

                if (strstr(motAvantOperateur, "annee") != NULL)
                {
                    *annee = val;

                    if (nouveauphrase[j + 1] == '=')
                    {
                        strcpy(cond_annee, (nouveauphrase[j] == '>') ? ">=" : "<=");
                    }
                    else
                    {
                        strcpy(cond_annee, (nouveauphrase[j] == '>') ? ">" : "<");
                    }
                }
                else if (strstr(motAvantOperateur, "popularite") != NULL)
                {
                    *popularite = val;

                    if (nouveauphrase[j + 1] == '=')
                    {
                        strcpy(cond_popularite, (nouveauphrase[j] == '>') ? ">=" : "<=");
                    }
                    else
                    {
                        strcpy(cond_popularite, (nouveauphrase[j] == '>') ? ">" : "<");
                    }
                }
                else if (strstr(motAvantOperateur, "tempo") != NULL)
                {
                    *tempo = val;

                    if (nouveauphrase[j + 1] == '=')
                    {
                        strcpy(cond_tempo, (nouveauphrase[j] == '>') ? ">=" : "<=");
                    }
                    else
                    {
                        strcpy(cond_tempo, (nouveauphrase[j] == '>') ? ">" : "<");
                    }
                }
            }
        }
        else
        {
            i++;
        }
    }
}

int recherche(Hira *hira, int annee, int popularite, int tempo, int taille, char *cond_annee, char *cond_popularite, char *cond_tempo, int *resultats, Tranche *tranche, int nbtranche, char *ordre)
{

    int count = 0;

    for (int i = 0; i < taille; i++)
    {

        int match = 1;

        if (strcmp(cond_annee, "<") == 0 && hira[i].date_sortie.annee >= annee)
            match = 0;
        else if (strcmp(cond_annee, ">") == 0 && hira[i].date_sortie.annee <= annee)
            match = 0;
        else if (strcmp(cond_annee, "<=") == 0 && hira[i].date_sortie.annee > annee)
            match = 0;
        else if (strcmp(cond_annee, ">=") == 0 && hira[i].date_sortie.annee < annee)
            match = 0;

        if (strcmp(cond_popularite, "<") == 0 && hira[i].CHANTEUR.popularite >= popularite)
            match = 0;
        else if (strcmp(cond_popularite, ">") == 0 && hira[i].CHANTEUR.popularite <= popularite)
            match = 0;
        else if (strcmp(cond_popularite, "<=") == 0 && hira[i].CHANTEUR.popularite > popularite)
            match = 0;
        else if (strcmp(cond_popularite, ">=") == 0 && hira[i].CHANTEUR.popularite < popularite)
            match = 0;

        if (strcmp(cond_tempo, "<") == 0 && hira[i].tempo >= tempo)
            match = 0;
        else if (strcmp(cond_tempo, ">") == 0 && hira[i].tempo <= tempo)
            match = 0;
        else if (strcmp(cond_tempo, "<=") == 0 && hira[i].tempo > tempo)
            match = 0;
        else if (strcmp(cond_tempo, ">=") == 0 && hira[i].tempo < tempo)
            match = 0;

        int tranche_match = 0; // Variable pour vérifier si une tranche correspond
        for (int j = 0; j < nbtranche; j++)
        {
            if (tranche[j].langue == NULL || strcmp(hira[i].langue, tranche[j].langue) == 0)
            {
                tranche_match = 1; // Correspondance trouvée
            }
        }
        if (!tranche_match) // Si aucune langue correspondante n'a été trouvée
            match = 0;
        if (match)
        {

            resultats[count++] = i;
        }
    }
    if (strcmp(ordre, "Asc") == 0)
    {
        printf("Avant tri :\n");
        for (int i = 0; i < count; i++)
        {
            printf("Indice : %d, Popularité : %d\n", resultats[i], hira[resultats[i]].CHANTEUR.popularite);
        }

        qsort(resultats, count, sizeof(int), compare_asc);
        printf("Avant tri :\n");
        for (int i = 0; i < count; i++)
        {
            printf("Indice : %d, Popularité : %d\n", resultats[i], hira[resultats[i]].CHANTEUR.popularite);
        }
    }
    else if (strcmp(ordre, "Desc") == 0)
    {
        qsort(resultats, count, sizeof(int), compare_desc);
    }
    else
    {
        printf("Ordre invalide.\n");
        return 1;
    }

    return count;
}
int hira_tranche(Hira *playlist, int n, Tranche *tranches, int nb_tranches, int jour)
{
    printf("=== Planification des chansons pour le jour %d ===\n", jour);

    for (int t = 0; t < nb_tranches; t++)
    {

        // Vérifie si la tranche correspond au jour demandé
        if (tranches[t].jour != jour)
            continue;

        Tranche tranche = tranches[t];
        Duree debut = tranche.heure_debut;
        Duree fin = tranche.heure_fin;
        int tranche_max = convertion_seconde(fin) - convertion_seconde(debut);
        int sum = 0;

        printf("Tranche horaire : %02d:%02d:%02d a %02d:%02d:%02d\n",
               debut.heure, debut.minute, debut.seconde,
               fin.heure, fin.minute, fin.seconde);

        // Préparer les critères de recherche
        int annee = 0, popularite = 0, tempo = 0;
        char cond_annee[4] = "", cond_popularite[4] = "", cond_tempo[4] = "";
        char ordre[5] = "";

        if (tranche.critere != NULL)
        {
            traitementPhrase(tranche.critere, &annee, &popularite, &tempo, cond_annee, cond_popularite, cond_tempo, ordre);
        }

        int *resultats = (int *)malloc(n * sizeof(int));
        if (resultats == NULL)
        {
            fprintf(stderr, "Erreur : allocation mémoire échouée pour 'resultats'.\n");
            return -1;
        }

        int nb_resultats = recherche(playlist, annee, popularite, tempo, n, cond_annee, cond_popularite, cond_tempo, resultats, tranches, nb_tranches, ordre);

        for (int i = 0; i < nb_resultats; i++)
        {
            int index = resultats[i];
            int chanson_duree = convertion_seconde(playlist[index].dureeduree);

            if (sum + chanson_duree <= tranche_max)
            {

                if (tranche.langue != NULL && strcmp(tranche.langue, playlist[index].langue) != 0)
                    continue;

                sum += chanson_duree;
                printf("- %s (%02d:%02d:%02d, sortie en %04d-%02d-%02d)\n",
                       playlist[index].titre,
                       playlist[index].dureeduree.heure,
                       playlist[index].dureeduree.minute,
                       playlist[index].dureeduree.seconde,
                       playlist[index].date_sortie.annee,
                       playlist[index].date_sortie.mois,
                       playlist[index].date_sortie.jour);
            }
            else
            {
                printf("La chanson '%s' depasse la dure de la tranche.\n", playlist[index].titre);
                break;
            }
        }

        printf("Dure totale de la tranche : %02d:%02d:%02d\n",
               convertion_heure(sum).heure,
               convertion_heure(sum).minute,
               convertion_heure(sum).seconde);

        if (sum > tranche_max)
        {
            printf("Attention : la duree totale dépasse la tranche autorisée !\n");
        }

        printf("\n");

        free(resultats);
    }

    return 0;
}
void annee_sortie(Hira h, Date d)
{
    for (int i = 2020; i < 2025; i++)
    {
        if (d.annee == h.date_sortie.annee)
        {
            printf("%s\n", h.titre);
        }
    }
}

int main()
{
    int taille = 10;

    Hira *hira = (Hira *)malloc(taille * sizeof(Hira));
    // hira[0].titre = "Chanson 1";
    // hira[0].CHANTEUR.noms = "Chanteur 1"; // Correspond à `chanteurs[0]`
    // hira[0].tempo = 7;
    // hira[0].dureeduree.heure = 0;
    // hira[0].dureeduree.minute = 3;
    // hira[0].dureeduree.seconde = 30;
    // hira[0].date_sortie.jour = 12;
    // hira[0].date_sortie.mois = 3;
    // hira[0].date_sortie.annee = 2020;
    // hira[0].langue = "Français";

    // hira[1].titre = "Chanson 2";
    // hira[1].CHANTEUR.noms = "Chanteur 2";
    // hira[1].tempo = 5;
    // hira[1].dureeduree.heure = 0;
    // hira[1].dureeduree.minute = 4;
    // hira[1].dureeduree.seconde = 0;
    // hira[1].date_sortie.jour = 8;
    // hira[1].date_sortie.mois = 7;
    // hira[1].date_sortie.annee = 2018;
    // hira[1].langue = "Anglais";

    // hira[2].titre = "Chanson 3";
    // hira[2].CHANTEUR.noms = "Chanteur 3";
    // hira[2].tempo = 9;
    // hira[2].dureeduree.heure = 0;
    // hira[2].dureeduree.minute = 2;
    // hira[2].dureeduree.seconde = 45;
    // hira[2].date_sortie.jour = 15;
    // hira[2].date_sortie.mois = 6;
    // hira[2].date_sortie.annee = 2021;
    // hira[2].langue = "Français";

    // hira[3].titre = "Chanson 4";
    // hira[3].CHANTEUR.noms = "Chanteur 4";
    // hira[3].tempo = 8;
    // hira[3].dureeduree.heure = 0;
    // hira[3].dureeduree.minute = 5;
    // hira[3].dureeduree.seconde = 15;
    // hira[3].date_sortie.jour = 1;
    // hira[3].date_sortie.mois = 1;
    // hira[3].date_sortie.annee = 2019;
    // hira[3].langue = "Français";

    // hira[4].titre = "Chanson 5";
    // hira[4].CHANTEUR.noms = "Chanteur 5";
    // hira[4].tempo = 4;
    // hira[4].dureeduree.heure = 0;
    // hira[4].dureeduree.minute = 3;
    // hira[4].dureeduree.seconde = 0;
    // hira[4].date_sortie.jour = 20;
    // hira[4].date_sortie.mois = 10;
    // hira[4].date_sortie.annee = 2017;
    // hira[4].langue = "Anglais";

    // hira[5].titre = "Chanson 6";
    // hira[5].CHANTEUR.noms = "Chanteur 6";
    // hira[5].tempo = 10;
    // hira[5].dureeduree.heure = 0;
    // hira[5].dureeduree.minute = 6;
    // hira[5].dureeduree.seconde = 10;
    // hira[5].date_sortie.jour = 14;
    // hira[5].date_sortie.mois = 2;
    // hira[5].date_sortie.annee = 2022;
    // hira[5].langue = "Français";

    // hira[6].titre = "Chanson 7";
    // hira[6].CHANTEUR.noms = "Chanteur 7";
    // hira[6].tempo = 3;
    // hira[6].dureeduree.heure = 0;
    // hira[6].dureeduree.minute = 3;
    // hira[6].dureeduree.seconde = 20;
    // hira[6].date_sortie.jour = 3;
    // hira[6].date_sortie.mois = 3;
    // hira[6].date_sortie.annee = 2016;
    // hira[6].langue = "Anglais";

    // hira[7].titre = "Chanson 8";
    // hira[7].CHANTEUR.noms = "Chanteur 8";
    // hira[7].tempo = 9;
    // hira[7].dureeduree.heure = 0;
    // hira[7].dureeduree.minute = 2;
    // hira[7].dureeduree.seconde = 50;
    // hira[7].date_sortie.jour = 7;
    // hira[7].date_sortie.mois = 5;
    // hira[7].date_sortie.annee = 2020;
    // hira[7].langue = "Français";

    // hira[8].titre = "Chanson 9";
    // hira[8].CHANTEUR.noms = "Chanteur 9";
    // hira[8].tempo = 6;
    // hira[8].dureeduree.heure = 0;
    // hira[8].dureeduree.minute = 4;
    // hira[8].dureeduree.seconde = 10;
    // hira[8].date_sortie.jour = 22;
    // hira[8].date_sortie.mois = 11;
    // hira[8].date_sortie.annee = 2018;
    // hira[8].langue = "Anglais";

    // hira[9].titre = "Chanson 10";
    // hira[9].CHANTEUR.noms = "Chanteur 10";
    // hira[9].tempo = 7;
    // hira[9].dureeduree.heure = 0;
    // hira[9].dureeduree.minute = 5;
    // hira[9].dureeduree.seconde = 5;
    // hira[9].date_sortie.jour = 10;
    // hira[9].date_sortie.mois = 4;
    // hira[9].date_sortie.annee = 2020;
    // hira[9].langue = "Français";

    hira[0].titre = "kiko";
    hira[0].CHANTEUR.noms = "micka";
    hira[0].langue = "malagasy";
    hira[0].CHANTEUR.popularite = 4;
    hira[0].tempo = 3;
    hira[0].dureeduree.heure = 0.0;
    hira[0].dureeduree.minute = 2.0;
    hira[0].dureeduree.seconde = 30.0;
    hira[0].date_sortie.jour = 2;
    hira[0].date_sortie.mois = 5;
    hira[0].date_sortie.annee = 2020;

    hira[1].titre = "baba";
    hira[1].CHANTEUR.noms = "bob";
    hira[1].langue = "malagasy";
    hira[1].CHANTEUR.popularite = 7;
    hira[1].tempo = 2;
    hira[1].dureeduree.heure = 0;
    hira[1].dureeduree.minute = 3;
    hira[1].dureeduree.seconde = 20;
    hira[1].date_sortie.jour = 7;
    hira[1].date_sortie.mois = 6;
    hira[1].date_sortie.annee = 2022;

    hira[2].titre = "popo";
    hira[2].CHANTEUR.noms = "manou";
    hira[2].langue = "francais";
    hira[2].CHANTEUR.popularite = 8;
    hira[2].tempo = 3;
    hira[2].dureeduree.heure = 0;
    hira[2].dureeduree.minute = 4;
    hira[2].dureeduree.seconde = 28;
    hira[2].date_sortie.jour = 4;
    hira[2].date_sortie.mois = 11;
    hira[2].date_sortie.annee = 2002;

    hira[3].titre = "fifi";
    hira[3].CHANTEUR.noms = "lola";
    hira[3].langue = "francais";
    hira[3].CHANTEUR.popularite = 5;
    hira[3].tempo = 6;
    hira[3].dureeduree.heure = 0;
    hira[3].dureeduree.minute = 2;
    hira[3].dureeduree.seconde = 45;
    hira[3].date_sortie.jour = 1;
    hira[3].date_sortie.mois = 9;
    hira[3].date_sortie.annee = 2018;

    hira[4].titre = "zaza";
    hira[4].CHANTEUR.noms = "tina";
    hira[4].langue = "francais";
    hira[4].CHANTEUR.popularite = 6;
    hira[4].tempo = 4;
    hira[4].dureeduree.heure = 0;
    hira[4].dureeduree.minute = 3;
    hira[4].dureeduree.seconde = 15;
    hira[4].date_sortie.jour = 2;
    hira[4].date_sortie.mois = 2;
    hira[4].date_sortie.annee = 2015;

    hira[5].titre = "lolipop";
    hira[5].CHANTEUR.noms = "mario";
    hira[5].langue = "anglais";
    hira[5].CHANTEUR.popularite = 9;
    hira[5].tempo = 7;
    hira[5].dureeduree.heure = 0;
    hira[5].dureeduree.minute = 3;
    hira[5].dureeduree.seconde = 50;
    hira[5].date_sortie.jour = 6;
    hira[5].date_sortie.mois = 3;
    hira[5].date_sortie.annee = 2021;

    hira[6].titre = "momo";
    hira[6].CHANTEUR.noms = "sara";
    hira[6].langue = "anglais";
    hira[6].CHANTEUR.popularite = 3;
    hira[6].tempo = 2;
    hira[6].dureeduree.heure = 0;
    hira[6].dureeduree.minute = 2;
    hira[6].dureeduree.seconde = 10;
    hira[6].date_sortie.jour = 5;
    hira[6].date_sortie.mois = 12;
    hira[6].date_sortie.annee = 2019;

    hira[7].titre = "rocky";
    hira[7].CHANTEUR.noms = "tom";
    hira[7].langue = "anglais";
    hira[7].CHANTEUR.popularite = 8;
    hira[7].tempo = 8;
    hira[7].dureeduree.heure = 0;
    hira[7].dureeduree.minute = 5;
    hira[7].dureeduree.seconde = 20;
    hira[7].date_sortie.jour = 4;
    hira[7].date_sortie.mois = 7;
    hira[7].date_sortie.annee = 2010;

    hira[8].titre = "chacha";
    hira[8].CHANTEUR.noms = "lily";
    hira[8].langue = "francais";
    hira[8].CHANTEUR.popularite = 7;
    hira[8].tempo = 5;
    hira[8].dureeduree.heure = 0;
    hira[8].dureeduree.minute = 3;
    hira[8].dureeduree.seconde = 40;
    hira[8].date_sortie.jour = 7;
    hira[8].date_sortie.mois = 10;
    hira[8].date_sortie.annee = 2023;

    hira[9].titre = "titi";
    hira[9].CHANTEUR.noms = "jerry";
    hira[9].langue = "malagasy";
    hira[9].CHANTEUR.popularite = 2;
    hira[9].tempo = 4;
    hira[9].dureeduree.heure = 0;
    hira[9].dureeduree.minute = 2;
    hira[9].dureeduree.seconde = 50;
    hira[9].date_sortie.jour = 5;
    hira[9].date_sortie.mois = 3;
    hira[9].date_sortie.annee = 2016;

    int nb_tranches = 7;
    Tranche *tranches = (Tranche *)malloc(nb_tranches * sizeof(Tranche));
    if (tranches == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire pour les tranches.\n");
        free(hira);
        return -1;
    }

    // jour 1
    tranches[0].heure_debut = (Duree){8, 0, 0};
    tranches[0].heure_fin = (Duree){8, 30, 0};
    tranches[0].jour = 1;
    tranches[0].critere = "annee>2009;popularite<10;tempo>4;ordre:Asc";
    tranches[0].langue = NULL;

    // Jour 2
    tranches[1].heure_debut = (Duree){9, 0, 0};
    tranches[1].heure_fin = (Duree){11, 0, 0};
    tranches[1].jour = 2;
    tranches[1].critere = "annee<=2022;popularite<10;tempo<10;ordre:ascendant";
    tranches[1].langue = "francais";
    // Jour 3
    tranches[2].heure_debut = (Duree){15, 0, 0};
    tranches[2].heure_fin = (Duree){17, 0, 0};
    tranches[2].jour = 3;
    tranches[2].critere = "annee<2024;popularite>10;tempo<10";
    tranches[2].langue = "anglais"; // Toutes les langues autorisées

    // Jour 4
    tranches[3].heure_debut = (Duree){10, 0, 0};
    tranches[3].heure_fin = (Duree){12, 0, 0};
    tranches[3].jour = 4;
    tranches[3].critere = "annee<2020;popularite<=8;tempo>=6";
    tranches[3].langue = "anglais";
    // Jour 5
    tranches[4].heure_debut = (Duree){16, 0, 0};
    tranches[4].heure_fin = (Duree){18, 0, 0};
    tranches[4].jour = 5;
    tranches[4].critere = "annee>=2018;popularite<10;tempo>4";
    tranches[4].langue = NULL;

    // Jour 6
    tranches[5].heure_debut = (Duree){7, 30, 0};
    tranches[5].heure_fin = (Duree){9, 30, 0};
    tranches[5].jour = 6;
    tranches[5].critere = "annee<2025;popularite<=6;tempo<=7";
    tranches[5].langue = "espagnol";
    // Jour 7
    tranches[6].heure_debut = (Duree){13, 30, 0};
    tranches[6].heure_fin = (Duree){15, 30, 0};
    tranches[6].jour = 7;
    tranches[6].critere = "annee>2019;popularite>=4;tempo>=5;";
    tranches[6].langue = NULL;

    // // Jour 5
    // tranches[8].heure_debut = (Duree){8, 0, 0};
    // tranches[8].heure_fin = (Duree){10, 0, 0};
    // tranches[8].jour = 8;
    // tranches[8].critere = "annee<=2020;popularite<=9;tempo<=8";
    // tranches[8].langue = "italien";

    // tranches[9].heure_debut = (Duree){14, 0, 0};
    // tranches[9].heure_fin = (Duree){16, 0, 0};
    // tranches[9].jour = ;
    // tranches[9].critere = "annee>2020;popularite>6;tempo>7";
    // tranches[9].langue = NULL;

    // // Jour 6
    // tranches[10].heure_debut = (Duree){9, 0, 0};
    // tranches[10].heure_fin = (Duree){11, 0, 0};
    // tranches[10].jour = 6;
    // tranches[10].critere = "annee<2019;popularite<=7;tempo<6";
    // tranches[10].langue = "portugais";

    // tranches[11].heure_debut = (Duree){15, 0, 0};
    // tranches[11].heure_fin = (Duree){17, 0, 0};
    // tranches[11].jour = 6;
    // tranches[11].critere = "annee>=2020;popularite>=8;tempo>=9";
    // tranches[11].langue = NULL;

    // // Jour 7
    // tranches[12].heure_debut = (Duree){8, 0, 0};
    // tranches[12].heure_fin = (Duree){10, 0, 0};
    // tranches[12].jour = 7;
    // tranches[12].critere = "annee<=2017;popularite>5;tempo<=6";
    // tranches[12].langue = "allemand";

    // tranches[13].heure_debut = (Duree){14, 0, 0};
    // tranches[13].heure_fin = (Duree){16, 0, 0};
    // tranches[13].jour = 7;
    // tranches[13].critere = "annee>2018;popularite>=6;tempo>=8";
    // tranches[13].langue = NULL;

    int jour = 1;

    hira_tranche(hira, taille, tranches, nb_tranches, jour);

    free(hira);
    free(tranches);

    return 0;

    free(hira);

    return 0;
}