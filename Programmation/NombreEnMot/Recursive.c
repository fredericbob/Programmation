#include <stdio.h>
#include <stdlib.h>

char *mille = "5mille";
char *million = "7million";

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
        if (n == 400)
        {
            printf("%s", c[centaine - 1] + 2);
        }
        else
        {
            printf("%s", c[centaine - 1] + 1);
        }

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
        printf("%s", mille + 1);
        if (reste > 0)
        {
            printf("-");
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

    int nombre = 1670;
    char **i = malloc(20 * sizeof(char *));
    i[0] = "4zero";
    i[1] = "2un";
    i[2] = "4deux";
    i[3] = "5trois";
    i[4] = "6quatre";
    i[5] = "4cinq";
    i[6] = "3six";
    i[7] = "4sept";
    i[8] = "4huit";
    i[9] = "4neuf";
    i[10] = "3dix";
    i[11] = "4onze";
    i[12] = "5douze";
    i[13] = "6treize";
    i[14] = "8quatorze";
    i[15] = "6quinze";
    i[16] = "5seize";
    i[17] = "8dix-sept";
    i[18] = "8dix-huit";
    i[19] = "8dix-neuf";
    char **v = malloc(9 * sizeof(char *));
    v[0] = "5vingt";
    v[1] = "6trente";
    v[2] = "8quarante";
    v[3] = "9cinquante";
    v[4] = "8soixante";
    v[5] = "11soixante-dix";
    v[6] = "13quatre-vingts";
    v[7] = "16quatre-vingt-dix";
    v[8] = "4cent";
    char **c = malloc(9 * sizeof(char *));
    c[0] = "4cent";
    c[1] = "8deux-cent";
    c[2] = "9trois-cent";
    c[3] = "10quatre-cent";
    c[4] = "8cinq-cent";
    c[5] = "7six-cent";
    c[6] = "8sept-cent";
    c[7] = "8huit-cent";
    c[8] = "8neuf-cent";

    affiche_mot(i, nombre, v, c, mille, million);
    printf("\n");

    free(i);
    free(v);
    free(c);
    return 0;
}