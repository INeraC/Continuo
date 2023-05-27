#ifndef plocica_h
#define plocica_h
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class plocica
{
public:
    int polje[4][4];
    plocica(int lijevi_kut, int lijevi_segment, int desni_kut, int desni_segment);
    void rotiraj();
    void ispisi();
    bool iste (plocica p);
    bool crtajPlocicu (sf::RenderWindow &prozor, sf::Vector2f &gridStats, sf::Vector2i &mousePos);
};

vector<plocica> generiraj();
#endif