#include <stdio.h>
#include <stdlib.h>

int factoriel(int nombre)
{
    if (nombre < 0)
    {
        return -1;
    }
    int resultat = 1;
    for (int i = 1; i <= nombre; i++)
    {
        resultat *= i;
    }
    return resultat;
}

int main()
{

    int a = 5;

    int resultat = factoriel(a);
    printf("%d", resultat);
    return 0;
}
