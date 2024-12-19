#include <stdio.h>

// Fonction pour vérifier si un caractère est un chiffre
int est_chiffre(char c)
{
    return (c >= '0' && c <= '9');
}

// Fonction pour séparer la phrase en texte avant l'équation, l'équation, et extraire la valeur de f()
void separer_phrase_calculeX(const char *input, char *texte, char *equation, int *valeur_f)
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
            texte[j++] = input[i++];
            texte[j++] = input[i++];
            break;
        }
        texte[j++] = input[i++];
    }

    // Extraire le nombre après 'f('
    if (found_f)
    {
        int negatif = 0;
        if (input[i] == '-') // Vérifier si le nombre est négatif
        {
            negatif = 1;
            buffer[k++] = input[i];  // Ajouter le signe dans le buffer
            texte[j++] = input[i++]; // Copier le signe dans le texte
        }

        while (est_chiffre(input[i]))
        {
            buffer[k++] = input[i];
            texte[j++] = input[i++];
        }
        buffer[k] = '\0';        // Terminer le buffer avec un caractère nul
        texte[j++] = input[i++]; // Copier le caractère ')' dans le texte
        texte[j] = '\0';         // Terminer la chaîne texte

        // Convertir le buffer en entier
        *valeur_f = 0;
        for (int m = (negatif ? 1 : 0); buffer[m] != '\0'; m++) // Gérer le signe
        {
            *valeur_f = *valeur_f * 10 + (buffer[m] - '0');
        }
        if (negatif)
        {
            *valeur_f = -*valeur_f; // Appliquer le signe négatif si nécessaire
        }
    }

    // Ignorer le texte jusqu'à trouver le début de l'équation
    while (input[i] != '\0')
    {
        // Condition pour détecter un chiffre ou 'x_' suivi de chiffres
        if ((input[i] >= '0' && input[i] <= '9') ||
            (input[i] == 'x' && input[i + 1] != ' ') || input[i] == 'V' || input[i] == '(' || input[i] == '-')
        {

            break; // On arrête dès qu'on trouve un chiffre ou 'x_'
        }
        texte[j++] = input[i];
        i++;
    }
    texte[j] = '\0';
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

// Fonction pour analyser un côté de l'équation avec prise en charge des parenthèses
void analyser_cote_caluclX(const char *str, int *coef_x, int *coef_x2, int *constante, int valeur_x)
{
    int i = 0, signe = 1;
    while (str[i] != '\0')
    {
        // Gestion des signes
        if (str[i] == '-')
        {
            signe = -1;
            i++;
        }
        else if (str[i] == '+')
        {
            signe = 1;
            i++;
        }

        // Si une parenthèse ouvrante est trouvée
        if (str[i] == '(')
        {
            i++; // Passer la parenthèse ouvrante
            int temp_coef_x = 0, temp_coef_x2 = 0, temp_constante = 0;

            // Analyser l'expression à l'intérieur des parenthèses
            while (str[i] != ')' && str[i] != '\0')
            {
                int num = 0;
                int chiffre_trouve = 0;

                // Lire un nombre (ou un coefficient)
                while (str[i] >= '0' && str[i] <= '9')
                {
                    num = num * 10 + (str[i] - '0');
                    i++;
                    chiffre_trouve = 1;
                }
                if (!chiffre_trouve)
                {
                    num = 1; // Par défaut, coefficient de x est 1
                }

                if (str[i] == 'x')
                {
                    i++;
                    if (str[i] == '_' && str[i + 1] == '2')
                    {
                        i += 2; // Passer '_2'
                        temp_coef_x2 += signe * num;
                    }
                    else
                    {
                        temp_coef_x += signe * num;
                    }
                }
                else
                {
                    temp_constante += signe * num;
                }

                // Gestion des signes à l'intérieur des parenthèses
                if (str[i] == '-')
                {
                    signe = -1;
                    i++;
                }
                else if (str[i] == '+')
                {
                    signe = 1;
                    i++;
                }
            }

            // Appliquer les valeurs trouvées à l'intérieur des parenthèses
            *coef_x2 += temp_coef_x2;
            *coef_x += temp_coef_x;
            *constante += temp_constante;

            if (str[i] == ')')
            {
                i++; // Passer la parenthèse fermante
            }
        }
        else
        {
            // Si pas de parenthèses, analyser normalement
            int num = 0;
            int chiffre_trouve = 0;

            while (str[i] >= '0' && str[i] <= '9')
            {
                num = num * 10 + (str[i] - '0');
                i++;
                chiffre_trouve = 1;
            }
            if (!chiffre_trouve)
            {
                num = 1;
            }

            if (str[i] == 'x')
            {
                i++;
                if (str[i] == '_' && str[i + 1] == '2')
                {
                    i += 2;
                    *coef_x2 += signe * num;
                }
                else
                {
                    *coef_x += signe * num;
                }
            }
            else
            {
                *constante += signe * num;
            }
        }
    }
}
int calculer_f(const char *equation, int valeur_x)
{
    char gauche[100], droite[100];
    int coef_x_gauche = 0, coef_x2_gauche = 0, constante_gauche = 0;
    int coef_x_droite = 0, coef_x2_droite = 0, constante_droite = 0;

    // Trouver le signe '=' manuellement
    int i = 0, j = 0;
    int trouve_egal = 0;

    // Parcourir l'équation pour séparer gauche et droite
    while (equation[i] != '\0')
    {
        if (equation[i] == '=' && !trouve_egal)
        {
            trouve_egal = 1;
            gauche[j] = '\0'; // Finir la partie gauche
            i++;
            j = 0; // Réinitialiser j pour copier dans 'droite'
            continue;
        }

        if (!trouve_egal)
        {
            gauche[j++] = equation[i++];
        }
        else
        {
            droite[j++] = equation[i++];
        }
    }
    droite[j] = '\0'; // Finir la partie droite

    // Vérifier si '=' a été trouvé
    if (!trouve_egal)
    {
        printf("Erreur : pas de '=' trouvé dans l'équation.\n");
        return 0;
    }

    // Analyser chaque côté
    analyser_cote_caluclX(gauche, &coef_x_gauche, &coef_x2_gauche, &constante_gauche, valeur_x);
    analyser_cote_caluclX(droite, &coef_x_droite, &coef_x2_droite, &constante_droite, valeur_x);

    // Calculer le résultat final en transférant les termes du côté droit vers le côté gauche
    int resultat = (coef_x2_gauche - coef_x2_droite) * puissance(valeur_x, 2) +
                   (coef_x_gauche - coef_x_droite) * valeur_x +
                   (constante_gauche - constante_droite);

    return resultat;
}

int main()
{
    const char input[] = "firy f(-2) raha -1-x_2=1";
    char texte[100], equation[100];
    int valeur_f = 0;

    separer_phrase_calculeX(input, texte, equation, &valeur_f);

    printf("Texte : %s\n", texte);
    printf("Équation : %s\n", equation);
    printf("Valeur de f : %d\n", valeur_f);

    int resultat = calculer_f(equation, valeur_f);

    printf("Résultat de f(%d) = %d\n", valeur_f, resultat);

    return 0;
}