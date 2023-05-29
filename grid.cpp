#include <iostream>
#include <cmath>
#include "plocica.h"
#include "grid.h"
#include <SFML/Graphics.hpp>

#define Crvena 1
#define Plava 2
#define Zelena 3
#define Zuta 4

// konstruktori

grid::grid() {}

grid::grid(plocica pl)
{
    postaviPlocicu(166, 165, pl);
}

grid::grid(plocica pl, int x, int y, int velicina)
{
    postaviPlocicu(166, 165, pl);
    this->velicina = velicina;
    this->pozicija.x = x;
    this->pozicija.y = y;
}

// getteri i setteri
void grid::setPozicija(sf::Vector2i pozicija)
{
    this->pozicija = pozicija;
}

void grid::setVelicina(int velicina)
{
    this->velicina = velicina;
}

sf::Vector2i grid::getPosition()
{
    return pozicija;
}

int grid::getVelicina()
{
    return velicina;
}

// funkcije za izradu grida

void grid::nullirajVisited()
{
    for (int i = 0; i < 332; i++)
    {
        memset(visited[i], 0, 332 * sizeof(bool));
    }
}

int grid::postaviPlocicu(int x, int y, plocica pl)
{
    int i, j, bx = 0, by = 0, sum = 0;
    // cistimo polje visited
    nullirajVisited();
    // postavi plocicu na polje
    for (i = x - 2; i < x + 2; i++)
    {
        for (j = y - 1; j < y + 3; j++)
        {
            this->polje[i][j] = pl.polje[bx][by];
            by++;
        }
        by = 0;
        bx++;
    }
    // racunaj bodove
    // 1. ispitaj susjede
    // provjeravamo lijeve i desne susjede
    bool vrh;
    for (i = x - 1; i < x + 3; i++)
    {
        // provjera lijevo
        if (polje[i][y - 3] && polje[i][y - 3] == polje[i][y - 2])
        {

            cout << "lijevo " << i << " " << y - 2 << endl;
            sum += dfs(i, y - 2, polje[i][y - 3]);
        }
        // provejera desno
        if (polje[i][y + 2] && polje[i][y + 2] == polje[i][y + 1])
        {
            cout << "desno " << i << " " << y - 2 << endl;
            sum += dfs(i, y + 1, polje[i][y + 2]);
        }
    }

    // provjeravamo gornje i donje susjede
    for (j = y - 2; j < y + 2; j++)
    {
        vrh = j == y - 2 || j == y + 1;
        // provjera gore
        if (polje[x - 2][j] && polje[x - 2][j] == polje[x - 1][j] && !visited[x - 1][j])
        {
            cout << "gore " << x - 2 << " " << j << endl;
            sum += dfs(x - 1, j, polje[x - 1][j]);
        }
        // provjera dolje
        if (polje[x + 3][j] && polje[x + 3][j] == polje[x + 2][j] && !visited[x + 2][j])
        {
            cout << "dolje " << x + 2 << " " << j << endl;
            sum += dfs(x + 2, j, polje[x + 2][j]);
        }
    }
    return sum;
}

// ne moramo li pamtiti boju za koju radimo dfs

int grid::dfs(int x, int y, int boja)
{

    // zaustavni uvjeti
    // 1 petlja
    if (visited[x][y] == 1)
        return 0;

    if (polje[x][y] != boja)
        return 0;

    visited[x][y] = 1;
    cout << x << " " << y << endl;
    return 1 + dfs(x - 1, y, boja) + dfs(x + 1, y, boja) + dfs(x, y - 1, boja) + dfs(x, y + 1, boja);
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

sf::Vector2f grid::crtajGrid(sf::RenderWindow &prozor)
{

    int i, j;
    float stranica = 1.f * prozor.getSize().y / velicina;
    float offsetx = (prozor.getSize().x - prozor.getSize().y) / 2;
    sf::Vector2f ret(stranica, offsetx);
    // cout << prozor.getSize().y << " " << prozor.getSize().x << " " << stranica << endl;
    for (i = pozicija.x; i < pozicija.x + velicina; i++)
    {
        for (j = pozicija.y; j < pozicija.y + velicina; j++)
        {
            sf::RectangleShape element(sf::Vector2f(stranica, stranica));
            if (polje[i][j] == 0)
            {
                element.setFillColor(sf::Color::White);
            }
            else if (polje[i][j] == Crvena)
            {
                element.setFillColor(sf::Color::Red);
            }
            else if (polje[i][j] == Plava)
            {
                element.setFillColor(sf::Color::Blue);
            }
            else if (polje[i][j] == Zelena)
            {
                element.setFillColor(sf::Color::Green);
            }
            else if (polje[i][j] == Zuta)
            {
                element.setFillColor(sf::Color::Yellow);
            }
            element.setOutlineColor(sf::Color::Black);
            element.setOutlineThickness(1.0);
            element.setPosition(sf::Vector2f(stranica * (i - pozicija.x) + offsetx, stranica * (j - pozicija.y)));
            prozor.draw(element);
        }
    }
    return ret;
}

sf::Vector2i grid::getKoordinate(sf::Vector2i &mousePos, sf::Vector2f &gridStats)
{

    sf::Vector2i mousePosGrid(floor((mousePos.x - gridStats.y) / gridStats.x), floor(mousePos.y / gridStats.x));
    sf::Vector2i plocicaPos(pozicija.x + mousePosGrid.x - 2, pozicija.y + mousePosGrid.y - 1);
    return plocicaPos;
}

bool grid::provjeriPoziciju(sf::Vector2i &mousePos, sf::Vector2f &gridStats)
{
    if (gridStats.x < 0 || gridStats.y < 0)
    {
        return false;
    }
    sf::Vector2i plocicaPos = getKoordinate(mousePos, gridStats);
    int i, j;
    // provjeravamo je li podrucje za plocicu u gridu popunjeno
    for (i = plocicaPos.x; i < plocicaPos.x + 4; i++)
    {
        for (j = plocicaPos.y; j < plocicaPos.y + 4; j++)
        {
            if (polje[i][j])
                return false;
        }
    }

    // provjeravamo lijeve i desne susjede
    for (i = plocicaPos.x; i < plocicaPos.x + 4; i++)
    {
        if (polje[i][plocicaPos.y - 1] || polje[i][plocicaPos.y + 4])
            return true;
    }

    // provjeravamo gornje i donje susjede
    for (j = plocicaPos.y; j < plocicaPos.y + 4; j++)
    {
        if (polje[plocicaPos.x - 1][j] || polje[plocicaPos.x + 4][j])
            return true;
    }

    return false;
}

// funkcije za animaciju polja

void grid::zoomIn()
{
    if (velicina >= 10)
    {
        velicina -= 2;
    }
}

void grid::zoomOut()
{
    if (velicina + pozicija.x < 332 && velicina + pozicija.y < 332)
    {
        velicina += 2;
    }
}

void grid::moveLeft()
{

    if (pozicija.x > 0)
    {
        pozicija.x--;
    }
}

void grid::moveRight()
{
    if (velicina + pozicija.x < 300)
    {
        pozicija.x++;
    }
}
void grid::moveUp()
{
    if (pozicija.y > 10)
    {
        pozicija.y--;
    }
}
void grid::moveDown()
{
    if (pozicija.y < 300)
    {
        pozicija.y++;
    }
}