#include <iostream>
#include "plocica.h"
#include "grid.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <unistd.h>

#define FONT_SIZE_SMALL 0.012 * sf::VideoMode::getDesktopMode().width
#define FONT_SIZE_BIG 0.03 * sf::VideoMode::getDesktopMode().width
#define DEFAULT_SIZE_PRAVILA sf::VideoMode::getDesktopMode().width * 2 / 3, sf::VideoMode::getDesktopMode().height * 4 / 5
#define DEFAULT_SIZE_NOT_FULL_SCREEN sf::VideoMode::getDesktopMode().height * 4 / 5, sf::VideoMode::getDesktopMode().height * 4 / 5
#define DEFAULT_SIZE_FULL_SCREEN sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height

using namespace std;

int main()
{
    // izrada prozora
    sf::RenderWindow prozor;
    auto racunalo = sf::VideoMode::getDesktopMode();
    prozor.create(sf::VideoMode(DEFAULT_SIZE_PRAVILA), "Continuo pravila");
    sf::Vector2i pozicija(racunalo.width / 2 - prozor.getSize().x / 2, racunalo.height / 2 - prozor.getSize().y / 2 * 3);
    prozor.setPosition(pozicija);

    // potrebni alati na prozoru
    sf::Text naslov;
    sf::Text gumbText;
    sf::Font font;
    sf::Text pravila;

    // ucitavanje fonta
    if (!font.loadFromFile("./Merriweather/Merriweather-Black.ttf"))
    {
        cout << "ERROR" << endl;
        system("pause");
    }

    // napravimo naslov
    naslov.setFont(font);
    naslov.setString("Pravila Igre");
    naslov.setCharacterSize(FONT_SIZE_BIG);
    naslov.setFillColor(sf::Color(111, 78, 55));
    naslov.setStyle(sf::Text::Style::Bold);
    naslov.setPosition(prozor.getSize().x / 2 - naslov.getLocalBounds().width / 2, 0);

    // napravimo pravila
    pravila.setFont(font);
    pravila.setString("Igra Continuo igra se tako da svaki igrac na svom potezu postavlja jednu plocicu \n na veliko kvadratno polje, pri cemu ju moze rotirati. Novo postavljena plocica \n mora dodirivati, bez preklapanja, jednu ili vise postojecih plocica i mora  \nbiti poravnata s kvadraticima na plocicama. Igrac osvaja bod za svaki kvadratic\nna novopostavljenoj plocici spojen s istoobojanim kvadraticima na vec \npostavljenim plocicama, pri cemu se na broj vec osvojenih bodova dodaje broj \nkvadratica koji cine neprekidno podrucje s pocetkom na novopostavljenoj \nplocici. Neprekidno podrucje cini niz spojenih kvadratica u istoj boji. \n\nIgra se igra sve dok se ne potrose sve plocice, a pobjednik je onaj koji osvoji \nvise bodova. \n\nUPUTA: \nAko ne zelis igrati u fullscreenu, stisni tipku ESC, a ako se pozelis vratiti \nu fullscreen mozes stisnuti tipku F11 i tako mijenjati velicinu zaslona. Plocica \nse rotira pritiskom tipke r. Nadalje, po polju se mozes kretati strelicama, a \npostoji opcija i zoomiranja i odzoomiranja kako bi kao igrac mogao/la imati \npregled nad cijelom situacijom.\n\nU ovoj verziji igra se protiv racunala i jako je tesko pobijediti, stoga pokreni \nigru i pokusaj nadmudriti racunalo! Sretno!");
    pravila.setCharacterSize(FONT_SIZE_SMALL);
    pravila.setFillColor(sf::Color(111, 78, 55));
    pravila.setStyle(sf::Text::Style::Regular);
    pravila.setPosition(sf::Vector2f(prozor.getSize().x / 2 - pravila.getLocalBounds().width / 2, prozor.getSize().y / 2 - naslov.getCharacterSize() - pravila.getLocalBounds().height / 2));

    cout << "prozor size " << racunalo.width << " " << racunalo.height << endl;

    // napravimo gumb start koji se sastoji od texta i pravokutnika
    gumbText.setFont(font);
    gumbText.setString("Start");
    gumbText.setCharacterSize(FONT_SIZE_BIG);
    gumbText.setFillColor(sf::Color(255, 239, 222));
    gumbText.setPosition(sf::Vector2f(prozor.getSize().x / 2.f - gumbText.getLocalBounds().width / 2.f, prozor.getSize().y * 1.f - naslov.getCharacterSize() * 2.f));

    sf::RectangleShape gumbStart(sf::Vector2f(gumbText.getLocalBounds().width * 1.3f, 1.2f * gumbText.getCharacterSize()));
    gumbStart.setFillColor(sf::Color(111, 78, 55));
    gumbStart.setPosition(sf::Vector2f(prozor.getSize().x / 2.f - gumbStart.getLocalBounds().width / 2.f, prozor.getSize().y * 1.f - naslov.getCharacterSize() * 2.f));

    // bavimo se kursorom i ucitavamo kursor
    sf::Cursor ruka, strelica;
    if (!ruka.loadFromSystem(sf::Cursor::Hand))
    {
        cout << "Could not load hand cursor" << endl;
    }
    if (!strelica.loadFromSystem(sf::Cursor::Arrow))
    {
        cout << "Could not load arrow cursor" << endl;
    }

    // koristit cemo varijablu u slucaju promjene velicine prozora
    bool changeProzor = false, crtajObrub = false, krajIgre = false;

    // generiramo svoje plocice i  konstruktorom inicijaliziramo pocetni pogled
    vector<plocica> plocice = generiraj();
    grid polje(plocice.back(), 141, 141, 50);
    plocice.pop_back();
    sf::Vector2f gridStats(-1.0f, -1.0f);

    // uzimanje prve plocice
    plocica tr_plocica = plocice.back();
    plocice.pop_back();

    while (prozor.isOpen())
    {
        // biramo pozicije na prozoru za gumb, mis
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

            // animacija da gumb mijenja boju ako dodemo misem do njega
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
            // provjera je li plocica u poziciji za polaganje na polje
            if (d.type == sf::Event::MouseMoved && changeProzor && polje.provjeriPoziciju(mousePos, gridStats))
            {
                crtajObrub = true;
            }
            else
            {
                crtajObrub = false;
            }

            // provjera koristenja kotacica za zoomiranje polja
            if (d.type == sf::Event::MouseWheelMoved)
            {
                if (d.mouseWheel.delta < 0)
                {
                    polje.zoomOut();
                }
                if (d.mouseWheel.delta > 0)
                {
                    polje.zoomIn();
                }
            }
        }

        // otvaranje novog prozora i pocetak igranja Continuoa
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x > gumbPos.x && mousePos.x < gumbPos.x + gumbWiHi.x && mousePos.y > gumbPos.y && mousePos.y < gumbPos.y + gumbWiHi.y && !changeProzor)
        {
            changeProzor = true;
            prozor.create(sf::VideoMode(DEFAULT_SIZE_FULL_SCREEN), "Continuo", sf::Style::Fullscreen);
        }

        // s Esc cemo izlaziti van iz igrice ako ne zelimo zavrsiti partiju
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            sf::Vector2u sz(DEFAULT_SIZE_NOT_FULL_SCREEN);
            prozor.create(sf::VideoMode(DEFAULT_SIZE_NOT_FULL_SCREEN), "Continuo", sf::Style::Close | sf::Style::Titlebar);
            prozor.setPosition(pozicija);
        }

        // F11 mijenja velicinu prozora
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && changeProzor)
        {
            prozor.create(sf::VideoMode(DEFAULT_SIZE_FULL_SCREEN), "Continuo", sf::Style::Fullscreen);
        }
        // plocica se rotira
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            while (usleep(100))
                ;
            tr_plocica.rotiraj();
        }

        // stavljanje plocice na polje
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && polje.provjeriPoziciju(mousePos, gridStats))
        {
            sf::Vector2i koordinate = polje.getKoordinate(mousePos, gridStats);
            polje.postaviPlocicu(koordinate.x + 2, koordinate.y + 1, tr_plocica);
            int tr = polje.racunajBodoveZaPlocicu(koordinate.x + 2, koordinate.y + 1, tr_plocica);
            tr_plocica = plocice.back();
            plocice.pop_back();
            cout << tr << endl;

            polje.greedyPozicija(gridStats, tr_plocica);
            tr_plocica = plocice.back();
            plocice.pop_back();
        }

        // pomicanje ekrana
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            polje.moveDown();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            polje.moveUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            polje.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            polje.moveRight();
        }
        // stvara prikaz prozora
        if (krajIgre)
        {
        }
        else if (!changeProzor)
        {
            prozor.clear(sf::Color(255, 239, 222));
            prozor.draw(naslov);
            prozor.draw(gumbStart);
            prozor.draw(gumbText);
            prozor.draw(pravila);
        }
        else
        {
            prozor.clear(sf::Color::White);
            gridStats = polje.crtajGrid(prozor);
            if (crtajObrub)
                tr_plocica.crtajRub(prozor, gridStats, mousePos);
            tr_plocica.crtajPlocicu(prozor, gridStats, mousePos);
        }
        prozor.display();
    }
}
