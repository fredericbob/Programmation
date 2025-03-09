#include <stdio.h>
#include <stdlib.h>

int *triBulle(int *a, int taille)
{
    for (int i = 0; i < taille - 1; i++)
    {
        for (int j = 0; j < taille - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    return a;
}

int *Triselection(int *a, int n)
{

    for (int i = 0; i < n - 1; i++)
    {

        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {

            if (a[minIndex] > a[j])
            {
                minIndex = j;
            }
        }
        int temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;
    }

    return a;
}

int *TriInsertion(int *a, int taille)
{

    for (int i = 1; i < taille; i++)
    {
        int cle = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > cle)
        {
            a[j + 1] = a[j];

            j--;
        }

        a[j + 1] = cle;
    }

    return a;
}

void triComptage(int *a, int n)
{
    int max = a[0];
    for (int i = 1; i < n; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
        }
    }

    int *count = (int *)calloc(max + 1, sizeof(int));
    if (count == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    for (int i = 0; i <= max; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        count[a[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= max; i++)
    {
        while (count[i] > 0)
        {
            a[index++] = i;
            count[i]--;
        }
    }
}
void affiche(int *resultat, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        printf("%d ", resultat[i]);
    }
}

int main()
{
    int a[] = {1, 4, 1, 3, 9, 2, 5};
    int n = sizeof(a) / sizeof(a[0]);
    // int *resultat = TriInsertion(a, n);

    triComptage(a, n);
    affiche(a, n);
    return 0;
}