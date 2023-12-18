#include "quiz.h"
#include "menu.h"
#include "Game.h"
#include <locale>
quiz::quiz(std::string flag)
{
	font.loadFromFile("ShipporiMincho-Regular.ttf");
    victorytexture.loadFromFile(flag);
    v.setTexture(victorytexture);
    v.setScale(130 / v.getLocalBounds().width, 90 / v.getLocalBounds().height);
    v.setPosition(175.f, 70.f);
    chaine = flag;
    for (int i = 0; i < 4; i++)
    {
        chaine.pop_back();
    }
}
void quiz::run(sf::RenderWindow& window2)
{
	sf::RenderWindow window({ 480 ,480 }, "quiz");
    sf::Text text("", font);
    text.setFillColor(sf::Color::Red);
    text.setPosition(175.f, 240.f);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered) 
            {
                if (std::isprint(event.text.unicode))
                    input_text += event.text.unicode;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::BackSpace)
                {
                    if (!input_text.empty())
                        input_text.pop_back();
                }
                
                if (event.key.code == sf::Keyboard::Return) {
                    std::for_each(input_text.begin(), input_text.end(), [](char& c) { c = ::tolower(c); });
                    if (input_text == chaine) //checking
                    {
                        window.close();
                        menu menu;
                        menu.endgame(window2);
                    }
                    else
                    {
                        window.close();
                        menu menu;
                        menu.defeatquiz(window2);
                    }
                }
            }
        }

        static sf::Time text_effect_time;
        static bool show_cursor;

        text_effect_time += clock.restart();

        if (text_effect_time >= sf::seconds(0.5f))
        {
            show_cursor = !show_cursor;
            text_effect_time = sf::Time::Zero;
        }

        text.setString(input_text + (show_cursor ? '_' : ' '));

        window.clear(sf::Color::White);
        window.draw(v);
        window.draw(text);
        window.display();
    }
}

quiz::~quiz()
{

}