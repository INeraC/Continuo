#include <iostream>
#include "plocica.h"
#include <SFML/Graphics.hpp>

using namespace std;

// void PrvailaIgre(sf::RenderWindow prozor)
// {
//     auto racunalo = sf::VideoMode::getDesktopMode();
//     prozor.create(sf::VideoMode(racunalo.width * 2 / 3, racunalo.height * 4 / 5, 32), "Continuo pravila");
//     sf::Vector2i pozicija(racunalo.width / 2 - prozor.getSize().x / 2, racunalo.height / 2 - prozor.getSize().y / 2 * 3);
//     prozor.setPosition(pozicija);
//     sf::Text naslov;
//     sf::Font font;
//     sf::Text pravila;
//     if (!font.loadFromFile("./Merriweather/Merriweather-Black.ttf"))
//     {
//         cout << "ERROR" << endl;
//         system("pause");
//     }
//     naslov.setFont(font);
//     naslov.setString("Pravila Igre");
//     naslov.setCharacterSize(100);
//     naslov.setFillColor(sf::Color(111, 78, 55));
//     naslov.setStyle(sf::Text::Style::Bold);
//     naslov.setPosition(prozor.getSize().x / 2 - naslov.getLocalBounds().width / 2, 0);
//     prozor.clear(sf::Color(255, 239, 222));
//     prozor.draw(naslov);
//     prozor.display();
// }

int main()
{
    sf::RenderWindow prozor;
    auto racunalo = sf::VideoMode::getDesktopMode();
    prozor.create(sf::VideoMode(racunalo.width * 2 / 3, racunalo.height * 4 / 5, 32), "Continuo pravila");
    sf::Vector2i pozicija(racunalo.width / 2 - prozor.getSize().x / 2, racunalo.height / 2 - prozor.getSize().y / 2 * 3);
    prozor.setPosition(pozicija);
    sf::Text naslov;
    sf::Text gumbText;
    sf::Font font;
    sf::Text pravila;
    sf::RectangleShape gumbStart(sf::Vector2f(prozor.getSize().x / 5, prozor.getSize().y / 15));
    if (!font.loadFromFile("./Merriweather/Merriweather-Black.ttf"))
    {
        cout << "ERROR" << endl;
        system("pause");
    }
    naslov.setFont(font);
    naslov.setString("Pravila Igre");
    naslov.setCharacterSize(100);
    naslov.setFillColor(sf::Color(111, 78, 55));
    naslov.setStyle(sf::Text::Style::Bold);
    naslov.setPosition(prozor.getSize().x / 2 - naslov.getLocalBounds().width / 2, 0);

    gumbText.setFont(font);
    gumbText.setString("Start");
    gumbText.setCharacterSize(100);
    gumbText.setFillColor(sf::Color(255, 239, 222));
    gumbText.setPosition(sf::Vector2f(prozor.getSize().x/2.f - gumbText.getLocalBounds().width/2.f, prozor.getSize().y*1.f - gumbStart.getLocalBounds().height*2.f));

    gumbStart.setFillColor(sf::Color(111, 78, 55));
    gumbStart.setPosition(sf::Vector2f(prozor.getSize().x/2.f - gumbStart.getLocalBounds().width/2.f, prozor.getSize().y*1.f - gumbStart.getLocalBounds().height*2.f));
    while (prozor.isOpen())
    {
        prozor.clear(sf::Color(255, 239, 222));
        prozor.draw(naslov);
        prozor.draw(gumbStart);
        prozor.draw(gumbText);
        prozor.display();

        sf::Event d;
        while (prozor.pollEvent(d))
        {
            if (d.type == sf::Event::Closed)
            {
                prozor.close();
            }
        }
    }
}