#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include <sstream>

using namespace std;
int W=200; int H=200;
//Struct is for easy management of tiles. Each tile has a sprite/image, start/curr pos, and clicked boolean
struct Tiles
{
	Tiles(const char*, const sf::Vector2f);
	
	sf::Vector2f start_pos;
	sf::Vector2f curr_pos;
	
	bool is_clicked;
	
	sf::Sprite tile;
	sf::Image image;
};

Tiles::Tiles(const char* path, const sf::Vector2f pos)
{
	image.LoadFromFile(path);
	image.SetSmooth(false);
	tile.SetImage(image);
	is_clicked=false;
	tile.SetPosition(pos);
	start_pos=pos;
}

//Function to allign tiles next to eachother (current W/H is 32x32)
void allign(Tiles& t)
{
	//Get current x/y positions and set to variables
	int xp=(int)t.tile.GetPosition().x;
	int yp=(int)t.tile.GetPosition().y;
	
	//Create two vectors
	vector<int> xvals;
	vector<int> yvals;
	//Push back numbers from 0-800 & 0-600 with step of 32 respectively (not ready for views yet)
	for (int x=0; x<W; x++){ xvals.push_back(x*32); }
	for (int y=0; y<H; y++){ yvals.push_back(y*32); }
	
	//X value modification
	for (unsigned int x=0; x<xvals.size()-1; x++)
	{
		//From vectors of nums stepped by 32, find number ahead & behind x val
		if (xp >= xvals[x] && xp <= xvals[x+1])
		{
			//If x value is half the tile length more or equal than the behind num, set it to that position
			if (xp <= xvals[x]+16) t.tile.SetPosition(xvals[x],t.tile.GetPosition().y);
			//Otherwise set it to the ahead position
			if (xp > xvals[x]+16) t.tile.SetPosition(xvals[x+1],t.tile.GetPosition().y);
		}
	}
	//Y value modification
	for (unsigned int y=0; y<yvals.size()-1; y++)
	{
		//From vectors of nums stepped by 32, find number ahead & behind y val
		if (yp >= yvals[y] && yp <= yvals[y+1])
		{
			//If y value is half the tile length more or equal than the behind num, set it to that position
			if (yp <= yvals[y]+16) t.tile.SetPosition(t.tile.GetPosition().x, yvals[y]);
			//Else set it to the ahead position
			if (yp > yvals[y]+16) t.tile.SetPosition(t.tile.GetPosition().x, yvals[y+1]);
			
		}
	}

}


void MapToFile(char* bitmap)
{
	ofstream map("map1.txt");
	const char* table="01234";
	for(int i=0;i<H;i++) 
	{
		char buf[W+1];
		for(int x=0;x<W;x++)
		{
			if (x>4) buf[x]=table[bitmap[x+i*W]];
			else buf[x]='N';
		}
		buf[W]='\0';
		map << buf << "\n";
	}
	
	map.close();

}

int main()
{
	//Create window
	int w=200;
	int h=200;
	cout << "Enter width: ";
	cin >> w;
	cout << "Enter height: ";
	cin >> h;
	W=w;
	H=h;
	sf::RenderWindow App(sf::VideoMode(800, 600), "Map Creator for RPG Game");
	
	//Main tile container. Stores all tiles
	vector<sf::Sprite> tvect;
	
	//The grey left pane
	sf::Image i_LeftPane;
	sf::Sprite LeftPane;
	i_LeftPane.LoadFromFile("leftpane.png");
	LeftPane.SetImage(i_LeftPane);
	
    
    sf::Image save_img;
    sf::Image save_hover_img;
    sf::Sprite save;
    save_img.LoadFromFile("save.png");
    save_hover_img.LoadFromFile("save_hover.png");
    save.SetImage(save_img);
    save.SetPosition(30,550);
    
	//Create tile objects and add them to vector
	vector<Tiles> tiles;
	Tiles grass("../mattgfx/grass_tile.png", sf::Vector2f(0,150)); 
	Tiles gravel("../mattgfx/gravel_tile.png", sf::Vector2f(32,150));
	Tiles tree("../mattgfx/tree.png", sf::Vector2f(64,150));
    Tiles sand("../mattgfx/sand_tile.png",sf::Vector2f(96,150));
	tiles.push_back(grass);
	tiles.push_back(gravel);
	tiles.push_back(tree);
    tiles.push_back(sand);

	//Create bitmap by mmapping. 200x200
	char* bitmap=(char*)mmap(NULL, W*H, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if(bitmap==NULL) 
	{
			perror("null");
	}

    //view
    sf::View main;
    main.SetHalfSize(400,300);
    main.SetCenter(400,300);
    

	//booleans
	bool mmove=false;
	bool currtile=false;
	bool add=true;
    bool erase =true;
    
    //FPS rate
    sf::String str;
    str.SetText("FPS: ");
    str.SetFont(sf::Font::GetDefaultFont());
    str.SetSize(12);
    stringstream ss;
    
	while (App.IsOpened())
	{
		sf::Event Event;
		int mX=App.GetInput().GetMouseX();
		int mY=App.GetInput().GetMouseY();
		//hotfix for seg fault out of window
		if(mX<0 || mY<0) 
		{
			App.GetEvent(Event);
			continue;
		}
        sf::Vector2f MousePos = App.ConvertCoords(mX, mY, &main);
        erase=true;
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App.Close();
			//When mouse is moved do following events
			if (Event.Type == sf::Event::MouseMoved) {
				for (unsigned int x=0; x<tiles.size(); x++)
				{
					//Check if mouse is over tile on pane
					if (currtile==false && ((int)Event.MouseMove.X >=tiles[x].start_pos.x && (int)Event.MouseMove.X <=tiles[x].start_pos.x+32) &&
					((int)Event.MouseMove.Y >= tiles[x].start_pos.y  && (int)Event.MouseMove.Y <= tiles[x].start_pos.y+32 ))
					{
						tiles[x].is_clicked=true;
						currtile=true;
					}
					//If mouse over tile on pane, set it to move with mouse
					if (tiles[x].is_clicked)
					{
						if (MousePos.y>=16)	
						{
							//cout << MousePos.y << endl;
							tiles[x].tile.SetPosition(MousePos.x-16,MousePos.y-16);
							allign(tiles[x]);
						}
					}
				}
			}
			//If a mouse button is clicked, do following events
			if (Event.Type==sf::Event::MouseButtonPressed)
			{
				//if mouse in range of left-pane edge - inf
				if ((int)Event.MouseButton.X > 160)
				{				
					//If right clicked
					if (Event.MouseButton.Button==0)
					{
						for (unsigned int x=0; x<tiles.size(); x++) 
						{
							//If the tile is set to move
							if (tiles[x].is_clicked) 
							{
                                erase=false;
								add=true;
								tiles[x].tile.SetPosition(MousePos.x-16,MousePos.y-16);
								allign(tiles[x]);
								//Check if tile is already exisiting in the same position
								//Makes sure no more than 1 tile per spot
								for (unsigned int y=0; y<tvect.size(); y++)
								{
									if ((int)tvect[y].GetPosition().x == tiles[x].tile.GetPosition().x && 
									(int)tvect[y].GetPosition().y == tiles[x].tile.GetPosition().y)
									add=false;
								}
								
								if (add == true) {
									tvect.push_back(tiles[x].tile);
									int X=round(double(tiles[x].tile.GetPosition().x)/32);
									int Y=round(double(tiles[x].tile.GetPosition().y)/32);
									int I=(int)(X+Y*W);
									if (x==0) bitmap[I] = 1;
									else if (x==1) bitmap[I] = 0;
									else  bitmap[I] = x;
								}
								mmove=true;
							}
						}
                        if (erase==false) NULL;
                        else
                        {
                            for (unsigned int y=0; y<tvect.size(); y++)
                            {
                                if ((MousePos.x >= tvect[y].GetPosition().x && MousePos.x <= tvect[y].GetPosition().x+32) &&
                                (MousePos.y >= tvect[y].GetPosition().y && MousePos.y <= tvect[y].GetPosition().y+32))
                                {
									int X=round(double(tvect[y].GetPosition().x)/32);
									int Y=round(double(tvect[y].GetPosition().y)/32);
									int I=(int)(X+Y*W);
									bitmap[I]=0;
                                    tvect.erase(tvect.begin()+y);
                                    break;
                                }
                            }
                        }
					}
				}
                else 
                {
                    mmove=false;
					if ((MousePos.x >= save.GetPosition().x  && MousePos.x  <= save.GetPosition().x+save_img.GetWidth()) &&
                    (MousePos.y  >= save.GetPosition().y && MousePos.y  <= save.GetPosition().y+save_img.GetHeight()))       
                    {
                        MapToFile(bitmap);
                    }
                }
				//If Left Clicked
				if (Event.MouseButton.Button==1)
				{
					//Make tile go back to original spot
					for (unsigned int x=0; x<tiles.size(); x++)
					{
						tiles[x].is_clicked=false;
						currtile=false;
						tiles[x].tile.SetPosition(tiles[x].start_pos);
					}
				}

			}
			
			//When you let go of the mouse clicker
			else if (Event.Type==sf::Event::MouseButtonReleased) 
			{
				mmove=false;
			}
			
			//When mouse is moved
			else if (Event.Type==sf::Event::MouseMoved)
			{
				//if mouse in range of left-pane edge - inf
				if ((int)Event.MouseMove.X > 160 && (int)Event.MouseMove.Y >= 1)
                {
					//cout << (int)Event.MouseMove.Y << endl;
                    //if set to drag
                    if (mmove)
                    {
                        for (unsigned int x=0; x<tiles.size(); x++)
                        {
                            //if tile is set to move
                            if (tiles[x].is_clicked) 
                            {
                                add=true;
                                erase=false;
                                //Check if tile is already exisiting in the same position
                                //Makes sure no more than 1 tile per spot
                                for (unsigned int y=0; y<tvect.size(); y++)
                                {
                                    if ((int)tvect[y].GetPosition().x == tiles[x].tile.GetPosition().x && 
                                    (int)tvect[y].GetPosition().y == tiles[x].tile.GetPosition().y)
                                    add=false;
                                }
                                if (add) {
									tvect.push_back(tiles[x].tile);
									int X=round(double(tiles[x].tile.GetPosition().x)/32);
									int Y=round(double(tiles[x].tile.GetPosition().y)/32);
									int I=(int)(X+Y*W);
									if (x==0) bitmap[I] = 1;
									else if (x==1) bitmap[I] = 0;
									else  bitmap[I] = x;
								}
                            }
						}
                    }
				}
                if ((int)Event.MouseMove.X <= 160 && (int)Event.MouseMove.Y >= 1)
                {
                    if ((MousePos.x >= save.GetPosition().x  && MousePos.x <= save.GetPosition().x+save_img.GetWidth()) &&
                    (MousePos.y >= save.GetPosition().y && MousePos.y <= save.GetPosition().y+save_img.GetHeight()))
                    {
                        save.SetImage(save_hover_img);
                    }
                    else save.SetImage(save_img);
                    
                }
			}
		}
        
        if (App.GetInput().IsKeyDown(sf::Key::Right))
        {
            main.Move(6,0);
        }
        else if (App.GetInput().IsKeyDown(sf::Key::Down))
        {
            main.Move(0,6);
        }
        if ((int)main.GetCenter().x-400 >= 0) if (App.GetInput().IsKeyDown(sf::Key::Left))
        {
            main.Move(-6,0);
        }
        if ((int)main.GetCenter().y-300 >= 0) if (App.GetInput().IsKeyDown(sf::Key::Up))
        {
            main.Move(0,-6);
        }
        
		if (App.GetInput().IsKeyDown(sf::Key::C))
		{
			tvect.clear();
		}
        
        for (unsigned int x=0; x<tiles.size(); x++)
        {
            if (tiles[x].is_clicked == false) tiles[x].tile.SetPosition(main.GetCenter().x-400+tiles[x].start_pos.x, main.GetCenter().y-300+tiles[x].start_pos.y);
        }
		//Clear window
		App.Clear();
		ss.str("");
		ss << 1/App.GetFrameTime();
		str.SetText("FPS: "+ss.str());
        //Set the window view to the 2d camera
        App.SetView(main);
		//Draw all the tiles added to the vector
		for (unsigned int x=0; x<tvect.size(); x++) 
		{
			if ((tvect[x].GetPosition().x >= main.GetCenter().x-400 && tvect[x].GetPosition().x <= main.GetCenter().x+400) &&
			(tvect[x].GetPosition().y >= main.GetCenter().y-332 && tvect[x].GetPosition().y <= main.GetCenter().y+332))
			App.Draw(tvect[x]);
		}
        LeftPane.SetPosition(main.GetCenter().x-400,main.GetCenter().y-300);
        //Draw left pane
        App.Draw(LeftPane);
		//Draw tiles on the pane
		for (unsigned int x=0; x<tiles.size(); x++) 
		{
			App.Draw(tiles[x].tile);
		}
        save.SetPosition(main.GetCenter().x-370,main.GetCenter().y+250);
        str.SetPosition(main.GetCenter().x+300,main.GetCenter().y-300);
        App.Draw(save);
        App.Draw(str);
		//Display everything
		App.Display();
	}
	return EXIT_SUCCESS;
}
