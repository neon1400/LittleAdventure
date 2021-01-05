#pragma once

#include "State.h"
#include "button.h"
#include "StatsButton.h"
#include "Hero.h"
#include "SecStatsButton.h"

class StatsState : public State
{
	private:
		RenderWindow* myWindow;
		// przyciski
		Button* reroll; // odpowiada za ponowne losowanie statystyk
		SysButton* accept; // odpowiada za zaakceptowanie statystyk i przejscie do kolejnego stanu 

		//obiekty odpowiedzialne za wyswietlanie statystyk 
		StatsButton* Health;
		StatsButton* Inteligance;
		StatsButton* Strength;
		StatsButton* Agility;
		StatsButton* Sex;
		SecStatsButton* RerollsBar;
		
		//bohater
		Hero * myHero;

		//tlo
		Texture backTexture;
		Sprite backSprite;

		//bar
		Texture barTexture;
		Sprite barSprite;

		//ilosc pozosta³ych losowañ statystyk
		int rerolls;

		//tekst
		Font usedFont;
		string usedText;
		Text text;
	public:
		StatsState(RenderWindow*, Hero*, SysButton*);
		void update(Vector2i, bool);
		void draw();
		~StatsState();
};

StatsState::StatsState(RenderWindow* borrowedWindow, Hero* borrowedHero, SysButton* borrowedButton)
{
	myWindow = borrowedWindow;
	myHero = borrowedHero;

	usedText = "Akceptujesz te statystyki?";
	rerolls = 3;
	
	//przyciski
	reroll = new Button(50, 490, 200, 100, L"Nie", 0.75);
	accept = borrowedButton;
	
	// ramki statystyk
	// przyjmuj¹ wartoœci zwracane przez metody klasy hero
	int offset = 10;
	Health = new StatsButton(450, 0 + offset, L"Punkty ¯ycia:", myHero->getHP());
	Inteligance = new StatsButton(450, 69 + 2*offset, L"Inteligencja:", myHero->getInteligance());
	Strength = new StatsButton(450, 138 + 3*offset, L"Si³a:", myHero->getStrength());
	Agility = new StatsButton(450, 207 + 4*offset, L"Zrêcznoœæ:", myHero->getAgility());
	Sex = new StatsButton(450, 276 + 5*offset, L"P³eæ:", myHero->getSex());

	RerollsBar = new SecStatsButton(0, 0, L"Rzuty kostk¹:", rerolls);

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

	//wczytywanie fontu
	if (!usedFont.loadFromFile("Fonts/ENDORALT.ttf"))
	{
		cout << "Coudn't load a font." << endl;
	}
	
	//backSprite
	backSprite.setTexture(backTexture);
	barTexture.setSmooth(true);
	barSprite.setTexture(barTexture);

	//tekst
	text.setFont(usedFont);
	text.setString(usedText);
	text.setCharacterSize(70);
	text.setFillColor(Color(255, 216, 2, 255));

	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(1.5);

	text.setPosition(220, 450);

}

void StatsState::update(Vector2i mousePosition, bool isClicked)
{
	if(brighten())
	{
		if (!accept->wasClicked and reroll->update(mousePosition, isClicked))
		{
			if (rerolls > 0)
			{
				myHero->rerollAttribs();
				rerolls--;
				Health->update(myHero->getHP());
				Inteligance->update(myHero->getInteligance());
				Strength->update(myHero->getStrength());
				Agility->update(myHero->getAgility());
				Sex->update(myHero->getSex());

				RerollsBar->update(rerolls);
			}
		}
		if (!accept->wasClicked and accept->update(mousePosition, isClicked))
		{
			accept->fuse = true;
			accept->wasClicked = true;
		}
	}
}

void StatsState::draw()
{
	myWindow->clear(Color::White);
	myWindow->draw(backSprite);

	//statystyki postaci
	myWindow->draw(Health->StatsButtonSprite);
	myWindow->draw(Health->text);

	myWindow->draw(Inteligance->StatsButtonSprite);
	myWindow->draw(Inteligance->text);

	myWindow->draw(Strength->StatsButtonSprite);
	myWindow->draw(Strength->text);

	myWindow->draw(Agility->StatsButtonSprite);
	myWindow->draw(Agility->text);

	myWindow->draw(Sex->StatsButtonSprite);
	myWindow->draw(Sex->text);
	
	//statystyka rerolls
	myWindow->draw(RerollsBar->SecStatsButtonSprite);
	myWindow->draw(RerollsBar->text);

	//g³owny pasek
	myWindow->draw(barSprite);

	//przycisk NO
	myWindow->draw(reroll->buttonSprite);
	myWindow->draw(reroll->text);

	//przycisk YES
	myWindow->draw(accept->SysButtonSprite);
	myWindow->draw(accept->text);
	
	//tekst
	myWindow->draw(text);

	myWindow->draw(curtain);
	myWindow->display();
}

StatsState::~StatsState()
{
	delete reroll;
	cout << "usunieto statsstate" << endl;

}