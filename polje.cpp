#include <iostream>
#include "plocica.h"
#include "polje.h"
#include <SFML/Graphics.hpp>

grid::grid() {}

void grid::postaviPlocicu(int x, int y, plocica pl)
{
    int i, j, bx = 0, by = 0;
    for (i = x - 1; i < x + 3; i++)
    {
        for (j = y - 1; j < y + 3; j++)
        {
            this->polje[i][j] = pl.polje[bx][by];
            by++;
        }
        by = 0;
        bx++;
    }
}

grid::grid(plocica pl)
{
    postaviPlocicu(165, 165, pl);
}

void grid::ispisiPolje(int x, int y)
{
    int i, j;
    for (i = x - 50; i < x + 50; i++)
    {
        for (j = y - 50; j < y + 50; j++)
        {
            cout << polje[i][j];
        }
        cout << endl;
    }
    cout << endl;
}