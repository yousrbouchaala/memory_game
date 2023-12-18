#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class menu
{
public:
	menu();

	~menu();
	void run();
	void victory(sf::RenderWindow& window, int nb);
	void defeat(sf::RenderWindow& window,int nb);
	void endgame(sf::RenderWindow& window);
	void defeatquiz(sf::RenderWindow& window);

	bool checkmouse(sf::RectangleShape& shape, sf::RenderWindow& window);
	
private:
	sf::Sprite v;
	sf::Sprite d;
	sf::Sprite menuback;

	sf::Texture menutexture;
	sf::Texture victorytexture;
	sf::Texture defeattexture;

	sf::RectangleShape buttons[2];
	sf::RectangleShape buttonsVictory[2];
	sf::RectangleShape buttonsDefeat[2];
	sf::RectangleShape buttonsEnd[2];
	sf::Texture buttonsTextures[4];
	sf::Texture buttonsTexturesVictory[4];
	sf::Texture buttonsTexturesDefeat[4];
	sf::Texture buttonsTexturesEnd[4];

};
