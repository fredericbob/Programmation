#include <stdio.h>

// Fonction pour vérifier si un caractère est un chiffre
int est_chiffre(char c)
{
    return (c >= '0' && c <= '9');
}

// Fonction pour séparer la phrase en texte avant l'équation, l'équation, et extraire la valeur de f()
void separer_phrase(const char *input, char *texte, char *equation, int *valeur_f)
{
    int i = 0, j = 0, k = 0;
    int found_f = 0;
    char buffer[20];

    // Chercher "f(" dans l'entrée
    while (input[i] != '\0')
    {
        if (input[i] == 'f' && input[i + 1] == '(')
        {
            found_f = 1;
            // Copier "f(" dans le texte
            texte[j++] = input[i++];
            texte[j++] = input[i++];
            break;
        }
        texte[j++] = input[i++];
    }

    // Extraire le nombre après 'f('
    if (found_f)
    {
        while (est_chiffre(input[i]))
        {
            buffer[k++] = input[i];
            texte[j++] = input[i++]; // Copier le chiffre dans le texte
        }
        buffer[k] = '\0';        // Terminer le buffer avec un caractère nul
        texte[j++] = input[i++]; // Copier le caractère ')' dans le texte
        texte[j] = '\0';         // Terminer la chaîne texte

        // Convertir le buffer en entier manuellement
        *valeur_f = 0;
        for (int m = 0; buffer[m] != '\0'; m++)
        {
            *valeur_f = *valeur_f * 10 + (buffer[m] - '0');
        }
    }

    // Ignorer le texte jusqu'à trouver le début de l'équation
    while (input[i] != '\0' && input[i] != 'x' && input[i] != '(')
    {
        i++;
    }

    // Copier l'équation à partir du caractère actuel jusqu'à la fin
    j = 0;
    while (input[i] != '\0')
    {
        equation[j++] = input[i++];
    }
    equation[j] = '\0'; // Terminer la chaîne equation
}

// Fonction pour calculer la puissance d'un entier
int puissance(int base, int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;
}

int calculer_f(const char *equation, int valeur_x)
{
    int i = 0, signe = 1, nombre = 0, resultat_gauche = 0, resultat_droite = 0;
    int terme_courant = 0;
    int apres_egal = 0; // Pour savoir si on est après le signe égal '='

    while (equation[i] != '\0')
    {
        // Gérer les signes + et -
        if (equation[i] == '+')
        {
            signe = 1;
            i++;
        }
        else if (equation[i] == '-')
        {
            signe = -1;
            i++;
        }

        // Si on rencontre '=', commencer à gérer les termes après
        if (equation[i] == '=')
        {
            i++;            // Passer '='
            apres_egal = 1; // On est après l'égal
            // À ce moment, vous devez commencer à "soustraire" les termes après le signe égal
        }

        // Si on rencontre 'x', vérifier s'il y a une puissance
        if (equation[i] == 'x')
        {
            i++;

            // Vérifier s'il y a '_2' qui doit être interprété comme x^2
            if (equation[i] == '_' && equation[i + 1] == '2')
            {
                i += 2;                                         // Passer '_2'
                terme_courant = signe * puissance(valeur_x, 2); // Calculer x^2
            }
            else
            {
                terme_courant = signe * valeur_x; // Par défaut, juste x
            }
        }
        // Lire un nombre entier
        else if (est_chiffre(equation[i]))
        {
            nombre = 0;
            while (est_chiffre(equation[i]))
            {
                nombre = nombre * 10 + (equation[i] - '0');
                i++;
            }
            terme_courant = signe * nombre;
        }
        else
        {
            i++;
            continue;
        }

        // Ajouter ou soustraire le terme courant en fonction de la position par rapport à '='
        if (apres_egal)
        {
            // Si on est après le signe égal, on soustrait le terme
            resultat_droite -= terme_courant;
        }
        else
        {
            // Avant '=', on ajoute normalement
            resultat_gauche += terme_courant;
        }
    }

    // Une fois les termes calculés, réarranger l'équation pour obtenir 0.
    return resultat_gauche + resultat_droite; // Résultat de l'équation réarrangée
}

int main()
{
    const char input[] = "Quel est le f(2) si x_2+3x+4=1";
    char texte[100], equation[100];
    int valeur_f = 0;

    separer_phrase(input, texte, equation, &valeur_f);

    printf("Texte : %s\n", texte);
    printf("Équation : %s\n", equation);
    printf("Valeur de f : %d\n", valeur_f);

    int resultat = calculer_f(equation, valeur_f);

    printf("Résultat de f(%d) = %d\n", valeur_f, resultat);

    return 0;
}
