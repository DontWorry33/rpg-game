#include "items.h"
#include "equipment.cpp"

Items::Items()
{
	//Bools for controlling inventory opening
	inventory_isopen=false;
	last_I=false;
	
	//Bools for controlling stats opening
	stats_isopen=false;
	last_S=false;
	
	loadPaths(item_paths);

	//Allocate space in 2d vector for sprites
	for (unsigned int x=0; x<8; x++)
	{
		slots.push_back(std::vector<Slot_Items*>());
		for (unsigned int y=0; y<10; y++)
		{
			slots[x].push_back(new Slot_Items);			
		}
	}
	
	for (unsigned int x=0; x<item_paths.size(); x++)
	{
		thumbspr[item_paths[x]->thumb]=item_paths[x]->usable;
		item_paths[x]->description.SetText(item_paths[x]->pt_description);
	}
	
	//Push back sprite pointers for each left slot and initalize with coords
	for (unsigned int x=0; x<5; x++)
	{
		left_slots[x]=new sf::Sprite;
	}
	left_slots_initialize();
	
	//Load and set inventory img
	inv_img.LoadFromFile("inventory/inventory.png");
	inventory.SetImage(inv_img);
	
	//Load and set gold mouse over inventory img
	mouse_over_img.LoadFromFile("inventory/mouse_over.png");
	mouse_over.SetImage(mouse_over_img);
	
	//Load and set description bar img
	desc_bar_img.LoadFromFile("inventory/desc_bar.png");
	desc_bar.SetImage(desc_bar_img);
	
	blank.LoadFromFile("mattgfx/blankimg.png");
	
	stats_img.LoadFromFile("inventory/stats.png");
	stats.SetImage(stats_img);
	
	ITEM_SIZE=32;
}

//Draws Items. Inventory when I is held.
void Items::displayItems(sf::RenderWindow& App, sf::Event& Event, sf::Sprite& ani_spr, sf::Vector2f& MousePos, Character& player)
{
	//for (unsigned int x=0; x<items.size(); x++) App.Draw(*(items[x]));
	for (unsigned int x=0; x<item_paths.size(); x++)
	{
		if (item_paths[x]->drawable==true) App.Draw(*(item_paths[x]->thumb));
	}
	bool keydown_I=App.GetInput().IsKeyDown(sf::Key::I);
	if(keydown_I && !last_I) {
		inventory_isopen=!inventory_isopen;
	}
	last_I=keydown_I;
	if (inventory_isopen) 
	{
		desc_bar.SetPosition(App.GetView().GetCenter().x-265,App.GetView().GetCenter().y-300);
		App.Draw(desc_bar);
		App.Draw(inventory);
		for (int x=0; x<left_slots.size(); x++) App.Draw(*(left_slots[x]));
		for (unsigned int x=0, a=426; x<slots.size(), a<682; x++, a+=32)
		{
			for (unsigned int y=0, b=142; y<slots[x].size(), b<462; y++,b+=32)
			{
				App.Draw(*(slots[x][y]->slot));
				if ((MousePos.x >= slots[x][y]->slot->GetPosition().x && MousePos.x <= slots[x][y]->slot->GetPosition().x+32) 
					 && (MousePos.y >= slots[x][y]->slot->GetPosition().y && MousePos.y <= slots[x][y]->slot->GetPosition().y+32))
					{
						slots[x][y]->description_text.SetPosition(App.GetView().GetCenter().x-250,App.GetView().GetCenter().y-300);
						App.Draw(slots[x][y]->description_text);
					}
					
				//red boxes over equpped items
				for (unsigned int z =0; z<item_paths.size(); z++)
				{	
					/*					
					if (slots[x][y]->slot->GetImage() == item_paths[z]->thumb_img)
						for (unsigned int a=0; a<equipped.size(); a++)
						{
							if (equipped[a] == item_paths[z]->usable) slots[x][y]->equipped=true;
						}
					*/
					auto it = find(equipped.begin(), equipped.end(), slots[x][y]->actual_sprite);
					if (it!=equipped.end())
					{
						if (slots[x][y]->actual_sprite == item_paths[z]->usable) 
						{
							slots[x][y]->equipped=true;
						}
					}
				} 
				
				if (Event.Type == sf::Event::MouseMoved)
				{
					if ((Event.MouseMove.X >= a && Event.MouseMove.X <= a+32 ) && (Event.MouseMove.Y >= b && Event.MouseMove.Y <= b+32))
					{
						mouse_over.SetPosition(slots[x][y]->slot->GetPosition());
					}
				}
				
				if (Event.Type == sf::Event::MouseButtonPressed)
				{
					if ((MousePos.x >= slots[x][y]->slot->GetPosition().x && MousePos.x <= slots[x][y]->slot->GetPosition().x+32) 
					 && (MousePos.y >= slots[x][y]->slot->GetPosition().y && MousePos.y <= slots[x][y]->slot->GetPosition().y+32))
					{
						if (slots[x][y]->equipped==false)
						{
							if (slots[x][y]->actual_sprite->GetImage() == 0) goto breakpoint;
							equipped.push_back(slots[x][y]->actual_sprite);
							slots[x][y]->equipped=true;
							player.player.swapImage(equipped);
							for (int xx=0; xx<item_paths.size(); xx++)
							{
								if (slots[x][y]->actual_sprite == item_paths[xx]->usable)
								{
									left_slots[item_paths[xx]->id]->SetImage(*(item_paths[xx]->thumb_img));
								}
							}
						breakpoint: ;
						}
						
						else if (slots[x][y]->equipped==true) 
						{
							slots[x][y]->equipped=false;
							auto it = find(equipped.begin(), equipped.end(), slots[x][y]->actual_sprite);
							if (it!=equipped.end()) equipped.erase(it);
							player.player.swapImage(equipped);
							slots[x][y]->equipped_over.SetPosition(-100,-100);
							for (int xx=0; xx<item_paths.size(); xx++)
							{
								if (slots[x][y]->actual_sprite == item_paths[xx]->usable)
								{
									left_slots[item_paths[xx]->id]->SetImage(blank);
								}
							}
						}
						Event.Type=sf::Event::MouseButtonReleased;					
					}
				}
				
				if (slots[x][y]->equipped == true)
				{
					slots[x][y]->equipped_over.SetPosition(slots[x][y]->slot->GetPosition());
					App.Draw(slots[x][y]->equipped_over);					
				}
			}
		}
	App.Draw(mouse_over);
	}
}

void Items::displayStats(sf::RenderWindow& App,Character& player)
{
	bool keydown_S=App.GetInput().IsKeyDown(sf::Key::S);
	if(keydown_S && !last_S) {
		stats_isopen=!stats_isopen;
	}
	last_S=keydown_S;
	if (stats_isopen) 
	{
		stats.SetPosition(App.GetView().GetCenter().x-400,App.GetView().GetCenter().y-210);
		std::cout << "health: " << player.stats.health << std::endl;
		App.Draw(stats);
		
	}
	
	
}


//Set all the items on the map
void Items::setItems(sf::RenderWindow& App)
{
	item_paths[0]->thumb->SetPosition(640,224);	item_paths[1]->thumb->SetPosition(1088,512); item_paths[2]->thumb->SetPosition(1792,768); 
	item_paths[3]->thumb->SetPosition(1452,678);item_paths[4]->thumb->SetPosition(964,790);
	for (int x=0; x<item_paths.size(); x++)
	{
		item_pos[item_paths[x]].insert({item_paths[x]->thumb->GetPosition().x,item_paths[x]->thumb->GetPosition().y});	
	}
}

//Load all the paths where the items are.
void Items::loadPaths(std::vector<Equip*>& paths)
{
	Weapon* start_sword = new Weapon("sprites/sword.png");
	Head* eye_patch = new Head("sprites/eye.png");
	Body* blue_coat = new Body("sprites/blue_coat.png");
	Body* red_supercoat = new Body("sprites/red_supercoat.png");
	Legs* black_pants = new Legs("sprites/black_pants.png");
	
	start_sword->set_thumbnail("items/start_sword.png");
	eye_patch->set_thumbnail("items/eye_patch.png");
	blue_coat->set_thumbnail("items/blue_coat.png");
	red_supercoat->set_thumbnail("items/red_supercoat.png");
	black_pants->set_thumbnail("items/black_pants.png");

	start_sword->pt_description = "A tough blade that can slice monsters easily";
	eye_patch->pt_description = "Arghh! I'm a pirate!";
	blue_coat->pt_description = "An old coat that can still impress";
	red_supercoat->pt_description = "A fine, rare piece of clothing passed down from the king's family";
	black_pants->pt_description = "Just a normal pair of pants...";
	
	paths.push_back(start_sword);
	paths.push_back(eye_patch);
	paths.push_back(blue_coat);
	paths.push_back(red_supercoat);
	paths.push_back(black_pants);

}

void Items::left_slots_initialize()
{
	left_slots[0]->SetPosition(200,100); //head slot, goes to 300,150, ID=0
	left_slots[1]->SetPosition(110,200); //weapon slot, goes to 165,350, ID=1
	left_slots[2]->SetPosition(175,200); //armor slot, goes to 325,350, ID=2
	left_slots[3]->SetPosition(335,200); //secondary slot, goes to 385,350, ID=3
	left_slots[4]->SetPosition(200,400); //Leg slot, goes to 300,500, ID=4
}

void Items::equip_item(sf::Sprite* item)
{
	 equipped.push_back(item);
}

//Destructor to clear memory
Items::~Items()
{	
	for (unsigned int i=0; i<slots.size(); i++)
	{
		for (unsigned int j=0; j<slots[i].size(); j++)
		{
			delete slots[i][j];
		}
	}
}
