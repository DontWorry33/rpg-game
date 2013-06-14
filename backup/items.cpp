#include "items.h"
#include "Other/testitems.cpp"
Items::Items()
{
	loadPaths(item_paths, sprite_paths);
	
		
	//Pushes back empty sf::sprite/image pointers to vector
	//Loads files from item_paths (see loadPaths()) and sets sprites in item vector to load images
	for (unsigned int x=0; x<item_paths.size(); x++)
	{
		item_imgs.push_back(new sf::Image);
		items.push_back(new sf::Sprite);
		item_imgs[x]->LoadFromFile(item_paths[x]);
		items[x]->SetImage(*item_imgs[x]);
	}
	
	
	//Pushes back empty sf::image pointers to sf::image vector containing sprite images
	//Loads sprite images from the sprite paths
	for (unsigned int x=0; x<sprite_paths.size(); x++)
	{
		sprite_items.push_back(new sf::Image);
		sprite_spr.push_back(new sf::Sprite);
		sprite_items[x]->LoadFromFile(sprite_paths[x]);
		sprite_spr[x]->SetImage(*sprite_items[x]);
		std::cout << "Size: " << sprite_spr.size() << std::endl;
	}
	//slots.push_back(std::vector<sf::Sprite*>());
	//Allocate space in 2d vector for sprites
	for (unsigned int x=0; x<8; x++)
	{
		slots.push_back(std::vector<sf::Sprite*>());
		for (unsigned int y=0; y<10; y++)
		{
			slots[x].push_back(new sf::Sprite);			
		}
	}
	
	for (unsigned int x=0; x<sprite_spr.size(); x++)
	{
		thumbspr[items[x]]=sprite_spr[x];
	}
	
	//Push back sprite pointers for each left slot and initalize with coords
	for (unsigned int x=0; x<5; x++)
	{
		left_slots[x]=new sf::Sprite;
	}
	left_slots_initialize(left_slots);
	
	//Load and set inventory img
	inv_img.LoadFromFile("inventory/inventory.png");
	inventory.SetImage(inv_img);
	
	//Load and set gold mouse over inventory img
	mouse_over_img.LoadFromFile("inventory/mouse_over.png");
	mouse_over.SetImage(mouse_over_img);
	
	thumb_id_initialize(items,item_paths,thumb_id);
	
	ITEM_SIZE=32;
}

//Draws Items. Inventory when I is held.
void Items::displayItems(sf::RenderWindow& App, sf::Event& Event, sf::Sprite& ani_spr)
{
	for (unsigned int x=0; x<items.size(); x++) App.Draw(*(items[x]));
	if (App.GetInput().IsKeyDown(sf::Key::I)) 
	{
		App.Draw(inventory);
		for (int x=0; x<left_slots.size(); x++) App.Draw(*(left_slots[x]));
		for (unsigned int x=0, a=426; x<slots.size(), a<426+(32*8); x++, a+=32)
		{
			for (unsigned int y=0, b=142; y<slots[x].size(), b<142+(32*10); y++,b+=32)
			{
				App.Draw(*(slots[x][y]));
				if (Event.Type == sf::Event::MouseMoved)
				{
					//std::cout << "X: " << Event.MouseMove.X << "\nY: " << Event.MouseMove.Y << std::endl; 
					if ((Event.MouseMove.X >= a && Event.MouseMove.X <= a+32 ) && (Event.MouseMove.Y >= b && Event.MouseMove.Y <= b+32))
					{
						mouse_over.SetPosition(slots[x][y]->GetPosition());
						
					}
				}
			}
		}
	App.Draw(mouse_over);
	}
}

//Set all the items on the map
void Items::setItems(sf::RenderWindow& App)
{
	items[0]->SetPosition(640,224);	items[1]->SetPosition(1088,512); items[2]->SetPosition(1792,768); items[3]->SetPosition(1452,678);
	items[4]->SetPosition(964,790);
	item_pos[(items[0])].insert(std::pair<int,int>(640,256));
	item_pos[(items[1])].insert(std::pair<int,int>(1088,512));
	item_pos[(items[2])].insert(std::pair<int,int>(1792,768));
	item_pos[(items[3])].insert(std::pair<int,int>(1452,678));
	item_pos[(items[4])].insert(std::pair<int,int>(964,790));
}

//Load all the paths where the items are.
void Items::loadPaths(std::vector<std::string>& paths, std::vector<std::string>& spr_paths)
{
	//Weapon sword("items/start_sword.png");
	
	//thumbnails drawn on map
	paths.push_back("items/start_sword.png");
	paths.push_back("items/eye_patch.png");
	paths.push_back("items/blue_coat.png");
	paths.push_back("items/red_supercoat.png");
	paths.push_back("items/black_pants.png");
	
	//Base items to be "equipped"
	spr_paths.push_back("sprites/sword.png");
	spr_paths.push_back("sprites/eye.png");
	spr_paths.push_back("sprites/blue_coat.png");
	spr_paths.push_back("sprites/red_supercoat.png");
	spr_paths.push_back("sprites/black_pants.png");
}

void Items::left_slots_initialize(std::map<int,sf::Sprite*>& ls)
{
	ls[0]->SetPosition(200,100); //head slot, goes to 300,150, ID=0
	ls[1]->SetPosition(110,200); //weapon slot, goes to 165,350, ID=1
	ls[2]->SetPosition(175,200); //armor slot, goes to 325,350, ID=2
	ls[3]->SetPosition(335,200); //secondary slot, goes to 385,350, ID=3
	ls[4]->SetPosition(200,400); //Leg slot, goes to 300,500, ID=4
}

void Items::thumb_id_initialize(std::vector<sf::Sprite*> items, 
								std::vector<std::string> item_paths, 
								std::map<sf::Sprite*, int>& thumb_id)
{
	//0-0 weapon, 1-1 head, 2-2 armor, 
	thumb_id[items[0]]=1; //sword
	
	thumb_id[items[1]]=0; //eyepatch
	
	thumb_id[items[2]]=2; //blue coat
	thumb_id[items[3]]=2; //red super coat
	
	thumb_id[items[4]]=4;//black pants
}

void Items::equip_item(sf::Sprite* item)
{
	 equipped.push_back(item);
}
//Destructor to clear memory
Items::~Items()
{	
	for(unsigned int i=0;i<item_imgs.size();i++)
		delete item_imgs[i];
	for(unsigned int i=0;i<sprite_items.size();i++)
		delete sprite_items[i];
	for (unsigned int i=0; i<slots.size(); i++)
	{
		for (unsigned int j=0; j<slots[i].size(); j++)
		{
			delete slots[i][j];
		}
	}
}
