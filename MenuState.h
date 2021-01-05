#pragma once

#include "State.h"
#include "SysButton.h"

class MenuState : public State
{
	private:
		RenderWindow * myWindow;
		SysButton *myBox;

		//tytul vvv
		Font titleFont;
		Text title;
		string gameTitle;

		//tlo
		Texture backTexture;
		Sprite backSprite;

	public:
		MenuState(RenderWindow*, SysButton*);
		void update(Vector2i, bool);
		void draw();
		~MenuState();
};

MenuState::MenuState(RenderWindow * borrowedWindow, SysButton * borrowedButton)
{
	myWindow = borrowedWindow;
	myBox = borrowedButton;

	gameTitle = "Little  Adventure";
	
	//wczytywanie t�a i fontu do obiekt�w z plik�w 
	if (!backTexture.loadFromFile("Textures/title-background.jpg"))
	{
		cout << "Coudn't load a texture" << endl;
	}

	if (!titleFont.loadFromFile("Fonts/EndorAltPl.ttf"))
	{
		cout << "Coudn't load a font." << endl;
	}
	//

	//tytul
	title.setFont(titleFont);
	title.setString(gameTitle);
	title.setCharacterSize(160);
	title.setFillColor(Color::Black);
	title.setPosition(150, 50);

	title.setOutlineColor(Color(255, 216, 2, 255));
	title.setOutlineThickness(2.5);

	//backSprite 
	backSprite.setTexture(backTexture);
}

void MenuState::update(Vector2i mousePosition, bool isClicked)
{
	// je�li ekran jest rozja�niony to rozpoczyna sprawdzanie 
	// czy metoda update obiektu sysButton zwraca prawd�. Zrobi to tylko, gdy pozycja myszy znajduje si� nad obiektem i zosta�a na nim klikni�ta
	// wtedy blokuje mo�liwo�� ponownego klikni�cia obieku i zezwala prze�adowanej metodzie update obieku sysButton na zwr�cenie warto�ci do SystemManager
	if(brighten())
	{
		if(!myBox->wasClicked and myBox->update(mousePosition, isClicked))
		{
			myBox->wasClicked = true;
			myBox->fuse = true;
		}
	}
}

void MenuState::draw()
{
	// czy�ci ekran i po kolei rysuja ka�dy obiekt na ekranie 
	myWindow->clear(Color::White);
	myWindow->draw(backSprite);

	myWindow->draw(myBox->SysButtonSprite);
	myWindow->draw(myBox->text);
	
	myWindow->draw(title);
	myWindow->draw(curtain);
	myWindow->display();

}

MenuState::~MenuState()
{
	cout << "usunieto menustate" << endl;
}