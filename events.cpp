#include "events.h"
#include "slotitems.cpp"

Events::Events()
{
		
}
//X=400,Y=300
void setLeftSlots(std::map<int, sf::Sprite*>& ls,int X,int Y)
{
	ls[0]->SetPosition(X-180,Y-200);
	ls[1]->SetPosition(X-290,Y-90);
	ls[2]->SetPosition(X-215,Y-100);
	ls[3]->SetPosition(X-65,Y-100);
	ls[4]->SetPosition(X-200,Y+100);
}

void setRect(std::map<int, sf::Sprite*>& ls, Character& player)
{
	for (unsigned int x=0; x<ls.size(); x++)
	{
		//left,top,right,bottom
		if (ls[x]->GetImage()!=0) 
		{
			if (ls[0]->GetScale().x != 2.f) ls[0]->Scale(2.f,1.f);
			if (ls[1]->GetScale().y != 3.f) ls[1]->Scale(1.5,3.f);
			if (ls[2]->GetScale().x != 4.f) ls[2]->Scale(4.f,4.f);
			if (ls[3]->GetScale().y != 2.f) ls[3]->Scale(1.5,2.f);
			if (ls[4]->GetScale().x != 3.f) ls[4]->Scale(3.f,3.f);
		}
	}
}

void Events::findItem(Items& items, Character& player)
{

    //Initialize variables/functions
	int xPos = player.player.ani_spr.GetPosition().x;
	int yPos = player.player.ani_spr.GetPosition().y;
	setLeftSlots(items.left_slots,xPos,yPos);
	setRect(items.left_slots,player);
	items.inventory.SetPosition(xPos-300,yPos-200);
	int invenX = 324;
	int invenY = 40;
	bool set=false;
    
    
	//Set the 2d vector of inventory space's position accordingly
	for (unsigned int x=0; x<items.slots.size(); x++)
	{
		invenY = 40;
		for (unsigned int y=0; y<items.slots[x].size(); y++)
		{
			items.slots[x][y]->slot->SetPosition(items.inventory.GetPosition().x+invenX,items.inventory.GetPosition().y+invenY);
			invenY+=32;
		}
		invenX+=32;
	}
    //finding an item is defaultly false until player moves over it
	bool found=false;  
    
	for (auto it=items.item_pos.begin(); it!=items.item_pos.end(); it++)
	{
        //it2->first = xpos of thumbnail, it2->second = ypos of thumbnail
		for (auto it2=it->second.begin(); it2!=it->second.end(); it2++)
		{
            //Check if player is standing on top of thumbnail, if so set bool found to true
			if ((xPos+(player.player.ani_img_width) >= it2->first && xPos <= it2->first+items.ITEM_SIZE) && (yPos+player.player.ani_img_height >= it2->second && yPos+player.player.ani_img_height <= it2->second+items.ITEM_SIZE))
			{
				found=true;
			}
		}
		if (found) 
		{	
			if (items.left_slots[it->first->id]->GetImage() == 0)
			{
				items.left_slots[it->first->id]->SetImage(*(it->first->thumb_img));
				items.equipped.push_back(it->first->usable);
			}
            
            //Not really a swap, just passes equipped vector to animation struct to be drawn onto character
			player.player.swapImage(items.equipped);

            it->first->drawable=false;
			for (unsigned int x=0; x<items.slots.size(); x++)
			{
				for (unsigned int y=0; y<items.slots[x].size(); y++)
				{
                    //if the slot is empty
					if (items.slots[x][y]->slot->GetImage()==0) 
					{
                        //Set the slots image to the thumbnail
						items.slots[x][y]->slot->SetImage(*(it->first->thumb_img));
						items.slots[x][y]->description_text.SetText(it->first->description.GetText());
						items.slots[x][y]->actual_sprite = it->first->usable;
						set=true;
						break;
					}
				}
                //Failsafe so it doesn't add more than once
				if (set) break;
			}
            //Erase the item from the vector of sprites and thumb pos's
			items.item_pos.erase(it);
			break;
		}
		
	}
}
	
