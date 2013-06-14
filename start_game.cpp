#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "start_game.h"
using namespace std;


Start_Items::Start_Items(const char* path, sf::Vector2f pos)
{
	hair_img.LoadFromFile(path);
	hair.SetImage(hair_img);
	this->pos=pos;
}

Start_Items& Start_Items::operator=(const Start_Items& rhs)
{
	if (this==&rhs) return *this;
	hair_img=rhs.hair_img;
	hair=rhs.hair;
	pos=rhs.pos;
	name=rhs.name;
	
	return *this;
	
}

int Start_Items::initalizeItems(int chk, vector<Start_Items*>& vect, sf::Sprite* menu)
{
	vect.clear();
	if (chk==0)
	{
		//char* mem=malloc(sizeof(Start_Items));
		//Start_Items* black=new (mem+sizeof(Start_Items)*0) Start_Items("Start_Items/hair/black.png",sf::Vector2f(400,200)); vect.push_back(black); black->name="black hair";
		Start_Items* black = new Start_Items("items/hair/black.png",sf::Vector2f(400,200)); vect.push_back(black); black->name="black hair";
		Start_Items* blue = new Start_Items("items/hair/blue.png",sf::Vector2f(450,200)); vect.push_back(blue); blue->name = "blue hair";
		Start_Items* brown = new Start_Items("items/hair/brown.png",sf::Vector2f(500,200)); vect.push_back(brown); brown->name = "brown hair";
		Start_Items* green = new Start_Items("items/hair/green.png",sf::Vector2f(550,200)); vect.push_back(green); green->name = "green hair";
		Start_Items* red = new Start_Items("items/hair/red.png",sf::Vector2f(400,248)); vect.push_back(red); red->name = "red hair";
		Start_Items* gold = new Start_Items("items/hair/gold.png",sf::Vector2f(450,248)); vect.push_back(gold); gold->name = "gold hair";
		Start_Items* gray = new Start_Items("items/hair/gray.png",sf::Vector2f(500,248)); vect.push_back(gray); gray->name = "gray hair";
		Start_Items* wine = new Start_Items("items/hair/wine.png",sf::Vector2f(550,248)); vect.push_back(wine); wine->name = "wine hair";
		return 1;
	}
	if (chk==1)
	{
		sf::Image* newImg = new sf::Image;
		newImg->LoadFromFile("items/body/choose.png");
		menu->SetImage(*(newImg));
		Start_Items* blackb = new Start_Items("items/body/black_shirt.png",sf::Vector2f(400,200)); vect.push_back(blackb); blackb->name="black shirt";
		Start_Items* blueb = new Start_Items("items/body/blue_shirt.png",sf::Vector2f(450,200)); vect.push_back(blueb); blueb->name = "blue shirt";
		Start_Items* brownb = new Start_Items("items/body/brown_shirt.png",sf::Vector2f(500,200)); vect.push_back(brownb); brownb->name = "brown shirt";
		Start_Items* greenb = new Start_Items("items/body/green_shirt.png",sf::Vector2f(550,200)); vect.push_back(greenb); greenb->name = "green shirt";
		Start_Items* redb = new Start_Items("items/body/red_shirt.png",sf::Vector2f(400,248)); vect.push_back(redb); redb->name = "red shirt";
		Start_Items* goldb = new Start_Items("items/body/gold_shirt.png",sf::Vector2f(450,248)); vect.push_back(goldb); goldb->name = "gold shirt";
		Start_Items* grayb = new Start_Items("items/body/gray_shirt.png",sf::Vector2f(500,248)); vect.push_back(grayb); grayb->name = "gray shirt";
		Start_Items* purpleb = new Start_Items("items/body/purple_shirt.png",sf::Vector2f(550,248)); vect.push_back(purpleb); purpleb->name = "purple shirt";
		return 1;
	}
	if (chk==2) return 2;
	
	return 0;
}

vector<Start_Items*> Start_Items::SetHair(sf::RenderWindow& App, sf::Sprite* menu)
{
	vector<Start_Items*> parts;
	int ids=0;
	if (initalizeItems(ids,parts,menu) == 1) NULL;
	else EXIT_FAILURE;
	
	//cout << parts[0]->name << endl;
	
	sf::Image img_spr;
	img_spr.LoadFromFile("sprites/fig2t.png");
	sf::Sprite spr(img_spr);
	spr.SetPosition(200,210);
	spr.Scale(1.5,1.5);
	
	sf::Image i;
	i.LoadFromFile("items/hair/next_button.jpg");
	sf::Sprite next(i);
	next.SetPosition(691,491);
	
	vector<Start_Items*> eq2;
	vector<Start_Items*> all;
	sf::String hair_str;
	
	hair_str.SetPosition(100,500);
	
	while (App.IsOpened())
	{
		App.Clear();
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App.Close();
			if (Event.Type == sf::Event::MouseButtonPressed)
			{
				if (eq2.size() >=1 && !((Event.MouseButton.X >= 691 && Event.MouseButton.X <= 755) && 
				(Event.MouseButton.Y >= 491 && Event.MouseButton.Y <=555))) eq2.clear();
				for (int x=0; x<parts.size(); x++)
				{
					if ((Event.MouseButton.X >= parts[x]->hair.GetPosition().x && Event.MouseButton.X <= parts[x]->hair.GetPosition().x+26*(parts[x]->hair.GetScale().x)) && 
					(Event.MouseButton.Y >= parts[x]->hair.GetPosition().y  && Event.MouseButton.Y <= parts[x]->hair.GetPosition().y+40*(parts[x]->hair.GetScale().y)))
					eq2.push_back(parts[x]);
				}
				if ((Event.MouseButton.X >= 691 && Event.MouseButton.X <= 755) && (Event.MouseButton.Y >= 491 && Event.MouseButton.Y <=555)) 
				{
					ids+=1;
					all.push_back(eq2[0]);
					if (initalizeItems(ids,parts,menu) == 2) return all;
				}
				
				
			}
		}
		//cout << ids << endl;
		App.Draw(*(menu));
		
		spr.SetSubRect(sf::IntRect(0,0,32,48));
		App.Draw(spr);
		if (ids>0)
		{
			for (int x=0; x<all.size(); x++)
			{
				all[x]->hair.Scale(1,1);
				all[x]->hair.SetSubRect(sf::IntRect(0,0,32,48));
				all[x]->hair.SetPosition(spr.GetPosition().x, spr.GetPosition().y);
				App.Draw(all[x]->hair);
			}
		}
		for (int x=0; x<eq2.size(); x++) 
		{
			eq2[x]->hair.Scale(1,1);
			eq2[x]->hair.SetSubRect(sf::IntRect(0,0,32,48));
			eq2[x]->hair.SetPosition(spr.GetPosition().x, spr.GetPosition().y);
			hair_str.SetText("You have selected: "+eq2[x]->name);
			App.Draw(eq2[x]->hair);
			App.Draw(hair_str);
		}
		for (int x=0; x<parts.size(); x++)
		{
			int wid=400+(50*(x+1));
			int hei=200;
			if (wid>=601) 
			{
				hei=280;
				wid=400+(50*(x-3));
			}
			parts[x]->hair.SetSubRect(sf::IntRect(0,0,32,47));
			if (parts[x]->hair.GetScale().x != 1.5) parts[x]->hair.Scale(1.5,1.5);
			parts[x]->hair.SetPosition(wid,hei);
			App.Draw(parts[x]->hair);
		}
		App.Draw(next);
		App.Display();
	}
}

vector<Start_Items*> Start_Items::start_game()
{
	sf::RenderWindow App(sf::VideoMode(800, 600), "Creation");
	sf::Image Image;
	if (!Image.LoadFromFile("items/hair/choose.png"))
		NULL;
	sf::Sprite* menu = new sf::Sprite;
	menu->SetImage(Image);
	menu->SetPosition(100,50);
	vector<Start_Items*> tmp = SetHair(App,menu);
	return tmp;
}
