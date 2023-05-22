#include <iostream>
#include <SFML/Graphics.hpp>
#include "plocica.h"

#define CRVENA 1
#define PLAVA 2
#define ZUTA 3
#define ZELENA 4

using namespace std;

plocica::plocica(int lijevi_kut, int lijevi_segment, int desni_kut, int desni_segment)
{
    int i, j;
    // lijevi_kut
    polje[0][0] = polje[3][3] = lijevi_kut;

    // desni_kut
    polje[0][3] = polje[3][0] = desni_kut;

    // lijevi_segment
    polje[0][1] = polje[1][0] = polje[1][1] = polje[2][2] = polje[2][3] = polje[3][2] = lijevi_segment;

    // desni_segment
    polje[1][2] = polje[2][1] = polje[0][2] = polje[2][0] = polje[1][3] = polje[3][1] = desni_segment;
}

void plocica::rotiraj()
{
    int i, j, temp;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 2; j++)
        {
            temp = polje[i][j];
            polje[i][j] = polje[i][3 - j];
            polje[i][3 - j] = temp;
        }
    }
}

void plocica::ispisi()
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            cout << polje[i][j] << " ";
        }
        cout << endl;
    }
}
