#pragma once
#pragma once

#include "State.h"
#include "button.h"
#include "charButton.h"

class ClassState : public State
{
	private:
		RenderWindow* myWindow;
		SysButton* accept;

		CharButton* leftCharacter;
		CharButton* middleCharacter;
		CharButton* rightCharacter;

		Hero* myHero;
		//tlo
		Texture backTexture;
		Sprite backSprite;

		//bar
		Texture barTexture;
		Sprite barSprite;
		
		bool wasClicked;

		//tekst
		Font usedFont;
		wstring usedText;
		wstring secondUsedText;
		Text text;
		Text secondText;
	public:
		ClassState(RenderWindow*, Hero*, SysButton*);
		void update(Vector2i, bool);
		void draw();
		~ClassState();
};

ClassState::ClassState(RenderWindow* borrowedWindow, Hero* borrowedHero, SysButton* borrowedButton)
{
	myWindow = borrowedWindow;
	myHero = borrowedHero;
	accept = borrowedButton;

	usedText = L"Wybierz swoj¹ klasê";
	secondUsedText = L"Bêdzie mieæ to wp³yw na obra¿enia";

	wasClicked = false;
	// przyciski wyboru postaci
	leftCharacter = new CharButton(0, 0, 250, 400, L"Czarodziej", L"Inteligencja", "Wizard.png");
	middleCharacter = new CharButton(276, 0, 250, 400, L"Paladyn", L"Si³a", "Paladin.png");
	rightCharacter = new CharButton(551, 0, 250, 400, L"£otrzyk", L"Zrêcznoœæ", "Rogue.png");

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
	//wczytywanie
	if (!usedFont.loadFromFile("Fonts/EndorAltPl.ttf"))
	{
		cout << "Coudn't load a font." << endl;
	}
	backSprite.setTexture(backTexture);
	
	//backSprite
	barTexture.setSmooth(true);
	barSprite.setTexture(barTexture);

	//tekst
	text.setFont(usedFont);
	text.setString(usedText);
	text.setCharacterSize(70);
	text.setFillColor(Color(255, 216, 2, 255));

	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(1.5);
	FloatRect size = text.getLocalBounds();
	text.setPosition((800 - size.width) / 2, 420);

	secondText.setFont(usedFont);
	secondText.setString(secondUsedText);
	secondText.setCharacterSize(70);
	secondText.setFillColor(Color(255, 216, 2, 255));

	secondText.setOutlineColor(Color::Black);
	secondText.setOutlineThickness(1.5);
	size = secondText.getLocalBounds();
	secondText.setPosition((800 - size.width) / 2, 470);
}

void ClassState::update(Vector2i mousePosition, bool isClicked)
{
	if(brighten())
	{
		if (!wasClicked and leftCharacter->update(mousePosition, isClicked))
		{
			myHero->assignClass(1);
			wasClicked = true;
			accept->fuse = true;
		}
		if (!wasClicked and middleCharacter->update(mousePosition, isClicked))
		{
			myHero->assignClass(2);
			wasClicked = true;
			accept->fuse = true;
		}
		if (!wasClicked and rightCharacter->update(mousePosition, isClicked))
		{
			myHero->assignClass(3);
			wasClicked = true;
			accept->fuse = true;
		}
	}
}

void ClassState::draw()
{
	myWindow->clear(Color::White);
	myWindow->draw(backSprite);

	//przyciski postaci
	myWindow->draw(leftCharacter->CharButtonSprite);
	myWindow->draw(leftCharacter->heroSprite);
	myWindow->draw(leftCharacter->text);


	myWindow->draw(middleCharacter->CharButtonSprite);
	myWindow->draw(middleCharacter->heroSprite);
	myWindow->draw(middleCharacter->text);
	myWindow->draw(middleCharacter->secondText);

	myWindow->draw(rightCharacter->CharButtonSprite);
	myWindow->draw(rightCharacter->heroSprite);
	myWindow->draw(rightCharacter->text);
	myWindow->draw(rightCharacter->secondText);

	//g³owny pasek
	myWindow->draw(barSprite);

	//kawalek lewego przycisku
	myWindow->draw(leftCharacter->secondText);

	//tekst 
	myWindow->draw(text);
	myWindow->draw(secondText);

	myWindow->draw(curtain);

	myWindow->display();
}

ClassState::~ClassState()
{
	delete leftCharacter;
	delete rightCharacter;
	delete middleCharacter;
	cout << "usunieto classstate" << endl;

}