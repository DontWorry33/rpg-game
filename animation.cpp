#include "animation.h"

Animation::Animation(const char* path)
{
	//ani_spr.SetPosition(300,0);
	ani_img.LoadFromFile(path);
	ani_img.SetSmooth(false);
	ani_spr.SetImage(ani_img);
	ani_img_full_width = ani_img.GetWidth();
	ani_img_full_height = ani_img.GetHeight();
	ani_img_width = ani_img_full_width/4;
	ani_img_height = ani_img_full_height/4;
	ani_xpos = 0;
	ani_ypos = 0;
	int count=0;
	speed=5;
	xpos=250;
	ypos=64;
	velx=1;
	vely=1;
	st=0;
	for (int tmp=0; tmp<4; tmp++) 
	{
		ani_movements[tmp]=count;
		count+=ani_img_height;
		std::cout << "AniMov[" << tmp << "]=" << ani_movements[tmp] << std::endl;
	}
}

void Animation::swapImage(std::vector<sf::Sprite*> bases)
{
	to_draw.clear();
	for (unsigned int x=0; x<bases.size(); x++) 
	{
		to_draw.push_back(sf::Sprite());
		to_draw[x].SetImage(*(bases[x]->GetImage()));
	}
	
	//ani_spr.SetImage(*(immg.GetImage()));	
	
}

void Animation::Update(sf::RenderWindow& App, Tiles& tile, sf::View& view, int& hp, Strings& health)
//Down-0, Left-1, Right-2, Up-3
{
	speed=5;
		
	for (auto it=tile.gravel_tiles.begin(); it!=tile.gravel_tiles.end(); it++)
	{
		//Checks if standing on gravel tile
		if ( (int)(ani_spr.GetPosition().x+(ani_img_width/2)) /32 == it->first && (int) (ani_spr.GetPosition().y+(ani_img_height))/32 == it->second) 
		{
			speed=7.5;
			
			if (clock.GetElapsedTime() > 0.5) 
			{
				health.str.SetText("Health: "+health.UpdateString(1,false));
				hp-=1;
				clock.Reset();
			}			
		}
	}
	
	for (auto it=tile.tree_tiles.begin(); it!=tile.tree_tiles.end(); it++)
	{
		if (((int)(ani_spr.GetPosition().x)/32 == it->first && ((int)(ani_spr.GetPosition().y/32) == it->second))
		|| (((int)(ani_spr.GetPosition().x+(ani_img_width/2))/32 == it->first && ((int)(ani_spr.GetPosition().y+(ani_img_height))/32 == it->second))))
		{
			xpos-=velx;
			ypos-=vely;
		}
	}
	
	if (App.GetInput().IsKeyDown(sf::Key::Up))
	{
		ani_ypos = ani_movements[3];
		vely=-speed;
	}
	
	else if (App.GetInput().IsKeyDown(sf::Key::Down))
	{
		ani_ypos=ani_movements[0];
		vely=speed;
	}
	
	else vely=0;
	
	if (App.GetInput().IsKeyDown(sf::Key::Right))
	{
		ani_ypos = ani_movements[2];
		velx=speed;
	}
	
	else if (App.GetInput().IsKeyDown(sf::Key::Left))
	{
		ani_ypos = ani_movements[1];
		velx=-speed;
	}
	
	else velx=0;
	
	xpos+=velx;
	ypos+=vely;
	
	if (App.GetInput().IsKeyDown(sf::Key::V))
	{
		App.SetView(App.GetDefaultView());
	}

	if (velx!=0 || vely!=0) ani_xpos += ani_img_width;
	else ani_xpos=0;
	
	if (ani_xpos == ani_img_full_width) ani_xpos=0;
	
		//if ((int)ani_spr.GetPosition().x+(ani_img_width) > (int)App.GetWidth()) xpos=(int)App.GetWidth()-(ani_img_width); //Right wall collision
		//if (ani_spr.GetPosition().y < 0) ypos=0; //Top wall collision
		//if (ani_spr.GetPosition().y+(ani_img_height) >= (int)App.GetHeight()) ypos=(int)App.GetHeight()-(ani_img_width*2); //Bottom wall collision
	
	//Sets animation to move with ani_spr
	ani_spr.SetSubRect(sf::IntRect(ani_xpos, ani_ypos, ani_xpos+(ani_img_width), ani_ypos+(ani_img_height)));
	//Sets animation for all other base images
	for (unsigned int x=0; x<to_draw.size(); x++) 
		to_draw[x].SetSubRect(sf::IntRect(ani_xpos, ani_ypos, ani_xpos+(ani_img_width), ani_ypos+(ani_img_height)));
	ani_spr.SetPosition(xpos,ypos);
	view.SetCenter(ani_spr.GetPosition().x, ani_spr.GetPosition().y);
	health.str.SetPosition(view.GetCenter().x-400, view.GetCenter().y-300);
	App.SetView(view);
	
	//Draws base animation character
	App.Draw(ani_spr);
	//Draws all base images on top of animation sprite
	for (unsigned int x=0; x<to_draw.size(); x++) 
	{
		to_draw[x].SetPosition(xpos,ypos);
		App.Draw(to_draw[x]);
	}
}

