#include <stdio.h>
#include <math.h>

// int sum(int a, int b)
// {

//    int sum = a + b;

//    return sum;
// }

// int factorielle(int n)
// {
//    int val = 1;
//    for (int i = n; i > 0; i--)
//    {
//       val = val * i;
//    }

//    return val;
// }

int nombre_premier(int nbr)
{

   int milieu = nbr / 2;
   int count = 0;

   for (int i = 2; i < milieu; i++)
   {

      if (nbr % i == 0)
      {
         count++;
      }
   }

   if (count != 0)
   {

      printf("Le nombre n'est pas premier");
   }
   else
   {
      printf("Le nombre est premier");
   }

   return 0;
}

// void maxDeTrois(int a, int b, int c)
// {

//    if (a < b < c)
//    {
//       printf("%d es le plus grand\n", c);
//    }
//    else if (b < c < a)
//    {
//       printf("%d es le plus grand\n", a);
//    }
//    else
//    {
//       printf("%d es le plus grand\n", b);
//    }
// }

// void affichematrice(int matrice[3][3])
// {
//    for (int i = 0; i < 3; i++)
//    {
//       for (int j = 0; j < 3; j++)
//       {
//          printf("*");
//       }
//       printf("\n");
//    }
// }

// int trace_matrice(int matrice[3][3])
// {

//    int sum = 0;
//    for (int i = 0; i < 3; i++)
//    {
//       sum = sum + matrice[i][i];
//    }
//    printf("%d\n", sum);
//    int sum2 = 0;
//    for (int i = 0, j = 2; i < 3, j >= 0; i++, j--)
//    {
//       sum2 = sum2 + matrice[i][j];
//    }
//    printf("%d\n", sum2);

//    return 0;
// }

// float moyenne(float note[], int taille)
// {

//    float sum = 0;
//    for (int i = 0; i < taille; i++)
//    {
//       sum = sum + note[i];
//    }
//    float moyenne = sum / taille;

//    return moyenne;
// }

// float auDeSousDeLaMoyenne(float note[], int taille, float moyennes)
// {
//    *note = moyenne(note, taille);

//    for (int i = 0; i < taille; i++)
//    {
//       if (moyennes < note[i])
//       {

//          printf("vous etes au dessu de la moyenne\n");
//       }
//    }
//    printf("vous etes au dessou de la moyenne\n");
//    return 0;
// }

// void inveser_le_tableau(int tab[], int taille)
// {
//    for (int i = taille - 1; i >= 0; i--)
//    {
//       printf("%d ", tab[i]);
//    }
//    printf("\n");
// }

// int compter_Occurance(int tab[], int taille, int valeur)
// {

//    int repetition = 0;
//    for (int i = 0; i < taille; i++)
//    {
//       if (tab[i] == valeur)
//       {
//          repetition = repetition + 1;
//       }
//    }
//    return repetition;
// }

void produit_Matrices(int A[2][2], int B[2][2], int resultats[2][2])
{

   for (int i = 0; i < 2; i++)
   {
      for (int j = 0; j < 2; j++)
      {
         for (int k = 0; k < 2; k++)
         {
            resultats[i][j] += A[i][k] * B[k][j];
         }
      }
   }
   for (int i = 0; i < 2; i++)
   {
      for (int j = 0; j < 2; j++)
      {
         printf("%d ", resultats[i][j]);
      }
      printf("\n");
   }
}

float celsiusVersFahrenheit(float celsius)
{
   return (celsius * 1.8) + 32;
}

float fahrenheitVersCelsius(float fahrenheit)
{
   return (fahrenheit - 32) / 1.8;
}

int main()
{
   int MATRICE_A[2][2] = {{2, 2}, {1, 2}};
   int MATRICE_B[2][2] = {{2, 2}, {1, 2}};
   int resultats[2][2] = {0};

   // int tab[] = {1, 2, 3, 4, 4};
   // int taille = 5;

   // int sum1 = sum(2, 3);
   // printf("%d\n", sum1);

   // int facto = factorielle(5);
   // printf("la factorielle est %d\n", facto);

   // printf("Maximum:\n");
   // maxDeTrois(2, 3, 8);

   // int matrice[3][3];
   // printf("L'affichage de la matrice 3*3 est:\n");
   // affichematrice(matrice);

   // int matrice1[3][3] = {{1, 2, 3}, {1, 6, 5}, {1, 5, 4}};
   // printf("La matrice 3*3 est:\n");
   // trace_matrice(matrice1);

   // float note[] = {1.5, 1.5, 1.5, 1.5};
   // printf("la moyenne est:\n");
   // float moyennes = moyenne(note, taille);
   // printf("%lf\n", moyennes);

   // printf("MOYENNE\n");
   // auDeSousDeLaMoyenne(note, taille, 10.0);

   // printf("L'inversement du tableau est: \n");
   // inveser_le_tableau(tab, taille);

   // int valeur = 4;
   // printf("Le nombre d'occurence de %d est", valeur);
   // int result = compter_Occurance(tab, taille, valeur);
   // printf(" %d", result);
   printf("\n");
   nombre_premier(11);
   printf("\n");
   produit_Matrices(MATRICE_A, MATRICE_B, resultats);

   return 0;
}