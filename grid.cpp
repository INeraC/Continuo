#include <iostream>
#include <cmath>
#include "plocica.h"
#include "grid.h"
#include <SFML/Graphics.hpp>


#define Crvena 1
#define Plava 2
#define Zelena 3
#define Zuta 4


//! konstruktori
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


//! getteri i setteri
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


//!funckija za postavljanje plocice
void grid::postaviPlocicu(int x, int y, plocica pl)
{
    int i, j, bx = 0, by = 0;
    // postavljamo plocicu na polje
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
}


//!funkcija za brisanje plocice
void grid::obrisiPlocicu(int x, int y, plocica pl)
{
    int i, j;
    // brisemo plocicu
    for (i = x - 2; i < x + 2; i++)
    {
        for (j = y - 1; j < y + 3; j++)
        {
            this->polje[i][j] = 0;
        }
    }
}


//!funkcij za ispis grida
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


//! funkcija koja prima koordinate gornjeg lijevog te donjeg desnog vrha kvadrata koji ce biti prikazan i prozor te na tom prozoru crta taj dio grida
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


//!funkcija za dohvacanje koordinata iz pozicije misa na screenu
sf::Vector2i grid::getKoordinate(sf::Vector2i &mousePos, sf::Vector2f &gridStats)
{

    sf::Vector2i mousePosGrid(floor((mousePos.x - gridStats.y) / gridStats.x), floor(mousePos.y / gridStats.x));
    sf::Vector2i plocicaPos(pozicija.x + mousePosGrid.x - 2, pozicija.y + mousePosGrid.y - 1);
    return plocicaPos;
}


//!funkcija za provjeru je li moguce staviti plocicu sa misa na polje
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

    // provjeravamo gornje i donje susjede
    for (i = plocicaPos.x; i < plocicaPos.x + 4; i++)
    {
        if (polje[i][plocicaPos.y - 1] || polje[i][plocicaPos.y + 4])
            return true;
    }

    // provjeravamo lijeve i desne susjede
    for (j = plocicaPos.y; j < plocicaPos.y + 4; j++)
    {
        if (polje[plocicaPos.x - 1][j] || polje[plocicaPos.x + 4][j])
            return true;
    }

    return false;
}


//!funkcija za provjeru je li moguce staviti plocicu na polje
bool grid::provjeriPoziciju(sf::Vector2i &plocicaPos)
{
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

    // provjeravamo gornje i donje susjede
    for (i = plocicaPos.x; i < plocicaPos.x + 4; i++)
    {
        if (polje[i][plocicaPos.y - 1] || polje[i][plocicaPos.y + 4])
            return true;
    }

    // provjeravamo lijeve i desne susjede
    for (j = plocicaPos.y; j < plocicaPos.y + 4; j++)
    {
        if (polje[plocicaPos.x - 1][j] || polje[plocicaPos.x + 4][j])
            return true;
    }

    return false;
}


//! funkcije za izradu pomocnog grida
void grid::nullirajVisited()
{
    for (int i = 0; i < 332; i++)
    {
        memset(visited[i], 0, 332 * sizeof(bool));
    }
}


//!dfs
int grid::dfs(int x, int y, int boja)
{

    // zaustavni uvjeti
    if (visited[x][y] == 1)
        return 0;

    if (polje[x][y] != boja)
        return 0;

    visited[x][y] = 1;
    return 1 + dfs(x - 1, y, boja) + dfs(x + 1, y, boja) + dfs(x, y - 1, boja) + dfs(x, y + 1, boja);
}


//!funkcija za racunanje bodova
int grid::racunajBodoveZaPlocicu(int x, int y, plocica pl)
{
    int i, j, sum = 0;
    // cistimo polje visited
    nullirajVisited();
    // jako bitno je napomenuti da smo se u cijelom kodu s i kretali po stupcima, a s j po retcima pa su varijable
    // i i j zamijenjene u odnosu na inace

    // provjeravamo gornje i donje susjede
    for (i = x - 2; i < x + 2; i++)
    {
        // provjera gore
        if (polje[i][y - 2] && polje[i][y - 2] == polje[i][y - 1])
        {
            sum += dfs(i, y - 1, polje[i][y - 1]);
        }

        // provjera dolje
        if (polje[i][y + 3] && polje[i][y + 3] == polje[i][y + 2])
        {
            sum += dfs(i, y + 2, polje[i][y + 2]);
        }
    }

    // provjeravamo lijeve i desne susjede
    for (j = y - 1; j < y + 3; j++)
    {
        // provjera lijevo
        if (polje[x - 3][j] && polje[x - 3][j] == polje[x - 2][j] && !visited[x - 2][j])
        {
            sum += dfs(x - 2, j, polje[x - 2][j]);
        }

        // provjera desno
        if (polje[x + 2][j] && polje[x + 2][j] == polje[x + 1][j] && !visited[x + 1][j])
        {
            sum += dfs(x + 1, j, polje[x + 1][j]);
        }
    }
    return sum;
}


//!funkcija za greedy algoritam 
int grid::greedyPozicija(sf::Vector2f &gridStats, plocica pl)
{
    int i, j, max_br_bodova = -1, tr_bodovi, posx, posy;
    bool rotirana = false;

    for (i = 4; i < 332; i++)
    {
        for (j = 2; j < 332; j++)
        {
            sf::Vector2i pozicija(i - 2, j - 1);
            if (provjeriPoziciju(pozicija))
            {
                // provjera za obicnu plocicu
                postaviPlocicu(i, j, pl);
                tr_bodovi = racunajBodoveZaPlocicu(i, j, pl);
                // cout << i  << " " << j  <<" "<< tr_bodovi << endl;
                if (max_br_bodova < tr_bodovi)
                {
                    posx = i;
                    posy = j;
                    max_br_bodova = tr_bodovi;
                    rotirana = false;
                }
                obrisiPlocicu(i, j, pl);

                // provjera za rotiranu plocicu
                pl.rotiraj();
                postaviPlocicu(i, j, pl);
                tr_bodovi = racunajBodoveZaPlocicu(i, j, pl);
                // cout << i  << " " << j  <<" "<< tr_bodovi << endl;
                if (max_br_bodova < tr_bodovi)
                {
                    posx = i;
                    posy = j;
                    max_br_bodova = tr_bodovi;
                    rotirana = true;
                }
                obrisiPlocicu(i, j, pl);
                // rotiramo plocicu u pocetno stanje
                pl.rotiraj();
            }
        }
    }
    if (rotirana)
        pl.rotiraj();
    postaviPlocicu(posx, posy, pl);
    return max_br_bodova;
}


//! funkcije za animaciju polja
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