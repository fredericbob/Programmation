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
void traiter_parentheses_premier(const char *str, char *resultat)
{
    int i = 0, j = 0;
    int signe = 1; // Par défaut, pas de signe

    // Parcours de l'expression
    while (str[i] != '\0')
    {
        if (str[i] == '(')
        {
            i++; // Ignorer la parenthèse ouvrante
            // Changer de signe si on rencontre un '-'
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
        // Si on rencontre une parenthèse fermante, revenir à signe positif
        else if (str[i] == ')')
        {
            i++;       // Ignorer la parenthèse fermante
            signe = 1; // Par défaut, après la parenthèse fermée, on reprend le signe normal
        }

        // Traiter le cas de 'x_2' pour le second degré
        else if (str[i] == 'x' && str[i + 1] == '_' && str[i + 2] == '2')
        {
            resultat[j++] = 'x';
            resultat[j++] = '^';
            resultat[j++] = '2';
            i += 3; // Passer 'x_2'
        }
        // Traiter les signes en fonction de leur position
        else if (str[i] == '+' || str[i] == '-')
        {
            if (signe == -1)
            {
                // Inverser le signe
                resultat[j++] = (str[i] == '+') ? '-' : '+';
            }
            else
            {
                resultat[j++] = str[i];
            }
            i++;
        }
        else
        {
            // Copier les autres caractères (chiffres ou variables)
            resultat[j++] = str[i++];
        }
    }
    resultat[j] = '\0'; // Terminer la chaîne résultante
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

    // Traiter les parenthèses
    char gauche_sans_parentheses[100], droite_sans_parentheses[100];
    traiter_parentheses_premier(gauche, gauche_sans_parentheses);
    traiter_parentheses_premier(droite, droite_sans_parentheses);

    analyser_cote(gauche_sans_parentheses, &coef_x_gauche, &constante_gauche);
    analyser_cote(droite_sans_parentheses, &coef_x_droite, &constante_droite);

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

void traiter_parentheses(const char *str, char *resultat)
{
    int i = 0, j = 0;
    int signe = 1; // Par défaut, pas de signe

    // Parcours de l'expression
    while (str[i] != '\0')
    {
        if (str[i] == '(')
        {
            i++; // Ignorer la parenthèse ouvrante
            // Changer de signe si on rencontre un '-'
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
        // Si on rencontre une parenthèse fermante, revenir à signe positif
        else if (str[i] == ')')
        {
            i++;       // Ignorer la parenthèse fermante
            signe = 1; // Par défaut, après la parenthèse fermée, on reprend le signe normal
        }

        // Convertir 'x_2' en 'x^2' et copier
        else if (str[i] == 'x' && str[i + 1] == '_' && str[i + 2] == '2')
        {
            resultat[j++] = 'x';
            resultat[j++] = '^';
            resultat[j++] = '2';
            i += 3; // Passer 'x_2'
        }
        // Copier le reste des caractères
        else
        {
            resultat[j++] = str[i++];
        }
    }
    resultat[j] = '\0'; // Terminer la chaîne résultante
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
        if (str[i] == 'x' && str[i + 1] == '^' && str[i + 2] == '2')
        {
            *coef_x2 += num;
            i += 3; // Passer 'x^2'
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

    // Diviser l'équation en deux parties : gauche et droite
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

    // Supprimer les parenthèses et analyser les côtés
    char gauche_sans_parentheses[100], droite_sans_parentheses[100];
    traiter_parentheses(gauche, gauche_sans_parentheses);
    traiter_parentheses(droite, droite_sans_parentheses);

    analyser_cote_second_degre(gauche_sans_parentheses, &coef_x2_gauche, &coef_x_gauche, &constante_gauche);
    analyser_cote_second_degre(droite_sans_parentheses, &coef_x2_droite, &coef_x_droite, &constante_droite);

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
            (input[i] == 'x' && input[i + 1] != ' ') || input[i] == 'V' || input[i] == '(' || input[i] == '-')
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
    char texte1[100], equations1[100], equation_traitee1[100];
    ;
    const char equation[] = "firy x raha -4x=-4"; // Exemple d'équation
    separer_phrase(equation, texte1, equations1);
    printf("Texte: %s\n", texte1);
    printf("Equation premier degrer: %s\n", equations1);
    traiter_racine_carre(equations1, equation_traitee1);
    resoudre_equation(equation_traitee1);

    const char input[] = "firy x raha x_2-3x-9=1";
    char texte[100], equations_de[100], equation_traitee[100];
    ; // Tableau pour stocker les résultats

    separer_phrase(input, texte, equations_de); // Exemple d'équation du second degré
    printf("Texte: %s\n", texte);
    printf("Equation second degrer: %s\n", equations_de);
    traiter_racine_carre(equations_de, equation_traitee);
    resoudre_second_degre(equation_traitee);

    const char input2[] = "firy f(-2) raha 1+x_2=1";
    char texte2[100], equation2[100];
    int valeur_f = 0;

    separer_phrase_calculeX(input2, texte2, equation2, &valeur_f);

    printf("Texte : %s\n", texte2);
    printf("Équation : %s\n", equation2);
    printf("Valeur de f : %d\n", valeur_f);

    int resultat = calculer_f(equation2, valeur_f);

    printf("Résultat de f(%d) = %d\n", valeur_f, resultat);
    return 0;
}
