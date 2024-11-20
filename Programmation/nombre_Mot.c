#include <stdio.h>
#include <stdlib.h>

void nombre_mot(char **i, int n)
{

    // while (i[n] != '\0')
    // {
    //     n++;
    // }

    if (n < 20)
    {
        printf("%s", i[n] + 1);
    }
}

int main()
{
    int nombre = 19;
    char **i = (char **)malloc(20 * sizeof(char *));
    i[0] = "4zero";
    i[1] = "2un";
    i[2] = "4deux";
    i[3] = "5trois";
    i[4] = "4quatre";
    i[5] = "4cinq";
    i[6] = "3six";
    i[7] = "4sept";
    i[8] = "5huit";
    i[9] = "4neuf";
    i[10] = "3dix";
    i[11] = "6onze";
    i[12] = "6douze";
    i[13] = "7treize";
    i[14] = "6quatorze";
    i[15] = "5quinze";
    i[16] = "7seize";
    i[17] = "8dix-sept";
    i[18] = "8dix-huit";
    i[19] = "8dix-neuf";

    nombre_mot(i, nombre);
}