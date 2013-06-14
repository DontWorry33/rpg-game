#include <iostream>
#include <vector>
#include "animation.cpp"
#include "tiles.cpp"
#include "strings.cpp"
#include "characterstats.cpp"
#include "character.cpp"
#include "fade.cpp"
#include "items.cpp"
#include "events.cpp"
#include "start_game.cpp"

sf::PostFX fx()
{
	sf::PostFX Effect;
	if (!Effect.LoadFromFile("effects/colorize.sfx")) NULL;
	Effect.SetTexture("framebuffer",NULL);
	Effect.SetParameter("color",1.f, 1.f, 1.f);
	return Effect;
}

std::vector<sf::Image> HPBAR()
{
	std::string files[] = {"hpbar/hp100.png","hpbar/hp80.png","hpbar/hp60.png","hpbar/hp40.png","hpbar/hp20.png","hpbar/hp0.png"};
	std::vector<sf::Image> images;
	for (int p=0; p<sizeof(files)/sizeof(files[0]); p++) images.push_back(sf::Image());
	for (unsigned int x=0; x<images.size(); x++) images[x].LoadFromFile(files[x]);
	return images;
}

void checkHP(int& health_count, sf::Sprite& healthbar, std::vector<sf::Image>& hp)
{
		if (health_count <=80 && health_count >60) healthbar.SetImage(hp[1]);
		if (health_count <=60 && health_count >40) healthbar.SetImage(hp[2]);
		if (health_count <=40 && health_count >20) healthbar.SetImage(hp[3]);
		if (health_count <=20 && health_count >0) healthbar.SetImage(hp[4]);
		if (health_count <=0) healthbar.SetImage(hp[5]);	
	
}

void drawTiles(Tiles& main, sf::RenderWindow& App, Character& player)
{
	//gravel tiles
	for (auto it = main.gravel_tiles.begin(); it!=main.gravel_tiles.end(); it++)
	{
		if ((it->first*32 <= (int)player.player.ani_spr.GetPosition().x+400 && it->first*32 >= (int)player.player.ani_spr.GetPosition().x-448) &&
		(it->second*32 <= (int)player.player.ani_spr.GetPosition().y+300 && it->second*32 >= (int)player.player.ani_spr.GetPosition().y-352))
			main.addTile(App, it->first, it->second, 0);
	}
	//grass tiles
	for (auto it = main.grass_tiles.begin(); it!= main.grass_tiles.end(); it++)
	{
		if ((it->first*32 <= (int)player.player.ani_spr.GetPosition().x+400 && it->first*32 >= (int)player.player.ani_spr.GetPosition().x-448) &&
		(it->second*32 <= (int)player.player.ani_spr.GetPosition().y+300 && it->second*32 >= (int)player.player.ani_spr.GetPosition().y-352))
		main.addTile(App, it->first, it->second, 1);
	}
	//tree tiles
	for (auto it = main.tree_tiles.begin(); it!= main.tree_tiles.end(); it++)
	{
		if ((it->first*32 <= (int)player.player.ani_spr.GetPosition().x+400 && it->first*32 >= (int)player.player.ani_spr.GetPosition().x-448) &&
		(it->second*32 <= (int)player.player.ani_spr.GetPosition().y+300 && it->second*32 >= (int)player.player.ani_spr.GetPosition().y-352))
		main.addTile(App, it->first, it->second, 2);
		
	}
	//sand tiles
	for (auto it = main.sand_tiles.begin(); it!= main.sand_tiles.end(); it++)
	{
		if ((it->first*32 <= (int)player.player.ani_spr.GetPosition().x+400 && it->first*32 >= (int)player.player.ani_spr.GetPosition().x-448) &&
		(it->second*32 <= (int)player.player.ani_spr.GetPosition().y+300 && it->second*32 >= (int)player.player.ani_spr.GetPosition().y-352))
		main.addTile(App, it->first, it->second, 3);
		
	}
	
}

int welcomeScreen()
{
	sf::RenderWindow App(sf::VideoMode(800,600), "Welcome");
	std::string image_names[] = {"startscreen/playgamee.png","startscreen/playgamee_c.png","startscreen/exit_game.png","startscreen/exitgame_c.png"};
	std::vector<sf::Image> buttons;
	for (int x=0; x<sizeof(image_names)/sizeof(image_names[0]); x++) buttons.push_back(sf::Image());
	for (int y=0; y<buttons.size(); y++) buttons[y].LoadFromFile(image_names[y]);
	int wid=200;
	int hei=50;
	sf::Sprite pg(buttons[0]); //button 0 for non-clicked, 1 for clicked (playgame)
	sf::Sprite eg(buttons[2]); //button 2 for non-clicked, 3 for clicked (exitgame)
	pg.SetPosition(550,200);
	eg.SetPosition(550,300);	
	
	while (App.IsOpened())
	{
		App.Clear();
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed || App.GetInput().IsKeyDown(sf::Key::Escape))
				return 1;
			
			//Detect mouse on playgame button	
			if ((Event.MouseMove.X >= pg.GetPosition().x && Event.MouseMove.X <= pg.GetPosition().x+wid) && (Event.MouseMove.Y >=
			pg.GetPosition().y && Event.MouseMove.Y <= pg.GetPosition().y+hei)) pg.SetImage(buttons[1]);
			else pg.SetImage(buttons[0]);
			//Detect click on playgame button
			if ((Event.MouseButton.Button == 0) && (Event.MouseButton.X >= pg.GetPosition().x && Event.MouseButton.X <= pg.GetPosition().x+wid) && 
			(Event.MouseButton.Y >= pg.GetPosition().y && Event.MouseButton.Y <= pg.GetPosition().y+hei)) return 0;	
	
			//Detect mouse on exit game button
			if ((Event.MouseMove.X >= eg.GetPosition().x && Event.MouseMove.X <= eg.GetPosition().x+wid) && (Event.MouseMove.Y >=
			eg.GetPosition().y && Event.MouseMove.Y <= eg.GetPosition().y+hei)) eg.SetImage(buttons[3]);
			else eg.SetImage(buttons[2]);
			//Detect click on exitgame button
			if ((Event.MouseButton.Button == 0) && (Event.MouseButton.X >= eg.GetPosition().x && Event.MouseButton.X <= eg.GetPosition().x+wid) && 
			(Event.MouseButton.Y >= eg.GetPosition().y && Event.MouseButton.Y <= eg.GetPosition().y+hei)) return 1;
		
		}
		
		App.Draw(pg);
		App.Draw(eg);
		App.Display();
	}
	return 0;
	
}

int main()
{
	sf::RenderWindow App(sf::VideoMode(800,600),"RPG Game by Hussain");
	App.Show(false);
	
	if (welcomeScreen() == 0) NULL;
	else
	{
		std::cout << "Welcome Screen Closed" << std::endl;
		return 0;
	}

	Items _item;
	_item.setItems(App);
	
	CharacterStats stats;
	Animation character("sprites/fig2t.png");
	Character player(character,stats);
	
	Start_Items choose_items;
	vector<Start_Items*> begin = choose_items.start_game();
	
	
	for (int x=0; x<begin.size(); x++)
	{
		_item.equip_item(&begin[x]->hair);
		player.player.swapImage(_item.equipped);
		
	}
	App.Show(true);
	
	//Default window and set frame limit
	
	//sf::RenderWindow App(sf::VideoMode(800,600),"RPG Game by Hussain");
	App.SetFramerateLimit(25);
	
	//Temporary welcome variable
	bool welcome=true;

	//Create clock object
	sf::Clock clock;
	
	//Create fade object for fade in's and outs, (800x600)
	Fade fade_obj("sprites/black_filter.png");
	
	//Create strings
	Strings health("Health: ",100, sf::Color(sf::Color::White));
	Strings fps("FPS: ",20,sf::Color(sf::Color::Blue));
	
	//Load default stats
	//CharacterStats stats;
	
	//Load hpbar
	std::vector<sf::Image> hp = HPBAR();
	sf::Sprite healthbar;
	healthbar.SetImage(hp[0]);
	
	//Create view
	sf::View locked;
	
	//Set View Properties
	locked.SetHalfSize(400,300);
	locked.SetCenter(0,0);
	
	//Set the window view to the locked view
	App.SetView(locked);

	//Create the main tile
	Tiles main;
	main.loadMap("mapgen/map1.txt",App);

	//Load effects for screen
	if (sf::PostFX::CanUsePostFX() == false) return 0;
	sf::PostFX effx = fx();
	
	//Event handler
	Events event;

	
	while (App.IsOpened())
	{
		App.Clear();
		sf::Event Event;
		while (App.GetEvent(Event))
		{
		 if (Event.Type == sf::Event::Closed)
			 App.Close();
			 
		}
		//Draw tiles on screen
		drawTiles(main, App, player);
		
		//Fade in beginning
		if (welcome)
		{
			if (clock.GetElapsedTime() > 0.001)
			{
				if (fade_obj.fadeIn(App) <= 5) welcome=false;
				clock.Reset();
				continue;
			}
		}
		//Events
		event.findItem(_item, player);
		//event.hoverItem(_item, player, Event);
		
		//Draw Items	
		_item.displayItems(App,Event,player.player.ani_spr);
		
		//Animation when moved
		player.player.Update(App, main, locked, stats.health, health);

		//Modify health bar
		checkHP(stats.health,healthbar,hp);
		
		//Set health bar moving with camera
		healthbar.SetPosition(locked.GetCenter().x-400,locked.GetCenter().y-300);
		fps.str.SetText("FPS: "+fps.UpdateString(fps.ss,1/App.GetFrameTime()));
		fps.str.SetPosition(locked.GetCenter().x+300,locked.GetCenter().y-300);
		
		App.Draw(healthbar);
		App.Draw(health.str);
		App.Draw(fps.str);
		App.Display();
		
		
	}
		return EXIT_SUCCESS;
	 
	return 0;
}
