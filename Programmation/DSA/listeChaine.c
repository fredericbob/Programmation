#include <stdio.h>
#include <stdlib.h>

typedef struct Personne
{
    char *nom;
    int age;
    struct Personne *suivant;
} Personne;

Personne *ajoutepersonne(int age, char *nom)
{
    Personne *personne = (Personne *)malloc(sizeof(Personne));
    personne->age = age;
    personne->nom = nom;
    personne->suivant = NULL;
    return personne;
}

Personne *deletepersonne(Personne *head, Personne *noedsuprimer)
{

    if (head == noedsuprimer)
    {
        Personne *newhead = head->suivant;
        free(head);
        return newhead;
    }

    Personne *personne = head;

    while (personne->suivant && personne->suivant != noedsuprimer)
    {
        personne = personne->suivant;
    }

    if (personne->suivant == NULL)
    {
        return head;
    }

    Personne *temp = personne->suivant;
    personne->suivant = personne->suivant->suivant;
    free(temp);

    return head;
}

int minAge(Personne *personne)
{
    int minimum = personne->age;
    Personne *suivant = personne->suivant;

    while (suivant)
    {
        if (minimum > suivant->age)
        {
            minimum = suivant->age;
        }
        suivant = suivant->suivant;
    }
    return minimum;
}

void affiche(Personne *personne)
{
    while (personne)
    {
        printf("%d %s ->", personne->age, personne->nom);
        personne = personne->suivant;
    }
    printf("\n");
}

int main()
{

    Personne *personne1 = ajoutepersonne(9, "Bob");
    Personne *personne2 = ajoutepersonne(13, "Mckaella");
    Personne *personne3 = ajoutepersonne(12, "Sos");
    Personne *personne4 = ajoutepersonne(11, "Kal");
    Personne *personne5 = ajoutepersonne(10, "King");

    personne1->suivant = personne2;
    personne2->suivant = personne3;
    personne3->suivant = personne4;
    personne4->suivant = personne5;
    personne5->suivant = NULL;

    personne1 = deletepersonne(personne1, personne4);
    affiche(personne1);

    int result = minAge(personne1);

    printf("Age minimum est : %d", result);

    free(personne1);
    free(personne2);
    free(personne3);
    free(personne4);
    free(personne5);
    return 0;
}