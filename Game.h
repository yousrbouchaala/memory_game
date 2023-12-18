#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <chrono>
#include <thread>
#include<string>
class Game
{
public:
	Game(int nb);
	

	~Game();

	bool checkmouse(sf::RectangleShape& shape, sf::RenderWindow& window);

	void restart(int nb);

	void mix(int nb);

	bool same(int nb);

	bool turned(int n, int nb);

	bool over(int nb);

	void run(sf::RenderWindow& window, int nb);
	void settbuttons();
	void settcards(int nb);
	void starttime();
	int limit;


private:
	sf::RectangleShape buttons;
	sf::Texture buttonsTextures[2];
	sf::Sprite gameback;
	sf::Texture gametexture;


	sf::RectangleShape cards[24];
	sf::Texture cardsTextures[13];


	unsigned short cardsTexturesBounds[24];
	short cardsSelected[2];
	short cardsCorrect[24];
	int turns;

	
	sf::Font timerFont;
	sf::Text timerText, limitText;
	sf::FloatRect timerTextRect, limitTextRect;
	sf::Clock clock;
	float duration;
	float fMilliseconds, fSeconds;
	int intMilliseconds, intSeconds;
	sf::String stringMilliseconds;
	sf::String stringSeconds;
	sf::String timerString, limitString;
	std::string ch[13] = { "photo.png","tree.png","sun.png" ,"moon.png" ,"fish.png","cream.png","flower.png","catspace.png","dog.png","blackhole.png","comet.png","p.png","m.png" };
	std::string flags[13] = { "tunisia.png" ,"poland.png","india.png" ,"spain.png","brazil.png","united-kingdom.png" ,"south-korea.png","japan.png","germany.png","netherlands.png","australia.png","italy.png","countries.png" };

};