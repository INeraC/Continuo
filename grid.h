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
    bool visited[velicina_polja][velicina_polja] = {0};
    int velicina;
    sf::Vector2i pozicija;
    int dfs(int x, int y);
    void nullirajVisited();

public:
    grid();
    grid(plocica pl);
    grid(plocica pl, int x, int y, int velicina);

    sf::Vector2i getPosition();
    int getVelicina();
    void setVelicina(int brKockica);
    void setPozicija(sf::Vector2i pocetna_pozicija);

    int postaviPlocicu(int x, int y, plocica pl);
    void ispisiGrid(int x, int y);
    sf::Vector2f crtajGrid(sf::RenderWindow &prozor);
    bool provjeriPoziciju(sf::Vector2i &mousePos, sf::Vector2f &gridStats);
    sf::Vector2i getKoordinate(sf::Vector2i &mousePos, sf::Vector2f &gridtats);

    void zoomIn();
    void zoomOut();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};

#endif