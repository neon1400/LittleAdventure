#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateMachine.h"
#include <string>

using namespace std;
using namespace sf;

class SecStatsButton
{
	private:
		int position_x;
		int position_y;

		int valueToShow;
		//graficzny staf
		Font usedFont;
		wstring usedText;
		wstring maybeUsedText;
		Texture SecStatsButtonTexture;

		void loadFont();
		void loadTexture();
		void reloadText(int);
	public:
		Sprite SecStatsButtonSprite;
		Text text;
		//RectangleShape myRectangle;

		SecStatsButton(int, int, wstring, int);
		~SecStatsButton();
		void update(int);

};

SecStatsButton::SecStatsButton(int posX, int posY, wstring myText, int value)
{
//ustawienie przycisku
	position_x = posX;
	position_y = posY;
	
	maybeUsedText = myText;
	reloadText(value);

	loadTexture();
	SecStatsButtonTexture.setSmooth(true);
	SecStatsButtonSprite.setTexture(SecStatsButtonTexture);
	SecStatsButtonSprite.setPosition(position_x, position_y);
	//SecStatsButtonSprite.setColor(Color(200, 200, 200));



//rysowanie tekstu
	//usedText = "Play";
	loadFont();
	text.setFont(usedFont);
	text.setCharacterSize(50);
	text.setFillColor(Color(255, 216, 2, 255));

	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(1.5);

	text.setPosition(position_x + 70, position_y);
	//text.scale(scale, scale);
}
void SecStatsButton::update(int newValue)
{
	valueToShow = newValue;
	reloadText(valueToShow);
}

void SecStatsButton::loadFont()
{
	if (!usedFont.loadFromFile("Fonts/EndorAltPl.ttf"))
	{
		cout << "Coudn't load a font." << endl;
	}
}

void SecStatsButton::loadTexture()
{
	if (!SecStatsButtonTexture.loadFromFile("Textures/secondary-bar.jpg"))
	{
		cout << "Coudn't load a texture." << endl;
	}
}

SecStatsButton::~SecStatsButton()
{
	SecStatsButtonSprite.setColor(Color(255, 255, 255));
}

void SecStatsButton::reloadText(int newValue)
{
	valueToShow = newValue;
	if (valueToShow >= 0)
		usedText = maybeUsedText + L" " + to_wstring(valueToShow);
	else if (valueToShow == -1)
		usedText = maybeUsedText + L" Male";
	else
		usedText = maybeUsedText + L" Female";

	text.setString(usedText);

}