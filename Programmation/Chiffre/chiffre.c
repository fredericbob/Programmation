#include <stdio.h>
#include <stdlib.h>

void tableau(int n, int taille, char **tab, char **d, char **mille, char *cent_mille, char *million, char *milliard)
{

    int dizaine = n / 10;
    int unite = n - (dizaine * 10);
    int centaine = (n / 100) % 10;
    int millier = n / 1000;

    if (n <= 10)
    {
        if (unite == 0)
        {
            printf("%s\n", tab[10] + 1);
        }
        else if (unite < 10)
        {
            printf("%s\n", tab[unite] + 1);
        }
    }
    else if (n > 10 && n <= 100)
    {
        if (dizaine == 1)
        {
            printf("%s-ambiny-%s\n", tab[unite] + 1, tab[10] + 1);
        }
        else if (dizaine > 1 && dizaine < 10)
        {
            if (unite == 0)
            {
                printf("%s-%s\n", tab[dizaine] + 1, tab[10] + 1);
            }
            else
            {
                printf("%s-ambiny-%s-%s\n", tab[unite] + 1, tab[dizaine] + 1, tab[10] + 1);
            }
        }
        else if (dizaine == 10)
        {
            printf("%s\n", d[0] + 1);
        }
    }
    // zato
    else if (n >= 100 && n < 1000)
    {
        int reste = n % 100;
        if (n == 100)
        {
            printf("%s", d[0] + 1);
        }
        else if (centaine > 0 && reste == 0)
        {
            printf("%s-%s", tab[centaine] + 1, d[0] + 1);
        }
        else
        {
            if (reste > 0)
            {
                if (reste < 10)
                {
                    printf(" %s\n", tab[reste] + 1);
                }
                else
                {
                    int dizaine_restante = reste / 10;
                    int unite_restante = reste % 10;

                    if (dizaine_restante == 1)
                    {
                        printf("%s-ambiny-%s", tab[unite_restante] + 1, tab[10] + 1);
                    }
                    else
                    {
                        printf("%s-ambiny-%s-%s", tab[unite_restante] + 1, tab[dizaine_restante] + 1, tab[10] + 1);
                    }
                    printf("-%s-%s", tab[centaine] + 1, d[0] + 1);
                }
            }
        }
    }
    // arivo
    else if (n >= 1000 && n < 10000)
    {

        int reste = n % 1000;
        if (n == 1000)
        {
            printf("%s", mille[0] + 1);
        }
        else if (millier > 0 && reste == 0)
        {
            printf("%s-%s", tab[millier] + 1, mille[0] + 1);
        }
        else
        {
            if (reste > 0)
            {

                if (reste < 10)
                {
                    printf(" %s-sy-%s\n", tab[reste] + 1, mille[0] + 1);
                }
                else if (reste >= 100)
                {
                    int dizaine_restante = reste / 100;

                    int unite_restante = reste % 100;

                    if (unite_restante == 0)
                    {
                        printf("%s-%s-sy-%s", tab[centaine] + 1, d[0] + 1, mille[0] + 1);
                    }
                    else if (unite_restante != 0)
                    {
                        int unite_restante_dernier = unite_restante / 10;

                        printf("%s-ambiny-%s-%s-%s-%s-%s-%s", tab[unite_restante % 10] + 1, tab[unite_restante / 10] + 1, tab[10] + 1, tab[dizaine_restante] + 1, d[0] + 1, tab[millier] + 1, mille[0] + 1);
                    }
                    // else
                    // {
                    //     printf("%s-ambiny-%s-%s", tab[unite_restante] + 1, tab[dizaine_restante] + 1, tab[10] + 1);
                    // }
                }

                else
                {
                    int dizaine_restante = reste / 10;
                    int unite_restante = reste % 10;

                    if (dizaine_restante == 1)
                    {
                        printf("%s-ambiny-%s", tab[unite_restante] + 1, tab[10] + 1);
                    }
                    else
                    {
                        printf("%s-ambiny-%s-%s", tab[unite_restante] + 1, tab[dizaine_restante] + 1, tab[10] + 1);
                    }
                    if (millier == 1)
                    {
                        printf("-sy-%s", mille[0] + 1);
                    }
                    else
                    {
                        printf("-%s-%s", tab[millier] + 1, mille[0] + 1);
                    }
                }
            }
        }
    }
}

int main()
{
    int taille = 20;
    int n = 2120;
    char **i = malloc(20 * sizeof(char *));

    for (int j = 0; j < 20; j++)
    {
        i[j] = malloc(50 * sizeof(char));
    }
    i[0][0] = '5';
    i[0][1] = 'a';
    i[0][2] = 'o';
    i[0][3] = 't';
    i[0][4] = 'r';
    i[0][5] = 'a';
    i[0][6] = '\0';

    i[1][0] = '3';
    i[1][1] = 'r';
    i[1][2] = 'a';
    i[1][3] = 'y';
    i[1][4] = '\0';

    i[2][0] = '3';
    i[2][1] = 'r';
    i[2][2] = 'o';
    i[2][3] = 'a';
    i[2][4] = '\0';

    i[3][0] = '4';
    i[3][1] = 't';
    i[3][2] = 'e';
    i[3][3] = 'l';
    i[3][4] = 'o';
    i[3][5] = '\0';

    i[4][0] = '6';
    i[4][1] = 'e';
    i[4][2] = 'f';
    i[4][3] = 'a';
    i[4][4] = 't';
    i[4][5] = 'r';
    i[4][6] = 'a';
    i[4][7] = '\0';

    i[5][0] = '4';
    i[5][1] = 'd';
    i[5][2] = 'i';
    i[5][3] = 'm';
    i[5][4] = 'y';
    i[5][5] = '\0';

    i[6][0] = '6';
    i[6][1] = 'e';
    i[6][2] = 'n';
    i[6][3] = 'i';
    i[6][4] = 'n';
    i[6][5] = 'a';
    i[6][6] = '\0';

    i[7][0] = '4';
    i[7][1] = 'f';
    i[7][2] = 'i';
    i[7][3] = 't';
    i[7][4] = 'o';
    i[7][5] = '\0';

    i[8][0] = '4';
    i[8][1] = 'v';
    i[8][2] = 'a';
    i[8][3] = 'l';
    i[8][4] = 'o';
    i[8][5] = '\0';

    i[9][0] = '4';
    i[9][1] = 's';
    i[9][2] = 'i';
    i[9][3] = 'v';
    i[9][4] = 'y';
    i[9][5] = '\0';

    i[10][0] = '4';
    i[10][1] = 'f';
    i[10][2] = 'o';
    i[10][3] = 'l';
    i[10][4] = 'o';
    i[10][5] = '\0';

    char **c = malloc(9 * sizeof(char *));
    for (int j = 0; j < 9; j++)
    {
        c[j] = malloc(6 * sizeof(char));
    }
    c[0][0] = '4';
    c[0][1] = 'z';
    c[0][2] = 'a';
    c[0][3] = 't';
    c[0][4] = 'o';
    c[0][5] = '\0';

    char **mille = malloc(9 * sizeof(char *));
    for (int j = 0; j < 9; j++)
    {
        mille[j] = malloc(7 * sizeof(char));
    }
    mille[0][0] = '5';
    mille[0][1] = 'a';
    mille[0][2] = 'r';
    mille[0][3] = 'i';
    mille[0][4] = 'v';
    mille[0][5] = 'o';
    mille[0][6] = '\0';

    char *dix_mille = "5alina";
    char *cent_mille = "5etsy";
    char *million = "9tapitrisa";
    char *milliard = "9lavitrisa";

    tableau(n, taille, i, c, mille, cent_mille, million, milliard);

    for (int j = 0; j < 20; j++)
    {
        free(i[j]);
    }
    free(i);

    for (int j = 0; j < 9; j++)
    {
        free(c[j]);
    }
    free(c);

    return 0;
}