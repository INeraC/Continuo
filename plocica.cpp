#include <iostream>
#include <SFML/Graphics.hpp>
#include "plocica.h"
#include <vector>
#include <time.h>

#define Crvena 1
#define Plava 2
#define Zelena 3
#define Zuta 4

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

bool plocica::iste(plocica p)
{
    int i, j;
    bool iste = true;
    bool rotirane = true;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (polje[i][j] != p.polje[i][j])
                iste = false;
        }
    }
    p.rotiraj();
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (polje[i][j] != p.polje[i][j])
                rotirane = false;
        }
    }

    if (rotirane || iste)
        return true;

    return false;
}

vector<plocica> generiraj()
{
    srand(unsigned(time(NULL)));
    vector<plocica> ret;
    int i, j, k;

    // generiranje plocica s dvije boje

    for (i = 1; i < 5; i++)
    {
        for (j = 1; j < 5; j++)
        {
            if (i >= j)
                continue;

            ret.push_back(plocica(i, j, j, i));
        }
    }

    for (i = 1; i < 5; i++)
    {
        for (j = 1; j < 5; j++)
        {

            // slucaj kada su sva cetiri vrha obojana istom bojom
            for (k = 1; k < 5; k++)
            {
                if (j >= k || j == i || k == i)
                    continue;
                plocica p(i, j, i, k);
                ret.push_back(p);
            }

            // slucaj kada su vrhovi obojani razlicitim bojama
            for (k = 1; k < 5; k++)
            {
                if (i == j || i == k || j == k)
                    continue;

                ret.push_back(plocica(i, k, j, i));
            }
        }
    }

    // for(i = 0; i < ret.size();i++){
    //     for( j = 0; j < ret.size(); j++){
    //         if( i== j)
    //             continue;

    //         if(ret[i].iste(ret[j])){
    //             cout<<"Error"<<endl;
    //         }
    //     }

    random_shuffle(ret.begin(), ret.end());
    return ret;
}

// crtaj plocicu s obzirom na poziciju misa
bool plocica::crtajPlocicu(sf::RenderWindow &prozor, sf::Vector2f &gridStats, sf::Vector2i &mousePos)
{
    int i, j;
    sf::Vector2f pozicijaBase(mousePos.x - 2.5f * gridStats.x, mousePos.y - 1.5f * gridStats.x);

    if (mousePos.x - 0.5f * gridStats.x < gridStats.y || mousePos.x + 0.5f * gridStats.x > prozor.getSize().x - gridStats.y)
        return false;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            sf::Vector2f pozicija(pozicijaBase.x + i * gridStats.x, pozicijaBase.y + j * gridStats.x);

            if (pozicija.x < gridStats.y || pozicija.x > prozor.getSize().x - gridStats.y)
                continue;

            sf::RectangleShape element(sf::Vector2f(gridStats.x, gridStats.x));

            if (polje[i][j] == Crvena)
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
            element.setPosition(pozicija);
            prozor.draw(element);
        }
    }
    return true;
}

// crtaj obrub plocice

void plocica::crtajRub(sf::RenderWindow &prozor, sf::Vector2f &gridStats, sf::Vector2i &mousePos)
{
    sf::Vector2f pozicijaBase(mousePos.x - 2.5f * gridStats.x, mousePos.y - 1.5f * gridStats.x);
    sf::RectangleShape obrub(sf::Vector2f(gridStats.x * 4, gridStats.x * 4));
    obrub.setOutlineColor(sf::Color::Black);
    obrub.setOutlineThickness(3.0);
    obrub.setPosition(pozicijaBase);
    prozor.draw(obrub);
}

// int main(){
//     vector<plocica> pl;
//     pl = generiraj();
//     return 0;
// }