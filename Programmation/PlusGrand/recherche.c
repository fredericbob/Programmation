#include <stdio.h>
#include <stdlib.h>

int rechercher(int tab[], int taille, int valeur)
{
    int resultat = valeur;
    for (int i = 0; i < taille; i++)
    {
        if (resultat == tab[i])
        {
            return i;
        }
    }
    return -1;
}

int main()
{

    int a[5] = {1, 2, 3, 4, 5};

    int resultat = rechercher(a, 5, 6);
    printf("%d", resultat);
    return 0;
}
