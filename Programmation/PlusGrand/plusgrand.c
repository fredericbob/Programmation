#include <stdio.h>
#include <stdlib.h>

int plusgrand(int a, int b, int c)
{
    int grand = a;
    if (b > grand)
    {
        grand = b;
    }
    if (c > grand)
    {
        grand = c;
    }

    return grand;
}

int main()
{

    int a = 5;
    int b = 10;
    int c = 12;

    int resultat = plusgrand(a, b, c);
    printf("%d", resultat);
    return 0;
}
