#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;

struct Start_Items
{
	Start_Items(){};
	Start_Items(const char*, sf::Vector2f);
	Start_Items& operator=(const Start_Items& rhs);
	int initalizeItems(int chk, vector<Start_Items*>& vect, sf::Sprite* menu);
	vector<Start_Items*> SetHair(sf::RenderWindow& App, sf::Sprite* menu);
	vector<Start_Items*> start_game();
	sf::Image hair_img;
	sf::Sprite hair;	
	sf::Vector2f pos;
	string name;
};
