#include <stdio.h>
#include <stdlib.h>

char *c[] = {
    "4cent", "9deux-cents", "9trois-cents", "10quatre-cents",
    "8cinq-cents", "8six-cents", "9sept-cents", "9huit-cents", "8neuf-cents"};

char *mille = "5mille";
char *million = "7million";

void ajoutTaille(char **i, int taille)
{
    for (int j = 0; j < taille; j++)
    {
        int tailleC = 0;
        char *str = i[j];
        while (*str != '\0')
        {
            tailleC++;
            str++;
        }
        char *nouveauTableau = (char *)malloc((tailleC + 2) * sizeof(char));
        nouveauTableau[0] = '0' + tailleC;
        char *tv = nouveauTableau + 1;
        char *a = i[j];
        while (*a != '\0')
        {
            *tv = *a;
            a++;
            tv++;
        }
        *tv = '\0';
        i[j] = nouveauTableau;
    }
}

void affiche_mot(char **i, int n, char **j, char **c, char *mille, char *million)
{
    if (n < 20)
    {
        printf("%s", i[n] + 1);
    }
    else if (n >= 20 && n < 70)
    {
        int dizaine = n / 10;
        int unite = n - (dizaine * 10);
        printf("%s", j[dizaine - 2] + 1);
        if (unite > 0)
        {
            printf("-%s", i[unite] + 1);
        }
    }
    else if (n >= 70 && n < 80)
    {
        int unite = n - 70;
        if (unite == 0)
        {
            printf("%s", j[5] + 2);
        }
        else
        {
            printf("%s", j[4] + 1);
        }
        if (unite > 0)
        {
            printf("-%s", i[unite + 10] + 1);
        }
    }
    else if (n >= 80 && n < 100)
    {
        int unite = n - 80;
        if (unite == 0)
        {
            printf("%s", j[7] + 2);
        }
        else
        {
            printf("%s", j[6] + 2);
        }

        if (unite > 0)
        {
            printf("-%s", i[unite] + 1);
        }
    }
    else if (n >= 100 && n < 1000)
    {
        int centaine = n / 100;
        int reste = n - (centaine * 100);
        printf("%s", c[centaine - 1] + 1);
        if (reste > 0)
        {
            printf("-");
            affiche_mot(i, reste, j, c, mille, million);
        }
    }

    else if (n >= 1000 && n < 1000000)
    {
        int millier = n / 1000;
        int reste = n - (millier * 1000);
        if (millier > 1)
        {
            affiche_mot(i, millier, j, c, mille, million);
        }
        printf("-%s", mille + 1);
        if (reste > 0)
        {
            printf("");
            affiche_mot(i, reste, j, c, mille, million);
        }
    }
    else if (n >= 1000000)
    {
        int millions = n / 1000000;
        int reste = n - (millions * 1000000);
        affiche_mot(i, millions, j, c, mille, million);
        printf("-%s", million + 1);
        if (reste > 0)
        {
            printf("-");
            affiche_mot(i, reste, j, c, mille, million);
        }
    }
}

int main()
{
    int taille = 19;
    int nombre = 81;
    char **i = (char **)malloc(20 * sizeof(char *));
    i[0] = "zero";
    i[1] = "un";
    i[2] = "deux";
    i[3] = "trois";
    i[4] = "quatre";
    i[5] = "cinq";
    i[6] = "six";
    i[7] = "sept";
    i[8] = "huit";
    i[9] = "neuf";
    i[10] = "dix";
    i[11] = "onze";
    i[12] = "douze";
    i[13] = "treize";
    i[14] = "quatorze";
    i[15] = "quinze";
    i[16] = "seize";
    i[17] = "dix-sept";
    i[18] = "dix-huit";
    i[19] = "dix-neuf";

    char *
        k[] = {
            "4zero", "2un", "4deux", "5trois", "6quatre", "4cinq", "3six", "4sept", "4huit", "4neuf",
            "3dix", "4onze", "5douze", "6treize", "8quatorze", "6quinze", "5seize", "8dix-sept", "8dix-huit", "8dix-neuf"};

    char *t[] = {
        "vingt", "trente", "quarante", "cinquante", "soixante",
        "soixante-dix", "quatre-vingts", "quatre-vingt-dix"};

    char *v[] = {
        "5vingt", "6trente", "8quarante", "9cinquante", "8soixante",
        "11soixante-dix", "13quatre-vingts", "16quatre-vingt-dix", "4cent"};

    ajoutTaille(i, 20);
    for (int j = 0; j < 20; j++)
    {
        printf("i[%d] = %s\n", j, i[j]);
    }

    affiche_mot(k, nombre, v, c, mille, million);

    for (int j = 0; j < taille; j++)
    {
        free(i[j]);
    }
    free(i);

    return 0;
}