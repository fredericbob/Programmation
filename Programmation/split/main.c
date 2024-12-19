#include <stdio.h>
#include <math.h>

// Fonction pour vérifier si un caractère est un chiffre
int est_chiffre(char c)
{
    return (c >= '0' && c <= '9');
}
void traiter_racine_carre(const char *entree, char *sortie)
{
    int i = 0, j = 0;

    while (entree[i] != '\0')
    {
        if (entree[i] == 'V') // Détecter le symbole de racine carrée
        {
            i++;
            int nombre = 0;

            // Lire le nombre qui suit le V
            while (est_chiffre(entree[i]))
            {
                nombre = nombre * 10 + (entree[i] - '0');
                i++;
            }

            // Calculer la racine carrée
            double racine = sqrt((double)nombre);

            // Ajouter la valeur calculée dans la chaîne de sortie
            j += sprintf(&sortie[j], "%.0f", racine);
        }
        else
        {
            // Copier les autres caractères normalement
            sortie[j++] = entree[i++];
        }
    }
    sortie[j] = '\0'; // Terminer la chaîne
}

// Fonction pour analyser un côté de l'équation
void analyser_cote(const char *str, int *coef_x, int *constante)
{
    int i = 0, signe = 1, coef = 0, constante_loc = 0;
    int est_x = 0;

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

        // Lire un nombre (ou un coefficient)
        int num = 0;
        int chiffre_trouve = 0;
        while (est_chiffre(str[i]))
        {
            num = num * 10 + (str[i] - '0');
            i++;
            chiffre_trouve = 1;
        }
        if (!chiffre_trouve)
        {
            num = 1; // Par défaut, coefficient de x est 1 (ex: "x")
        }

        // Vérifier si c'est un coefficient de x
        if (str[i] == 'x')
        {
            coef += signe * num;
            est_x = 1;
            i++; // Passer 'x'
        }
        else
        {
            constante_loc += signe * num;
        }
    }

    // Mise à jour des résultats
    *coef_x += coef;
    *constante += constante_loc;
}

// Fonction principale pour résoudre l'équation
void resoudre_equation(const char *equation)
{
    int coef_x_gauche = 0, constante_gauche = 0;
    int coef_x_droite = 0, constante_droite = 0;

    // Diviser l'équation en deux parties
    const char *separateur = equation;
    while (*separateur != '=' && *separateur != '\0')
    {
        separateur++;
    }

    if (*separateur == '\0')
    {
        printf("Erreur : pas de '=' trouvé dans l'équation.\n");
        return;
    }

    // Analyser chaque côté
    char gauche[100], droite[100];
    int i = 0;
    for (; equation[i] != '='; i++)
    {
        gauche[i] = equation[i];
    }
    gauche[i] = '\0';
    i++; // Passer '='
    int j = 0;
    for (; equation[i] != '\0'; i++, j++)
    {
        droite[j] = equation[i];
    }
    droite[j] = '\0';

    analyser_cote(gauche, &coef_x_gauche, &constante_gauche);
    analyser_cote(droite, &coef_x_droite, &constante_droite);

    // Calculer le résultat
    int coef_x = coef_x_gauche - coef_x_droite;
    int constante = constante_droite - constante_gauche;

    if (coef_x == 0)
    {
        if (constante == 0)
        {
            printf("L'équation a une infinité de solutions.\n");
        }
        else
        {
            printf("L'équation n'a pas de solution.\n");
        }
    }
    else
    {
        double x = (double)constante / coef_x;
        printf("Solution : x = %.2f\n", x);
    }
}

void analyser_cote_second_degre(const char *str, int *coef_x2, int *coef_x, int *constante)
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

        // Lire un nombre (ou un coefficient)
        int num = 0;
        int chiffre_trouve = 0;
        while (est_chiffre(str[i]))
        {
            num = num * 10 + (str[i] - '0');
            i++;
            chiffre_trouve = 1;
        }
        if (!chiffre_trouve)
        {
            num = 1; // Par défaut, coefficient est 1 (ex: "x" ou "x^2")
        }
        num *= signe;

        // Vérifier si c'est un coefficient de x^2
        if (str[i] == 'x' && str[i + 1] == '_' && str[i + 2] == '2')
        {
            *coef_x2 += num;
            i += 3; // Passer 'x_2'
        }
        // Vérifier si c'est un coefficient de x
        else if (str[i] == 'x')
        {
            *coef_x += num;
            i++; // Passer 'x'
        }
        else
        {
            *constante += num;
        }
    }
}

// Fonction pour résoudre une équation du second degré
void resoudre_second_degre(const char *equation)
{
    int coef_x2_gauche = 0, coef_x_gauche = 0, constante_gauche = 0;
    int coef_x2_droite = 0, coef_x_droite = 0, constante_droite = 0;

    // Diviser l'équation en deux parties
    const char *separateur = equation;
    while (*separateur != '=' && *separateur != '\0')
    {
        separateur++;
    }

    if (*separateur == '\0')
    {
        printf("Erreur : pas de '=' trouvé dans l'équation.\n");
        return;
    }

    // Analyser chaque côté
    char gauche[100], droite[100];
    int i = 0;
    for (; equation[i] != '='; i++)
    {
        gauche[i] = equation[i];
    }
    gauche[i] = '\0';
    i++; // Passer '='
    int j = 0;
    for (; equation[i] != '\0'; i++, j++)
    {
        droite[j] = equation[i];
    }
    droite[j] = '\0';

    analyser_cote_second_degre(gauche, &coef_x2_gauche, &coef_x_gauche, &constante_gauche);
    analyser_cote_second_degre(droite, &coef_x2_droite, &coef_x_droite, &constante_droite);

    // Calculer les coefficients totaux
    int coef_x2 = coef_x2_gauche - coef_x2_droite;
    int coef_x = coef_x_gauche - coef_x_droite;
    int constante = constante_gauche - constante_droite;

    // Calculer le discriminant
    int delta = coef_x * coef_x - 4 * coef_x2 * constante;
    printf("delta %d\n", delta);

    if (coef_x2 == 0)
    {
        printf("Erreur : l'équation n'est pas du second degré.\n");
        return;
    }

    if (delta > 0)
    {
        double x1 = (-coef_x + sqrt(delta)) / (2.0 * coef_x2);
        double x2 = (-coef_x - sqrt(delta)) / (2.0 * coef_x2);
        printf("Les solutions sont : x1 = %.2f et x2 = %.2f\n", x1, x2);
    }
    else if (delta == 0)
    {
        double x = -coef_x / (2.0 * coef_x2);
        printf("Il y a une solution : x = %.2f\n", x);
    }
    else
    {
        printf("L'équation n'a pas de solution réelle.\n");
    }
}

void separer_phrase(const char *input, char *texte, char *equation)
{
    int i = 0, j = 0, startIndex = 0;

    // Chercher où commence l'équation (dès qu'un chiffre ou 'x_' est trouvé)
    while (input[i] != '\0')
    {
        // Condition pour détecter un chiffre ou 'x_' suivi de chiffres
        if ((input[i] >= '0' && input[i] <= '9') ||
            (input[i] == 'x' && input[i + 1] != ' ') || input[i] == 'V')
        {
            break; // On arrête dès qu'on trouve un chiffre ou 'x_'
        }
        i++;
    }

    // Sauvegarder la position de `i` avant de le décrémenter
    startIndex = i;

    // Copier le texte avant l'équation
    j = 0;
    for (int k = 0; k < startIndex; k++)
    {
        texte[j++] = input[k]; // Copier les caractères avant l'équation
    }
    texte[j] = '\0'; // Terminer la chaîne texte

    // Copier l'équation (tout ce qui suit)
    j = 0;
    while (input[i] != '\0')
    {
        equation[j++] = input[i++]; // Copier tout ce qui suit
    }
    equation[j] = '\0'; // Terminer la chaîne equation
}

int main()
{
    char texte1[100], equations1[100], equation_traitee1[100];
    ;
    const char equation[] = "firy x raha 4x-V16=0"; // Exemple d'équation
    separer_phrase(equation, texte1, equations1);
    printf("Texte: %s\n", texte1);
    printf("Equation premier degrer: %s\n", equations1);
    traiter_racine_carre(equations1, equation_traitee1);
    resoudre_equation(equation_traitee1);

    const char input[] = "firy x raha x_2-3x-10=0";
    char texte[100], equations_de[100], equation_traitee[100];
    ; // Tableau pour stocker les résultats

    separer_phrase(input, texte, equations_de); // Exemple d'équation du second degré
    printf("Texte: %s\n", texte);
    printf("Equation second degrer: %s\n", equations_de);
    traiter_racine_carre(equations_de, equation_traitee);
    resoudre_second_degre(equation_traitee);
    return 0;
}
