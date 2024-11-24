#include <stdio.h>
#include <stdlib.h>

int cast(char *date)
{

    int resultat = 0;
    int i = 0;
    while (date[i] != '\0')
    {
        resultat = resultat * 10 + (date[i] - '0');
        i++;
    }

    return resultat;
}

int age(int result, char *date)
{

    int resultat = cast(date);
    int sum = result - resultat;
    return sum;
}
int main()
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
    char *naissance = malloc(5 * sizeof(char));
    naissance[0] = '2';
    naissance[1] = '0';
    naissance[2] = '1';
    naissance[3] = '0';
    naissance[4] = '\0';

    for (int i = 0; i < 15; i++)
    {
        printf("%c", lettre[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        printf("%c", naissance[i]);
    }

    int result = 2024;
    int resultat = age(result, naissance);
    printf(" et j'ai %d ans", resultat);

    free(lettre);
    free(naissance);
}