#include <stdio.h>
#include <stdlib.h>

void tableau(int nombre, int taille, char **tab, char **v, char **c, char *mille)
{
    int dizaine = nombre / 10;
    int unite = nombre - (dizaine * 10);
    int centaine = nombre / 100;
    int unite2 = nombre - (centaine * 100);
    int dizainecent = unite2 / 10;

    if (nombre < taille)
    {
        printf("%s\n", tab[nombre] + 1);
    }
    else if (nombre >= 20 && nombre < 70)
    {
        printf("%s", v[dizaine - 2] + 1);
        if (unite > 0)
        {
            printf("-%s", tab[unite] + 1);
        }
    }
    else if (nombre >= 70 && nombre < 80)
    {
        int soustraction = nombre - 70;
        if (soustraction == 0)
        {
            printf("%s", v[5] + 2);
        }
        else
        {
            printf("%s", v[4] + 1);
        }
        if (soustraction > 0)
        {
            printf("-%s", tab[soustraction + 10] + 1);
        }
    }
    else if (nombre >= 80 && nombre < 100)
    {
        int soustraction2 = nombre - 80;
        if (soustraction2 == 0)
        {
            printf("%s", v[7] + 1);
        }
        else
        {
            printf("%s", v[6] + 2);
        }
        if (soustraction2 > 0)
        {
            printf("-%s", tab[soustraction2] + 1);
        }
    }
    else if (nombre >= 100 && nombre < 1000)
    {

        if (nombre >= 100 && nombre < 1000)
        {
            printf("%s", c[centaine - 1] + 1);

            if (unite2 == 0)
            {
                printf("\n");
            }
            else if (unite2 >= 70 && unite2 < 80)
            {
                if (unite2 == 70)
                {
                    printf("-%s", v[5] + 2);
                }

                else
                {
                    printf("-%s", v[4] + 1);
                }

                if (unite2 - 70 > 0)
                {
                    printf("-%s", tab[unite2 - 70 + 10] + 1);
                }
            }
            else if (unite2 >= 80 && unite2 < 90)
            {
                printf("-%s", v[6] + 2);
                if (unite2 - 80 > 0)
                {
                    printf("-%s", tab[unite2 - 80] + 1);
                }
            }
            else if (unite2 >= 90 && unite2 < 100)
            {
                if (unite2 == 90)
                {
                    printf("-%s", v[7] + 2);
                }
                else
                {
                    printf("-%s", v[6] + 2);
                }
                if (unite2 - 90 > 0)
                {
                    printf("-%s", tab[unite2 - 90 + 10] + 1);
                }
            }
            else if (unite2 >= 20 && unite2 < 70)
            {

                printf("-%s", v[dizainecent - 2] + 1);

                if (unite2 - (dizainecent * 10) > 0)
                {
                    printf("-%s", tab[unite2 - (dizainecent * 10)] + 1);
                }
            }
            else if (unite2 >= 10 && unite2 < 20)
            {
                printf("-%s", tab[unite2] + 1);
            }
            else if (unite2 < 10 && unite2 > 0)
            {
                printf("-%s", tab[unite2] + 1);
            }
        }
    }
}

int main()
{
    int taille = 20;
    int nombre = 999;
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
    c[3] = "9quatre-cent";
    c[4] = "8cinq-cent";
    c[5] = "7six-cent";
    c[6] = "8sept-cent";
    c[7] = "8huit-cent";
    c[8] = "8neuf-cent";

    char *mille = "5mille";

    tableau(nombre, taille, i, v, c, mille);

    free(i);
    free(v);
    free(c);

    return 0;
}