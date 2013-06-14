#include "fade.h"

Fade::Fade(const char* imgPath)
{
	filter_image.LoadFromFile(imgPath);
	filter.SetImage(filter_image);
	alpha_num_out=0;
	alpha_num_in=255;
}

int Fade::fadeOut(sf::RenderWindow& App)
{
	alpha_num_out+=3;
	filter.SetColor(sf::Color(255,255,255,(int)alpha_num_out));
	App.Draw(filter);
	App.Display();
	return alpha_num_out;
}

int Fade::fadeIn(sf::RenderWindow& App)
{
	alpha_num_in-=3;
	filter.SetColor(sf::Color(255,255,255,alpha_num_in));
	App.Draw(filter);
	App.Display();
	return alpha_num_in;
}
