#pragma once

#include <fstream>
#include <string>
#include <locale>
#include <codecvt>

#include <cstdio>  // for _fileno
#include <io.h>    // for _setmode
#include <fcntl.h> // for _O_U16TEXT

#include "State.h"
#include "button.h"


class EndState : public State
{
	private:
		RenderWindow* myWindow;

		SysButton* toMenu;

		//tlo
		Texture backTexture;
		Sprite backSprite;

		//bohater
		Hero* myHero;

		//bar
		Texture barTexture;
		Sprite barSprite;

		//inne
		int rerolls = 3;

		//tekst
		Font usedFont;
		wstring usedText;
		wstring secondaryUsedText;
		Text text;
		Text secondaryText;
		int counter;
		bool pause();
	public:
		EndState(RenderWindow*, Hero*, SysButton*);
		void update(Vector2i, bool);
		void draw();
		~EndState();
};

EndState::EndState(RenderWindow* borrowedWindow, Hero* borrowedHero, SysButton* borrowedButton)
{
	myWindow = borrowedWindow;
	myHero = borrowedHero;
	//przyciski

	toMenu = borrowedButton;
	counter = 0;

	//wczytywanie
	if (!backTexture.loadFromFile("Textures/title-background.jpg"))
	{
		cout << "Coudn't load a texture" << endl;
	}

	//wczytywanie
	if (!barTexture.loadFromFile("Textures/main-bar.png"))
	{
		cout << "Coudn't load a texture" << endl;
	}



	//backSprite
	backSprite.setTexture(backTexture);
	barTexture.setSmooth(true);
	barSprite.setTexture(barTexture);

	//tekst
	if(myHero->getHP() <= 0)
	{
		//wczytywanie fontu
		if (!usedFont.loadFromFile("Fonts/OptimusPrinceps.ttf"))
		{
			cout << "Coudn't load a font." << endl;
		}
		usedText = L"YOU DIED";
		text.setFillColor(Color(103, 39, 37, 255));
		text.setPosition(150, 150);
		text.setCharacterSize(100);

		//secondaryUsedText = L"Press space to continue...";
		//secondaryText.setFillColor(Color(103, 39, 37, 255));
		//secondaryText.setPosition(250, 250);
		//secondaryText.setCharacterSize(25);

	}
	else 
	{
		//wczytywanie fontu
		if (!usedFont.loadFromFile("Fonts/ENDORALT.ttf"))
		{
			cout << "Coudn't load a font." << endl;
		}
		usedText = L"Koniec gry";

		text.setFillColor(Color::Black);
		text.setOutlineColor(Color(255, 216, 2, 255));
		text.setOutlineThickness(2.5);
		text.setPosition(250, 150);
		text.setCharacterSize(150);


	}

	text.setFont(usedFont);
	text.setString(usedText);
	secondaryText.setFont(usedFont);
	secondaryText.setString(secondaryUsedText);


}

void EndState::update(Vector2i mousePosition, bool isClicked)
{
	if (brighten())
	{
		if(myHero->getHP() <= 0)
		{
			if (pause())
			{
				toMenu->fuse = true;
			}
		}
		else
		{
			if(!toMenu->wasClicked and toMenu->update(mousePosition, isClicked))
			{
				toMenu->fuse = true;
				toMenu->wasClicked = true;
			}
		}
		
	}
}

void EndState::draw()
{
	myWindow->clear(Color::Black);
	if(myHero->getHP() > 0)
	{
		myWindow->draw(backSprite);
		
		//przycisk NextText
		myWindow->draw(toMenu->SysButtonSprite);
		myWindow->draw(toMenu->text);
	}



	//tekst
	myWindow->draw(text);
	myWindow->draw(secondaryText);
	
	//kurtyna
	myWindow->draw(curtain);

	myWindow->display();
}

EndState::~EndState()
{
	delete myHero;
}

bool EndState::pause()
{
	counter++;
	if(counter > 30)
	{
		counter = 0;
		return true;
	}
	else return false;
}