#include <iostream>
#include "plocica.h"
#include "grid.h"
#include <SFML/Graphics.hpp>

#define Crvena 1
#define Plava 2
#define Zelena 3
#define Zuta 4

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

void grid::ispisiGrid(int x, int y)
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

// funkcija koja prima koordinate gornjeg lijevog te donjeg desnog vrha kvadrata koji ce biti prikazan i prozor te na tom prozoru crta taj dio grida

void grid::crtajGrid(sf::RenderWindow &prozor, int x, int y, int velicina)
{
    int i, j;
    unsigned stranica = prozor.getSize().y / (velicina);
    unsigned offset = (prozor.getSize().x - prozor.getSize().y) / 2;
    cout << prozor.getSize().y << " " << prozor.getSize().x<< endl;
    for (i = x; i < x + velicina; i++)
    {
        for (j = y; j < y + velicina; j++)
        {
            sf::RectangleShape element(sf::Vector2f(stranica, stranica));
            if (polje[i][j] == 0)
            {
                element.setFillColor(sf::Color::White);
                element.setOutlineColor(sf::Color::Black);
                element.setOutlineThickness(1.0);
                element.setPosition(sf::Vector2f(stranica * (i - x) + offset, stranica * (j - y)));
                prozor.draw(element);
            }
            else if (polje[i][j] == Crvena)
            {
                element.setFillColor(sf::Color::Red);
                element.setOutlineColor(sf::Color::Black);
                element.setOutlineThickness(1.0);
                element.setPosition(sf::Vector2f(stranica * (i - x) + offset, stranica * (j - y)));
                prozor.draw(element);
            }
            else if (polje[i][j] == Plava)
            {
                element.setFillColor(sf::Color::Blue);
                element.setOutlineColor(sf::Color::Black);
                element.setOutlineThickness(1.0);
                element.setPosition(sf::Vector2f(stranica * (i-x) + offset, stranica * (j-y)));
                prozor.draw(element);
            }
            else if (polje[i][j] == Zelena)
            {
                element.setFillColor(sf::Color::Green);
                element.setOutlineColor(sf::Color::Black);
                element.setOutlineThickness(1.0);
                element.setPosition(sf::Vector2f(stranica * (i-x) + offset, stranica * (j-y)));
                prozor.draw(element);
            }
            else if (polje[i][j] == Zuta)
            {
                element.setFillColor(sf::Color::Yellow);
                element.setOutlineColor(sf::Color::Black);
                element.setOutlineThickness(1.0);
                element.setPosition(sf::Vector2f(stranica * (i-x) + offset, stranica * (j-y)));
                prozor.draw(element);
            }
        }
    }
}