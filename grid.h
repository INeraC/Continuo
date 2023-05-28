#ifndef grid_h
#define grid_h
#include <iostream>
#include "plocica.h"
#include <SFML/Graphics.hpp>
#include <string.h>

class grid
{
    static const int velicina_polja = 332;
    int polje[velicina_polja][velicina_polja] = {0};
    int xPoc, yPoc, velcina;

public:
    grid();
    grid(plocica pl);
    grid(plocica pl, int x, int y, int velicina);
    void postaviPlocicu(int x, int y, plocica pl);
    void ispisiGrid(int x, int y);
    sf::Vector2f crtajGrid(sf::RenderWindow &prozor, int x, int y, int velicina);
    bool provjeriPoziciju(sf::Vector2i &mousePos, sf::Vector2i &gridStats, int xPos, int yPos);
};

#endif