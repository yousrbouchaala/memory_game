#include "Game.h"
#include "menu.h"
#include "quiz.h"
#include <iostream>
#include <Windows.h>

Game::Game(int nb)
{
	settcards(nb);
	settbuttons();

	mix(nb); 
	turns = -1;
	
	//-----------------------//
	timerFont.loadFromFile("ShipporiMincho-Regular.ttf");
	timerText.setFont(timerFont);
	limitText.setFont(timerFont);
	limitText.setString("00");
	timerText.setString("TIME : 00:000");
	timerText.setCharacterSize(20);
	limitText.setCharacterSize(30);
	limitText.setFillColor(sf::Color::Black);
	timerText.setFillColor(sf::Color::Black);

	
	//-----------------------//
	timerTextRect = timerText.getLocalBounds();
	limitTextRect = limitText.getLocalBounds();
	timerText.setOrigin(timerTextRect.left + timerTextRect.width / 2.0f, timerTextRect.top + timerTextRect.height / 2.0f);
	limitText.setOrigin(timerTextRect.left + timerTextRect.width / 2.0f, timerTextRect.top + timerTextRect.height / 2.0f);
	timerText.setPosition(600.f, 585.f);
	limitText.setPosition(650.f, 585.f);

	//-----------------------//
	duration = 100.0f;
	limit = 50;
	
}
Game::~Game()
{

}
bool Game::checkmouse(sf::RectangleShape& shape, sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::FloatRect bounds = shape.getGlobalBounds();

	return bounds.contains(mousePos);
}
void Game::restart( int nb)
{
	mix(nb);
	for (int i = 0; i < nb; i++)
	{
		cardsCorrect[i] = -1;
		cards[i].setTexture(&cardsTextures[nb / 2]);
	}


	cardsSelected[0] = -1;
	cardsSelected[1] = -1;
	duration = 100.0f;
	limit = 50;

}
void Game::mix(int nb)
{
	srand(time(NULL));

	int x = nb / 2;

	int randomNumber;

	for (int i = 0; i < nb; )
	{
		bool alreadyThere = false;
		randomNumber = rand() % x;

		for (int j = 0; j < i; j++)
		{
			if (randomNumber == cardsTexturesBounds[j])
			{
				for (int h = j + 1; h < i; h++)
				{
					if (randomNumber == cardsTexturesBounds[h])
					{
						alreadyThere = true;
						break;
					}
				}
			}
		}

		if (!alreadyThere)
		{
			cardsTexturesBounds[i] = randomNumber;
			i++;
		}
	}
}
bool Game::same(int nb)
{

	if (cards[cardsSelected[0]].getTexture() == cards[cardsSelected[1]].getTexture())
	{
		for (int i = 0; i < nb; i++)
		{
			if (cardsCorrect[i] == -1)
			{
				cardsCorrect[i] = cardsSelected[0];
				cardsCorrect[i + 1] = cardsSelected[1];
				break;
			}
		}


		return true;
	}
	else
	{


		return false;
	}
}

bool Game::turned(int n,int nb)
{
	for (int i = 0; i < nb; i++)
	{
		if (cardsCorrect[i] == n)
		{
			return true;
		}
	}

	return false;
}

bool Game::over(int nb)
{
	for (int i = 0; i < nb; i++)
	{
		if (cardsCorrect[i] == -1)
		{
			return false;
		}
	}

	return true;
}
void Game::starttime()
{
	
	sf::Time time = clock.restart();

	
	if (duration > 0) {
		
		duration -= time.asSeconds();
		fMilliseconds = std::modf(duration, &fSeconds);
		intSeconds = static_cast<int>(fSeconds);
		intMilliseconds = static_cast<int>(fMilliseconds * 1000);
		stringMilliseconds = std::to_string(intMilliseconds);
		stringSeconds = std::to_string(intSeconds);

		if (intMilliseconds <= 0) {
			stringMilliseconds = "00";
		}

		if (intSeconds <= 0) {
			stringSeconds = "00";
		}
		else if (intSeconds < 10) {
			stringSeconds = "0" + stringSeconds;
		}

		timerString = "TIME : " + stringSeconds + ":" + stringMilliseconds;
		timerText.setString(timerString);

	}
}
void Game::run(sf::RenderWindow& window,int nb)
{

	restart(nb);
	while (window.isOpen())
	{
		sf::Event event;

		if (nb == 20)
		{
			starttime();
		}
		else if (nb == 16)
		{
			limitString = std::to_string(limit);

			limitText.setString(limitString);
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}


			if (nb == 20)
			{


				for (int i = 0; i < nb && duration>0; i++)
				{
					if (event.type == sf::Event::MouseButtonPressed && checkmouse(cards[i], window) && !(turned(i, nb)))
					{
						turns++;

						cardsSelected[turns] = i;

						if (turns >= 1 && cardsSelected[0] == cardsSelected[1])
						{
							turns = 0;
							continue;
						}
						else if (turns >= 1)
						{
							cards[i].setTexture(&cardsTextures[cardsTexturesBounds[i]]);

							{ 
								for (int i = 0; i < nb; i++)
									window.draw(cards[i]);
								window.display();
								event.type = sf::Event::MouseEntered;
								std::this_thread::sleep_for(std::chrono::milliseconds(500));

							}

							turns = -1;

							if (!same(nb))
							{
								for (int i = 0; i < 2; i++)
								{
									cards[cardsSelected[i]].setTexture(&cardsTextures[nb / 2]);
								}
							}
							else
							{
								if (over(nb))
								{


									menu menuu;
									menuu.victory(window, nb);


								}
							}

							continue;
						}

						

						cards[i].setTexture(&cardsTextures[cardsTexturesBounds[i]]);
					}

					else
					{
						bool allowChange = true;

						if (cardsSelected[0] == i || cardsSelected[1] == i)
							allowChange = false;

						for (int j = 0; j < nb; j++)
							if (cardsCorrect[j] == i)
								allowChange = false;

						if (allowChange)
							cards[i].setTexture(&cardsTextures[nb / 2]);
					}
				}
				if (!(over(nb))&& duration <= 0)
				{
					menu menuu;
					menuu.defeat(window,nb);
				}
			}
			else if (nb == 16)
			{
				for (int i = 0; i < nb && limit>0; i++)
				{
					if (event.type == sf::Event::MouseButtonPressed && checkmouse(cards[i], window) && !(turned(i, nb)))
					{
						turns++;
						

						cardsSelected[turns] = i;

						if (turns >= 1 && cardsSelected[0] == cardsSelected[1])
						{
							turns = 0;
							
							continue;
						}
						else if (turns >= 1)
						{
							limit--;
							cards[i].setTexture(&cardsTextures[cardsTexturesBounds[i]]);

							{
								for (int i = 0; i < nb; i++)
									window.draw(cards[i]);
								window.display();
								event.type = sf::Event::MouseEntered;
								std::this_thread::sleep_for(std::chrono::milliseconds(500));

							}

							turns = -1;

							if (!same(nb))
							{
								for (int i = 0; i < 2; i++)
								{
									cards[cardsSelected[i]].setTexture(&cardsTextures[nb / 2]);
								}
							}
							else
							{
								if (over(nb))
								{
									menu menu;

									menu.victory(window, nb);
								}
							}

							continue;
						}


						cards[i].setTexture(&cardsTextures[cardsTexturesBounds[i]]);
					}

					else
					{
						bool allowChange = true;

						if (cardsSelected[0] == i || cardsSelected[1] == i)
							allowChange = false;

						for (int j = 0; j < nb; j++)
							if (cardsCorrect[j] == i)
								allowChange = false;

						if (allowChange)
							cards[i].setTexture(&cardsTextures[nb / 2]);
					}
				}
				if (!(over(nb)) && limit <= 0)
				{
					menu menuu;
					menuu.defeat(window, nb);
				}
			}
			
			else
			{

			for (int i = 0; i < nb; i++)
			{
				if (event.type == sf::Event::MouseButtonPressed && checkmouse(cards[i], window) && !(turned(i, nb)))
				{
					turns++;

					cardsSelected[turns] = i;

					if (turns >= 1 && cardsSelected[0] == cardsSelected[1])
					{
						turns = 0;
						continue;
					}
					else if (turns >= 1)
					{
						cards[i].setTexture(&cardsTextures[cardsTexturesBounds[i]]);

						{
							for (int i = 0; i < nb; i++)
								window.draw(cards[i]);
							window.display();
							event.type = sf::Event::MouseEntered;
							std::this_thread::sleep_for(std::chrono::milliseconds(500));

						}

						turns = -1;

						if (!same(nb))
						{
							for (int i = 0; i < 2; i++)
							{
								cards[cardsSelected[i]].setTexture(&cardsTextures[nb / 2]);
							}
						}
						else
						{
							if (over(nb))
							{
								if (nb == 24)
								{
									srand(time(NULL));
									int flag;
									flag = rand() % 11;
									quiz q(flags[flag]);
									q.run(window);
								}
								else
								{
									menu menu;

									menu.victory(window, nb);
								}
								

							}
						}

						continue;
					}


					cards[i].setTexture(&cardsTextures[cardsTexturesBounds[i]]);
				}

				else
				{
					bool allowChange = true;

					if (cardsSelected[0] == i || cardsSelected[1] == i)
						allowChange = false;

					for (int j = 0; j < nb; j++)
						if (cardsCorrect[j] == i)
							allowChange = false;

					if (allowChange)
						cards[i].setTexture(&cardsTextures[nb / 2]);
				}
			}
			}
			for (int i = 0; i < 2; i++)
			{
				if (event.type == sf::Event::MouseMoved && checkmouse(buttons, window))
				{
					buttons.setTexture(&buttonsTextures[1]);
				}
				else if (event.type == sf::Event::MouseButtonPressed && checkmouse(buttons, window))
				{
					window.close();
					exit(0);
				}
				else
				{
					buttons.setTexture(&buttonsTextures[0]);
				}
			}
		}


		window.clear(sf::Color::White);
		window.draw(gameback);
		window.draw(buttons);
		for (int i = 0; i < nb; i++)
			window.draw(cards[i]);
		
		if (nb == 20)
		{
	
			window.draw(timerText);
		}
		else if (nb == 16)
		{

			window.draw(limitText);
		}
		
		window.display();

	}
}
void Game::settbuttons()
{
buttonsTextures[0].loadFromFile("exit1.png"); 
buttonsTextures[1].loadFromFile("exit2.png");


buttons.setTexture(&buttonsTextures[0]);


buttons.setSize(sf::Vector2f(60.f, 60.f));
gametexture.loadFromFile("gameback.png");
gameback.setTexture(gametexture);
gameback.setScale(700 / gameback.getLocalBounds().width, 700 / gameback.getLocalBounds().height);

buttons.setOrigin(buttons.getLocalBounds().width / 2, buttons.getLocalBounds().height / 2);

buttons.setPosition(350.f, 585.f);



}
void Game::settcards(int nb)
{
	switch (nb)
	{
	case 8:
		for (int i = 0; i <= 4; i++)
		{
			cardsTextures[i].loadFromFile(ch[i]);
		}
		for (int i = 0; i < 8; i++)
		{
			cards[i].setTexture(&cardsTextures[4]);
			cards[i].setSize(sf::Vector2f(120.f,120.f));
			
		}

		cards[0].setPosition(180.f, 15.f);
		cards[1].setPosition(360.f, 15.f);

		cards[2].setPosition(180.f, 145.f);
		cards[3].setPosition(360.f, 145.f);

		cards[4].setPosition(180.f, 275.f);
		cards[5].setPosition(360.f, 275.f);

		cards[6].setPosition(180.f, 405.f);
		cards[7].setPosition(360.f, 405.f);

		for (int i = 0; i < 8; i++)
		{
			cardsCorrect[i] = -1;
		}
		break;
	case 12:
		for (int i = 0; i <= 6; i++)
		{
			cardsTextures[i].loadFromFile(ch[i]);
		}
		for (int i = 0; i < 12; i++)
		{
			cards[i].setTexture(&cardsTextures[6]);
			cards[i].setSize(sf::Vector2f(115.f, 115.f));
			
		}

		cards[0].setPosition(50.f, 15.f);
		cards[1].setPosition(292.f, 15.f);
		cards[2].setPosition(540.f, 15.f);

		cards[3].setPosition(50.f, 145.f);
		cards[4].setPosition(292.f, 145.f);
		cards[5].setPosition(540.f, 145.f);

		cards[6].setPosition(50.f, 275.f);
		cards[7].setPosition(292.f, 275.f);
		cards[8].setPosition(540.f, 275.f);

		cards[9].setPosition(50.f, 405.f);
		cards[10].setPosition(292.f, 405.f);
		cards[11].setPosition(540.f, 405.f);
		for (int i = 0; i < 12; i++)
		{
			cardsCorrect[i] = -1;
		}

		break;
	case 16:
		for (int i = 0; i <= 8; i++)
		{
			cardsTextures[i].loadFromFile(ch[i]);
		}
		for (int i = 0; i < 16; i++)
		{
			cards[i].setTexture(&cardsTextures[8]);
			cards[i].setSize(sf::Vector2f(115.f, 115.f));
		}

		cards[0].setPosition(45.f, 15.f);
		cards[1].setPosition(210.f, 15.f);
		cards[2].setPosition(370.f, 15.f);
		cards[3].setPosition(530.f, 15.f);

		cards[4].setPosition(45.f, 145.f);
		cards[5].setPosition(210.f, 145.f);
		cards[6].setPosition(370.f, 145.f);
		cards[7].setPosition(530.f, 145.f);

		cards[8].setPosition(45.f, 275.f);
		cards[9].setPosition(210.f, 275.f);
		cards[10].setPosition(370.f, 275.f);
		cards[11].setPosition(530.f, 275.f);

		cards[12].setPosition(45.f, 405.f);
		cards[13].setPosition(210.f, 405.f);
		cards[14].setPosition(370.f, 405.f);
		cards[15].setPosition(530.f, 405.f);

		for (int i = 0; i < 16; i++)
		{
			cardsCorrect[i] = -1;
		}
		break;
	case 20:
		for (int i = 0; i <= 10; i++)
		{
			cardsTextures[i].loadFromFile(ch[i]);
		}
		for (int i = 0; i < 20; i++)
		{
			cards[i].setTexture(&cardsTextures[10]);
			cards[i].setSize(sf::Vector2f(115.f, 115.f));
	
		}
		cards[0].setPosition(25.f, 15.f);
		cards[1].setPosition(160.f, 15.f);
		cards[2].setPosition(295.f, 15.f);
		cards[3].setPosition(430.f, 15.f);
		cards[4].setPosition(565.f, 15.f);

		cards[5].setPosition(25.f, 145.f);
		cards[6].setPosition(160.f, 145.f);
		cards[7].setPosition(295.f, 145.f);
		cards[8].setPosition(430.f, 145.f);
		cards[9].setPosition(565.f, 145.f);

		cards[10].setPosition(25.f, 275.f);
		cards[11].setPosition(160.f, 275.f);
		cards[12].setPosition(295.f, 275.f);
		cards[13].setPosition(430.f, 275.f);
		cards[14].setPosition(565.f, 275.f);

		cards[15].setPosition(25.f, 405.f);
		cards[16].setPosition(160.f, 405.f);
		cards[17].setPosition(296.f, 405.f);
		cards[18].setPosition(430.f, 405.f);
		cards[19].setPosition(565.f, 405.f);
		for (int i = 0; i < 20; i++)
		{
			cardsCorrect[i] = -1;
		}
		break;
	case 24:
		for (int i = 0; i <= 12; i++)
		{
			cardsTextures[i].loadFromFile(flags[i]);
		}
		for (int i = 0; i < 24; i++)
		{
			cards[i].setTexture(&cardsTextures[12]);
			cards[i].setSize(sf::Vector2f(90.f, 90.f));
		}
		cards[0].setPosition(45.f, 15.f);
		cards[1].setPosition(145.f, 15.f);
		cards[2].setPosition(245.f, 15.f);
		cards[3].setPosition(345.f, 15.f);
		cards[4].setPosition(445.f, 15.f);
		cards[5].setPosition(545.f, 15.f);

		cards[6].setPosition(45.f, 145.f);
		cards[7].setPosition(145.f, 145.f);
		cards[8].setPosition(245.f, 145.f);
		cards[9].setPosition(345.f, 145.f);
		cards[10].setPosition(445.f, 145.f);
		cards[11].setPosition(545.f, 145.f);

		cards[12].setPosition(45.f, 275.f);
		cards[13].setPosition(145.f, 275.f);
		cards[14].setPosition(245.f, 275.f);
		cards[15].setPosition(345.f, 275.f);
		cards[16].setPosition(445.f, 275.f);
		cards[17].setPosition(545.f, 275.f);

		cards[18].setPosition(45.f, 405.f);
		cards[19].setPosition(145.f, 405.f);
		cards[20].setPosition(245.f, 405.f);
		cards[21].setPosition(345.f, 405.f);
		cards[22].setPosition(445.f, 405.f);
		cards[23].setPosition(545.f, 405.f);

		for (int i = 0; i < 24; i++)
		{
			cardsCorrect[i] = -1;
		}
		break;
	}

}