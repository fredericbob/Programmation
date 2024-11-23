#include <stdio.h>
#include <stdlib.h>

char *alphabe()
{
    char *resultat = (char *)malloc(27 * sizeof(char));
    for (int i = 0; i < 26; i++)
    {
        resultat[i] = 'a' + i;
    }
    resultat[26] = '\0';
    return resultat;
}

char *cryptage(char *word, int nombre, int types)
{
    char *resultat = (char *)malloc(27 * sizeof(char));
    int j = 0;

    if (types == 1)
    {
        for (int i = 0; i < 26; i++)
        {
            resultat[i] = 'a' + (word[i] - 'a' + nombre) % 26;
        }
        resultat[26] = '\0';
    }

    else if (types == 2)
    {
        for (int i = 0; i < 26; i++)
        {
            int shift = (word[i] - 'a' - nombre);
            if (shift < 0)
                shift += 26;
            resultat[i] = 'a' + shift % 26;
        }
        resultat[26] = '\0';
    }

    else if (types == 3)
    {
        for (int i = 0; i < 26; i++)
        {
            resultat[i] = 'a' + ((word[i] - 'a') * nombre) % 26;
        }
        resultat[26] = '\0';
    }

    else if (types == 4)
    {
        {
            for (int i = 0; i < 26; i++)
            {
                int c = (word[i] - 'a');
                if ((c % nombre) == 0)
                {
                    int division = c / nombre;

                    if (division >= 0 && division < 26)
                    {
                        resultat[j] = 'a' + division;
                        j++;
                    }
                }
            }
            resultat[j] = '\0';
        }
    }

    return resultat;
}

int main(void)
{
    char a = 'a';
    int nombre = 3;
    int type = 4;
    char *word = alphabe();
    printf("%s\n", word);
    char *resultat = cryptage(word, nombre, type);
    printf("%s", resultat);

    free(word);
    free(resultat);
}