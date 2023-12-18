#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <chrono>
#include <thread>
#include<string>
class quiz
{
public:
	quiz(std::string flag);

	~quiz();

	
	
	

	
	void run(sf::RenderWindow& window2);



private:
	std::string input_text;
	sf::Font font;
	sf::Clock clock;
	sf::Sprite v;
	sf::Texture victorytexture;
	std::string chaine;
	


};

