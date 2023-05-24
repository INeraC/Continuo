#ifndef polje_h
#define polje_h
#include <iostream>
#include "plocica.h"
#include <SFML/Graphics.hpp>
#include <string.h>

class grid
{
    static const int velicina_polja = 332;
    int polje[velicina_polja][velicina_polja] = {0};

public:
    grid();
    grid(plocica pl);
    void postaviPlocicu(int x, int y, plocica pl);
    void ispisiPolje(int x, int y);
};

#endif