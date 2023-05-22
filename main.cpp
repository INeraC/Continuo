#include <iostream>
#include "plocica.h"
#include <SFML/Graphics.hpp>

#define FONT_SIZE_BIG 100

using namespace std;

#define DEFAULT_SIZE sf::VideoMode::getDesktopMode().width * 2 / 3, sf::VideoMode::getDesktopMode().height * 4 / 5

int main()
{
    sf::RenderWindow prozor;
    auto racunalo = sf::VideoMode::getDesktopMode();
    prozor.create(sf::VideoMode(DEFAULT_SIZE), "Continuo pravila");
    sf::Vector2i pozicija(racunalo.width / 2 - prozor.getSize().x / 2, racunalo.height / 2 - prozor.getSize().y / 2 * 3);
    prozor.setPosition(pozicija);
    sf::Text naslov;
    sf::Text gumbText;
    sf::Font font;
    sf::Text pravila;
    if (!font.loadFromFile("./Merriweather/Merriweather-Black.ttf"))
    {
        cout << "ERROR" << endl;
        system("pause");
    }
    naslov.setFont(font);
    naslov.setString("Pravila Igre");
    naslov.setCharacterSize(FONT_SIZE_BIG);
    naslov.setFillColor(sf::Color(111, 78, 55));
    naslov.setStyle(sf::Text::Style::Bold);
    naslov.setPosition(prozor.getSize().x / 2 - naslov.getLocalBounds().width / 2, 0);

    // pravila.setFont(font);
    // pravila.setString("Pomiješajte pločice i stavite ih licem prema dolje. Uzmite gornju pločicu i stavite je licem prema gore na stol. U svakom potezu igrač koji je na potezu uzima gornju pločicu i dodaje je na stol. Nova pločica mora dodirivati, bez preklapanja, jednu ili više postojećih pločica i mora biti poravnata s kvadratićima na pločicama. Igrač osvaja bod za svaki kvadratić u obojenim područjima koja su uvećana novom pločicom. Područje čini niz kvadratića iste boje, pri čemu se računaju kvadratići na postojećim pločicama kao i na novoj pločici.");
    // pravila.setFillColor(sf::Color(255, 239, 222));
    // pravila.setPosition(sf::Vector2f(0.f, naslov.getLocalBounds().height * 4 / 3.f));

    gumbText.setFont(font);
    gumbText.setString("Start");
    gumbText.setCharacterSize(FONT_SIZE_BIG);
    gumbText.setFillColor(sf::Color(255, 239, 222));
    gumbText.setPosition(sf::Vector2f(prozor.getSize().x / 2.f - gumbText.getLocalBounds().width / 2.f, prozor.getSize().y * 1.f - naslov.getCharacterSize() * 2.f));

    sf::RectangleShape gumbStart(sf::Vector2f(gumbText.getLocalBounds().width * 1.3f, 1.2f * gumbText.getCharacterSize()));
    gumbStart.setFillColor(sf::Color(111, 78, 55));
    gumbStart.setPosition(sf::Vector2f(prozor.getSize().x / 2.f - gumbStart.getLocalBounds().width / 2.f, prozor.getSize().y * 1.f - naslov.getCharacterSize() * 2.f));

    sf::Cursor ruka, strelica;
    if (!ruka.loadFromSystem(sf::Cursor::Hand))
    {
        cout << "Could not load hand cursor" << endl;
    }
    if (!strelica.loadFromSystem(sf::Cursor::Arrow))
    {
        cout << "Could not load arrow cursor" << endl;
    }

    bool changeProzor = false;

    while (prozor.isOpen())
    {
        sf::Event d;
        sf::Vector2i mousePos = sf::Mouse::getPosition(prozor);
        sf::Vector2i gumbPos(gumbStart.getPosition());
        sf::Vector2i gumbWiHi(gumbStart.getGlobalBounds().width, gumbStart.getGlobalBounds().height);
        while (prozor.pollEvent(d))
        {
            if (d.type == sf::Event::Closed)
            {
                prozor.close();
            }

            if (d.type == sf::Event::MouseMoved && !changeProzor)
            {

                if (mousePos.x > gumbPos.x && mousePos.x < gumbPos.x + gumbWiHi.x && mousePos.y > gumbPos.y && mousePos.y < gumbPos.y + gumbWiHi.y)
                {
                    gumbStart.setFillColor(sf::Color(211, 182, 156));
                    gumbText.setStyle(sf::Text::Style::Bold);
                    prozor.setMouseCursor(ruka);
                }
                else
                {
                    gumbStart.setFillColor(sf::Color(111, 78, 55));
                    gumbText.setStyle(sf::Text::Style::Regular);
                    prozor.setMouseCursor(strelica);
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x > gumbPos.x && mousePos.x < gumbPos.x + gumbWiHi.x && mousePos.y > gumbPos.y && mousePos.y < gumbPos.y + gumbWiHi.y && !changeProzor)
        {
            changeProzor = true;
            prozor.create(sf::VideoMode(DEFAULT_SIZE), "Continuo", sf::Style::Fullscreen);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            sf::Vector2u sz(DEFAULT_SIZE);
            prozor.create(sf::VideoMode(DEFAULT_SIZE), "Continuo", sf::Style::Default);
            prozor.setPosition(pozicija);
        }
        prozor.clear(sf::Color(255, 239, 222));
        if (!changeProzor)
        {

            prozor.draw(naslov);
            prozor.draw(gumbStart);
            prozor.draw(gumbText);
            prozor.draw(pravila);
        }
        else
        {
        }
        prozor.display();
    }
}