#include <stdio.h>
#include <ctype.h>
#include <string.h>

void traiter_equation(const char *entree, char *sortie)
{
    int i = 0, j = 0;

    while (entree[i] != '\0')
    {
        if (entree[i] == 'x')
        { // Vérifier si on rencontre un 'x'
            if (entree[i + 1] == '_' && isdigit(entree[i + 2]))
            {
                // Cas où x est suivi d'un indice (ex: x_0, x_1, etc.)
                sortie[j++] = 'x';
                sortie[j++] = '_';
                sortie[j++] = entree[i + 2]; // Copier le chiffre après _
                i += 3;                      // Avancer de 3 positions (x, _, chiffre)
            }
            else
            {
                // Cas normal où x est une variable
                sortie[j++] = 'x';
                i++;
            }
        }
        else
        {
            // Copier les autres caractères normalement
            sortie[j++] = entree[i++];
        }
    }
    sortie[j] = '\0'; // Terminer la chaîne
}

int main()
{
    const char input[] = "firy x raha x_0-3x-10=0";
    char output[100];

    traiter_equation(input, output);

    printf("Sortie : %s\n", output);
    return 0;
}
