#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#ifndef STRINGS_H
#define STRINGS_H

struct Strings
{
	//Constructors
	Strings(){}
	Strings(std::string name, sf::Color color);
	Strings(std::string name, double xCord, double yCord, sf::Color color);
	Strings(const char* name, double startNum, sf::Color color);
	Strings(const char* name, double startNum, double xCord, double yCord, sf::Color color);
	
	//Functions
	std::string UpdateString(int value, bool operation);
	std::string UpdateString(std::stringstream& ss, float updater);
	std::string ClearString();
	
	//Static vars
	static sf::Font arial;
	
	//Vars
	double initNum;
	
	sf::String str;
	sf::Vector2f cords;
	
	std::stringstream ss;	
	
};

#endif
