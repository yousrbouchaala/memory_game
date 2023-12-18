#include "menu.h"
#include "Game.h"

menu::menu()
{//------backgrounds-------//
victorytexture.loadFromFile("youwin.png");
defeattexture.loadFromFile("youlose.png");
menutexture.loadFromFile("menuback.png");

//-------buttons-------//
//menubuttons
buttonsTextures[0].loadFromFile("exit2.png");
buttonsTextures[1].loadFromFile("exit1.png");
buttonsTextures[2].loadFromFile("play1.png");
buttonsTextures[3].loadFromFile("play2.png");
//victorybuttons
buttonsTexturesVictory[0].loadFromFile("exit2.png");
buttonsTexturesVictory[1].loadFromFile("exit1.png");
buttonsTexturesVictory[2].loadFromFile("nextgame.png");
buttonsTexturesVictory[3].loadFromFile("nextgame2.png");
//defeatbuttons
buttonsTexturesDefeat[0].loadFromFile("exit1.png");
buttonsTexturesDefeat[1].loadFromFile("exit2.png");
buttonsTexturesDefeat[2].loadFromFile("new2.png");
buttonsTexturesDefeat[3].loadFromFile("new.png");
//endgamebuttons
buttonsTexturesEnd[0].loadFromFile("exit1.png"); 
buttonsTexturesEnd[1].loadFromFile("exit2.png");
buttonsTexturesEnd[2].loadFromFile("menu.png");
buttonsTexturesEnd[3].loadFromFile("menu2.png");
//-------setting textures-------//
//menubuttons
buttons[0].setTexture(&buttonsTextures[0]);
buttons[1].setTexture(&buttonsTextures[2]);
//victorybuttons
buttonsVictory[0].setTexture(&buttonsTexturesVictory[0]);
buttonsVictory[1].setTexture(&buttonsTexturesVictory[2]);
//defeatbuttons
buttonsDefeat[0].setTexture(&buttonsTexturesDefeat[0]);
buttonsDefeat[1].setTexture(&buttonsTexturesDefeat[2]);
//endgamebuttons
buttonsEnd[0].setTexture(&buttonsTexturesEnd[0]);
buttonsEnd[1].setTexture(&buttonsTexturesEnd[2]);
//backgrounds
v.setTexture(victorytexture);
d.setTexture(defeattexture);
menuback.setTexture(menutexture);
//-------size-------//
//menubuttons
buttons[0].setSize(sf::Vector2f(60.f, 60.f));
buttons[1].setSize(sf::Vector2f(90.f,90.f));
//victorybuttons
buttonsVictory[0].setSize(sf::Vector2f(60.f, 60.f));
buttonsVictory[1].setSize(sf::Vector2f(90.f, 90.f));
//defeatbuttons
buttonsDefeat[0].setSize(sf::Vector2f(60.f, 60.f));
buttonsDefeat[1].setSize(sf::Vector2f(90.f, 90.f));
//endgamebuttons
buttonsEnd[0].setSize(sf::Vector2f(60.f, 60.f));
buttonsEnd[1].setSize(sf::Vector2f(90.f, 90.f));
//---------------//
v.setScale(700 / v.getLocalBounds().width, 700 / v.getLocalBounds().height);
menuback.setScale(700 / menuback.getLocalBounds().width, 700 / menuback.getLocalBounds().height);
d.setScale(700 / v.getLocalBounds().width, 700 / v.getLocalBounds().height);
//---------------//
for (int i = 0; i < 2; i++)
{
	buttons[i].setOrigin(buttons[i].getLocalBounds().width / 2, buttons[i].getLocalBounds().height / 2);
	buttonsVictory[i].setOrigin(buttonsVictory[i].getLocalBounds().width / 2, buttonsVictory[i].getLocalBounds().height / 2);
	buttonsDefeat[i].setOrigin(buttonsDefeat[i].getLocalBounds().width / 2, buttonsDefeat[i].getLocalBounds().height / 2);
	buttonsEnd[i].setOrigin(buttonsEnd[i].getLocalBounds().width / 2, buttonsEnd[i].getLocalBounds().height / 2);

}

buttons[0].setPosition(350.f, 400.f);
buttons[1].setPosition(350.f, 300.f);
buttonsVictory[0].setPosition(350.f, 400.f);
buttonsVictory[1].setPosition(350.f, 300.f);
buttonsDefeat[0].setPosition(350.f, 400.f);
buttonsDefeat[1].setPosition(350.f, 300.f);
buttonsEnd[0].setPosition(350.f, 400.f);
buttonsEnd[1].setPosition(350.f, 300.f);

}
menu::~menu()
{

}
bool menu::checkmouse(sf::RectangleShape& shape, sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::FloatRect bounds = shape.getGlobalBounds();

	return bounds.contains(mousePos);
}
void menu::victory(sf::RenderWindow& window,int nb)
{

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}

			for (int i = 0; i < 2; i++)
			{
				if (event.type == sf::Event::MouseMoved && checkmouse(buttonsVictory[i], window))
				{
					buttonsVictory[i].setTexture(&buttonsTexturesVictory[i * 2 + 1]);
				}
				else if (event.type == sf::Event::MouseButtonPressed && checkmouse(buttonsVictory[0], window))
				{
					window.close();
					exit(0);
				}
				else if (event.type == sf::Event::MouseButtonPressed && checkmouse(buttonsVictory[1], window))
				{
					Game game(nb + 4);
					game.run(window, nb + 4);
				}
				else
				{
					buttonsVictory[i].setTexture(&buttonsTexturesVictory[i * 2]);
				}
			}
		}


		window.clear(sf::Color::White);
		window.draw(v);
		for (int i = 0; i < 2; i++)
			window.draw(buttonsVictory[i]);
		window.display();
	}

}
void menu::defeat(sf::RenderWindow& window, int nb)
{

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}

			for (int i = 0; i < 2; i++)
			{
				if (event.type == sf::Event::MouseMoved && checkmouse(buttonsDefeat[i], window))
				{
					buttonsDefeat[i].setTexture(&buttonsTexturesDefeat[i * 2 + 1]);
				}
				else if (event.type == sf::Event::MouseButtonPressed && checkmouse(buttonsDefeat[0], window))
				{
					window.close();
					exit(0);
				}
				else if (event.type == sf::Event::MouseButtonPressed && checkmouse(buttonsDefeat[1], window))
				{
					Game game(nb);
					game.run(window, nb);
				}
				else
				{
					buttonsDefeat[i].setTexture(&buttonsTexturesDefeat[i * 2]);
				}
			}
		}


		window.clear(sf::Color::White);
		window.draw(d);
		for (int i = 0; i < 2; i++)
			window.draw(buttonsDefeat[i]);
		window.display();
	}

}
void menu::defeatquiz(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}

			for (int i = 0; i < 2; i++)
			{
				if (event.type == sf::Event::MouseMoved && checkmouse(buttonsEnd[i], window))
				{
					buttonsEnd[i].setTexture(&buttonsTexturesEnd[i * 2 + 1]);
				}
				else if (event.type == sf::Event::MouseButtonPressed && checkmouse(buttonsEnd[0], window))
				{
					window.close();
					exit(0);
				}
				else if (event.type == sf::Event::MouseButtonPressed && checkmouse(buttonsEnd[1], window))
				{
					window.close();
					run();
				}
				else
				{
					buttonsEnd[i].setTexture(&buttonsTexturesEnd[i * 2]);
				}
			}
		}


		window.clear(sf::Color::White);
		window.draw(d);
		for (int i = 0; i < 2; i++)
			window.draw(buttonsEnd[i]);
		window.display();
	}
}
void menu::endgame(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}

			for (int i = 0; i < 2; i++)
			{
				if (event.type == sf::Event::MouseMoved && checkmouse(buttonsEnd[i], window))
				{
					buttonsEnd[i].setTexture(&buttonsTexturesEnd[i * 2 + 1]);
				}
				else if (event.type == sf::Event::MouseButtonPressed && checkmouse(buttonsEnd[0], window))
				{
					window.close();
					exit(0);
				}
				else if (event.type == sf::Event::MouseButtonPressed && checkmouse(buttonsEnd[1], window))
				{
					window.close();
					run();
				}
				else
				{
					buttonsEnd[i].setTexture(&buttonsTexturesEnd[i * 2]);
				}
			}
		}


		window.clear(sf::Color::White);
		window.draw(v);
		for (int i = 0; i < 2; i++)
			window.draw(buttonsEnd[i]);
		window.display();
	}
}

void menu::run()
{
	sf::RenderWindow window(sf::VideoMode(700, 680), "Menu");
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}

			for (int i = 0; i < 2; i++)
			{
				if (event.type == sf::Event::MouseMoved && checkmouse(buttons[i], window))
				{
					buttons[i].setTexture(&buttonsTextures[i * 2 + 1]);
				}
				else if (event.type == sf::Event::MouseButtonPressed && checkmouse(buttons[0], window))
				{
					window.close();
					exit(0);
				}
				else if (event.type == sf::Event::MouseButtonPressed && checkmouse(buttons[1], window))
				{
					Game game(24);
					game.run(window,24);
				}
				else
				{
					buttons[i].setTexture(&buttonsTextures[i * 2]);
				}
			}
		}


		window.clear(sf::Color::White);
		window.draw(menuback);
		for (int i = 0; i < 2; i++)
			window.draw(buttons[i]);
		
		window.display();
	}

}