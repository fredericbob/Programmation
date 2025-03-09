#include <stdio.h>
#include <stdlib.h>

struct hira
{
    int popularite;
    char *mpihira;
    char *titre;
    struct hira *suivant;
};
typedef struct hira Hira;

void ajouter_fin(Hira **list_hira, Hira *nouveau)
{
    if (nouveau == NULL)
        return;

    if (*list_hira == NULL)
    {
        *list_hira = nouveau;
        nouveau->suivant = NULL;
        return;
    }

    Hira **hira = list_hira;
    while (*hira != NULL)
    {
        hira = &(*hira)->suivant;
    }

    *hira = nouveau;
    nouveau->suivant = NULL;
}
// void afficher(Hira *list_hira, Hira *nouveau)
// {

//     ajouter_fin(list_hira, nouveau);
//     Hira *affichage = list_hira;

//     while (affichage[0].suivant != NULL)
//     {
//         affichage = affichage[0].suivant;
//         printf("Popularite:%d Chanteur:%s Chanson:%s", affichage->popularite, affichage->mpihira, affichage->titre);
//         printf("\n");
//     }
// }

// Hira *supprimer(Hira *list_hira, Hira *supprimer)
// {
//     Hira *sup = list_hira;
//     while (sup->suivant != NULL)
//     {
//         sup = sup->suivant;
//         if (sup->suivant == supprimer)
//         {
//             sup->suivant = sup->suivant->suivant;
//         }
//         printf("Popularite:%d Chanteur:%s Chanson:%s", sup->popularite, sup->mpihira, sup->titre);
//         printf("\n");
//     }
// }
int main()
{
    // Déclaration d'un pointeur pour la tête de liste
    Hira *HIRA = NULL;

    // Création des nœuds avec allocation dynamique
    Hira *h1 = (Hira *)malloc(sizeof(Hira));
    Hira *h2 = (Hira *)malloc(sizeof(Hira));
    Hira *h3 = (Hira *)malloc(sizeof(Hira));
    Hira *h4 = (Hira *)malloc(sizeof(Hira));

    if (!h1 || !h2 || !h3 || !h4)
    {
        printf("Erreur d'allocation mémoire\n");
        return 1;
    }

    // Initialisation des valeurs
    h1->popularite = 3;
    h1->mpihira = "micka";
    h1->titre = "manembona";
    h1->suivant = NULL;
    h2->popularite = 2;
    h2->mpihira = "manou";
    h2->titre = "malala";
    h2->suivant = NULL;
    h3->popularite = 4;
    h3->mpihira = "njara";
    h3->titre = "ny fo";
    h3->suivant = NULL;
    h4->popularite = 10;
    h4->mpihira = "hanta";
    h4->titre = "mahatsiaro";
    h4->suivant = NULL;

    // Construction de la liste
    HIRA = h1;
    h1->suivant = h2;
    h2->suivant = h3;

    // Ajout de h4 à la fin
    ajouter_fin(&HIRA, h4);

    return 0;
}
