#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct categorie
{
    char nom[50];
} categorie;

typedef struct aliment
{
    categorie cat_aliment;
    int calorie_max;
    int calorie_min;
    char nom[50];
    double prix_gramme;
} aliment;

typedef struct plat
{
    char nom[50];
    aliment *aliments;
    int nombre_aliment;
    int echelle_tsirony;
    double prix_total;
} plat;
typedef struct vente
{
    int date;
    char plat_nom[50];
    int quantite;
    double revenu_total;
} vente;

typedef struct resto
{
    plat *list_plats;
    int nombre_plats;
    vente *ventes_journalieres;
    int nombre_ventes;
} resto;

double valeur_plat(const plat *p)
{
    int total_calories = 0;
    for (int i = 0; i < p->nombre_aliment; i++)
    {
        int moyenne_calories = (p->aliments[i].calorie_max + p->aliments[i].calorie_min) / 2;
        total_calories += moyenne_calories;
    }
    return p->echelle_tsirony - 4 * total_calories;
}

double prix_plat(const plat *p)
{
    double total_prix = 0;
    for (int i = 0; i < p->nombre_aliment; i++)
    {
        total_prix += p->aliments[i].prix_gramme;
    }
    return total_prix;
}

plat *meilleur_plat(const resto *r)
{
    if (r->nombre_plats == 0 || r->list_plats == NULL)
    {
        printf("Aucun plat disponible ou liste invalide.\n");
        return NULL;
    }

    plat *meilleur = &r->list_plats[0];
    double meilleure_valeur = valeur_plat(meilleur);

    for (int i = 1; i < r->nombre_plats; i++)
    {
        double valeur = valeur_plat(&r->list_plats[i]);
        if (valeur > meilleure_valeur)
        {
            meilleur = &r->list_plats[i];
            meilleure_valeur = valeur;
        }
    }
    return meilleur;
}

plat *meilleur_plat_par_categorie(const resto *r, const char *categorie_nom)
{
    plat *meilleur = NULL;
    double meilleure_valeur = -1e9;

    for (int i = 0; i < r->nombre_plats; i++)
    {
        plat *p = &r->list_plats[i];
        int appartient_categorie = 0;

        for (int j = 0; j < p->nombre_aliment; j++)
        {
            if (strcmp(p->aliments[j].cat_aliment.nom, categorie_nom) == 0)
            {
                appartient_categorie = 1;
                break;
            }
        }

        if (appartient_categorie)
        {
            double valeur = valeur_plat(p);
            if (valeur > meilleure_valeur)
            {
                meilleur = p;
                meilleure_valeur = valeur;
            }
        }
    }
    return meilleur;
}

void liberer_plat(plat *p)
{
    if (p->aliments)
    {
        free(p->aliments);
    }
}

void liberer_resto(resto *r)
{
    if (r->list_plats)
    {
        for (int i = 0; i < r->nombre_plats; i++)
        {
            liberer_plat(&r->list_plats[i]);
        }
        free(r->list_plats);
    }
    if (r->ventes_journalieres)
    {
        free(r->ventes_journalieres);
    }
}

double enregistrer_vente(resto *r, int date, const char *plat_nom, int quantite)
{
    for (int i = 0; i < r->nombre_plats; i++)
    {
        if (strcmp(r->list_plats[i].nom, plat_nom) == 0)
        {
            double revenu = r->list_plats[i].prix_total * quantite;

            r->ventes_journalieres = realloc(r->ventes_journalieres, (r->nombre_ventes + 1) * sizeof(vente));

            vente nouvelle_vente = {date, "", quantite, revenu};
            strcpy(nouvelle_vente.plat_nom, plat_nom);
            r->ventes_journalieres[r->nombre_ventes] = nouvelle_vente;
            r->nombre_ventes++;

            return revenu;
        }
    }
    printf("Plat non trouvé : %s\n", plat_nom);
    return 0;
}
void afficher_statistiques_ventes_par_categorie(const resto *r, int date, const char *categorie_nom)
{
    printf("Statistiques des ventes pour la date %d et la catégorie '%s' :\n", date, categorie_nom);
    double revenu_total = 0;
    int ventes_trouvees = 0;

    for (int i = 0; i < r->nombre_ventes; i++)
    {

        if (r->ventes_journalieres[i].date == date)
        {

            for (int j = 0; j < r->nombre_plats; j++)
            {
                if (strcmp(r->ventes_journalieres[i].plat_nom, r->list_plats[j].nom) == 0)
                {
                    plat *p = &r->list_plats[j];
                    int appartient_categorie = 0;

                    for (int k = 0; k < p->nombre_aliment; k++)
                    {
                        if (strcmp(p->aliments[k].cat_aliment.nom, categorie_nom) == 0)
                        {
                            appartient_categorie = 1;
                            break;
                        }
                    }

                    if (appartient_categorie)
                    {
                        printf("Plat : %s, Quantité : %d, Revenu : %.2f\n",
                               r->ventes_journalieres[i].plat_nom,
                               r->ventes_journalieres[i].quantite,
                               r->ventes_journalieres[i].revenu_total);
                        revenu_total += r->ventes_journalieres[i].revenu_total;
                        ventes_trouvees++;
                    }
                }
            }
        }
    }

    if (ventes_trouvees == 0)
    {
        printf("Aucune vente enregistrée pour cette date et catégorie.\n");
    }
    else
    {
        printf("Revenu total pour la date %d et la catégorie '%s' : %.2f\n", date, categorie_nom, revenu_total);
    }
}

int main()
{
    aliment aliment1 = {{"Legume"}, 4, 1, "Carotte", 0.5};
    aliment aliment2 = {{"Legume"}, 4, 2, "Pates", 1.2};
    aliment aliment3 = {{"Legume"}, 3, 1, "Pomme de terre", 0.3};
    aliment aliment4 = {{"Legume"}, 3, 1, "Oignon", 0.4};

    plat *plats = malloc(3 * sizeof(plat));

    plats[0].aliments = malloc(3 * sizeof(aliment));
    plats[0].aliments[0] = aliment1;
    plats[0].aliments[1] = aliment2;
    plats[0].aliments[2] = aliment3;
    strcpy(plats[0].nom, "Soupe");
    plats[0].nombre_aliment = 3;
    plats[0].echelle_tsirony = 5;
    plats[0].prix_total = prix_plat(&plats[0]);

    plats[1].aliments = malloc(3 * sizeof(aliment));
    plats[1].aliments[0] = aliment1;
    plats[1].aliments[1] = aliment3;
    plats[1].aliments[2] = aliment4;
    strcpy(plats[1].nom, "Soupe de legumes");
    plats[1].nombre_aliment = 3;
    plats[1].echelle_tsirony = 7;
    plats[1].prix_total = prix_plat(&plats[1]);

    plats[2].aliments = malloc(1 * sizeof(aliment));
    plats[2].aliments[0] = aliment2;
    strcpy(plats[2].nom, "Soupe de pates");
    plats[2].nombre_aliment = 1;
    plats[2].echelle_tsirony = 3;
    plats[2].prix_total = prix_plat(&plats[2]);

    resto r = {plats, 3, NULL, 0};

    plat *meilleur = meilleur_plat(&r);
    if (meilleur)
    {
        printf("Le meilleur plat est : %s\n", meilleur->nom);
        printf("Valeur : %.2f, Prix total : %.2f\n",
               valeur_plat(meilleur), meilleur->prix_total);
    }
    const char *categorie_nom = "Legume";
    plat *meilleur_par_categorie = meilleur_plat_par_categorie(&r, categorie_nom);
    if (meilleur_par_categorie)
    {
        printf("Le meilleur plat dans la categorie '%s' est : %s\n",
               categorie_nom, meilleur_par_categorie->nom);
    }
    else
    {
        printf("Aucun plat trouvé dans la catégorie '%s'.\n", categorie_nom);
    }

    enregistrer_vente(&r, 20250110, "Soupe", 3);
    enregistrer_vente(&r, 20250110, "Soupe de pates", 2);

    afficher_statistiques_ventes_par_categorie(&r, 20250110, "Legume");
    afficher_statistiques_ventes_par_categorie(&r, 20250111, "Legume");

    liberer_resto(&r);

    return 0;
}
