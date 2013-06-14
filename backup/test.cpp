 #include <SFML/Graphics.hpp>
 #include <iostream>
 #include <vector>
 using namespace std;
 
/*
int main()
{
	sf::RenderWindow App(sf::VideoMode(800, 600), "SFML window");
	sf::Image Image;
	if (!Image.LoadFromFile("items/start_sword.png"))
		return EXIT_FAILURE;
	sf::Sprite Sprite;
	Sprite.SetImage(Image);
	

	while (App.IsOpened())
	{
		sf::Event Event;
		
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App.Close();
		}
 
 
		App.Clear();
		Sprite.SetPosition(20,20);
		App.Draw(Sprite);
		Sprite.SetPosition(200,200);		
		App.Draw(Sprite);
		App.Display();
	}
 
	return EXIT_SUCCESS;
}
*/

int main()
{
	vector<int*> t;
	int asd=5;
	int* r=&asd;
	t.push_back(r);
	
	cout << *(t[0]) << endl;	
	
}
