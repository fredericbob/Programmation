#include <stdio.h>
#include <stdlib.h>

char *alphabe(char a)
{
    char *resultat = (char *)malloc(27 * sizeof(char));
    for (int i = 0; i < 26; i++)
    {
        resultat[i] = a + i;
    }
    resultat[26] = '\0';
    return resultat;
}

char *cryptage(char *word, int nombre, int types)
{

    int length = 0;
    while (word[length] != '\0')
    {
        length++;
    }

    char *resultat = (char *)malloc((length + 1) * sizeof(char));
    int j = 0;

    for (int i = 0; i < length; i++)
    {
        char c = word[i];

        if (types == 1)
        {
            if (c >= 'a' && c <= 'z')
            {
                resultat[j] = 'a' + (c - 'a' + nombre) % 26;
            }
            else if (c >= 'A' && c <= 'Z')
            {
                resultat[j] = 'A' + (c - 'A' + nombre) % 26;
            }
            else
            {
                resultat[j] = c;
            }
        }
        else if (types == 2)
        {
            if (c >= 'a' && c <= 'z')
            {
                int shift = (c - 'a' - nombre);
                if (shift < 0)
                    shift += 26;
                resultat[j] = 'a' + shift % 26;
            }
            else if (c >= 'A' && c <= 'Z')
            {
                int shift = (c - 'A' - nombre);
                if (shift < 0)
                    shift += 26;
                resultat[j] = 'A' + shift % 26;
            }
            else
            {
                resultat[j] = c;
            }
        }
        else if (types == 3)
        {
            if (c >= 'a' && c <= 'z')
            {
                resultat[j] = 'a' + ((c - 'a') * nombre) % 26;
            }
            else if (c >= 'A' && c <= 'Z')
            {
                resultat[j] = 'A' + ((c - 'A') * nombre) % 26;
            }
            else
            {
                resultat[j] = c;
            }
        }
        else if (types == 4)
        {
            if (c >= 'a' && c <= 'z')
            {
                int division = (c - 'a') / nombre;
                if ((c - 'a') % nombre == 0 && division >= 0 && division < 26)
                {
                    resultat[j] = 'a' + division;
                }
                else
                {
                    resultat[j] = c;
                }
            }
            else if (c >= 'A' && c <= 'Z')
            {
                int division = (c - 'A') / nombre;
                if ((c - 'A') % nombre == 0 && division >= 0 && division < 26)
                {
                    resultat[j] = 'A' + division;
                }
                else
                {
                    resultat[j] = c;
                }
            }
            else
            {
                resultat[j] = c;
            }
        }
        j++;
    }

    resultat[j] = '\0';
    return resultat;
}

int main(void)
{
    char *lettre = malloc(15 * sizeof(char));

    lettre[0] = 'j';
    lettre[1] = 'e';
    lettre[2] = ' ';
    lettre[3] = 's';
    lettre[4] = 'u';
    lettre[5] = 'i';
    lettre[6] = 's';
    lettre[7] = ' ';
    lettre[8] = 'n';
    lettre[9] = 'e';
    lettre[10] = 'e';
    lettre[11] = ' ';
    lettre[12] = 'e';
    lettre[13] = 'n';
    lettre[14] = ' ';
    lettre[15] = '\0';

    int nombre = 2;
    int type = 1;

    char *resultat = cryptage(lettre, nombre, type);
    printf("%s", resultat);

    free(lettre);
    free(resultat);
}