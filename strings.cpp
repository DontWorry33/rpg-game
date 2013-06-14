#include "strings.h"

sf::Font Strings::arial = arial.GetDefaultFont();

Strings::Strings(std::string name, sf::Color color)
{
	str.SetText(name);
	str.SetFont(Strings::arial);
	str.SetSize(14);
	str.SetColor(color);
}

Strings::Strings(std::string name, double xCord, double yCord, sf::Color color)
{
	cords.x=xCord;
	cords.y=yCord;
	str.SetText(name);
	str.SetFont(Strings::arial);
	str.SetSize(14);
	str.SetColor(color);
	str.SetPosition(cords);
}

Strings::Strings(const char* name, double startNum, sf::Color color)
{
	initNum=startNum;
	str.SetText(name+UpdateString(0,true));
	str.SetFont(Strings::arial);
	str.SetSize(14);
	str.SetColor(color);
}

Strings::Strings(const char* name, double startNum, double xCord, double yCord, sf::Color color)
{
	cords.x = xCord;
	cords.y = yCord;
	initNum=startNum;
	str.SetText(name+UpdateString(0,true));
	str.SetFont(Strings::arial);
	str.SetSize(14);
	str.SetPosition(cords);
	str.SetColor(color);
}

std::string Strings::UpdateString(int value, bool operation)
{
	this->ss.str("");
	if (operation) this->initNum+=value;
	else this->initNum-=value;
	this->ss << this->initNum;
	return ss.str();
}

std::string Strings::UpdateString(std::stringstream& ss, float updater)
{
	ss.str("");
	ss << updater;
	return ss.str();
}

std::string Strings::ClearString()
{
	ss.str("");
	return ss.str();
}

