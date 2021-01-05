#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateMachine.h"
#include <string>

using namespace std;
using namespace sf;

class StatsButton
{
	private:
		int position_x;
		int position_y;

		int valueToShow;
		//graficzny staf
		Font usedFont;
		wstring usedText;
		wstring maybeUsedText;
		Texture StatsButtonTexture;

		void loadFont();
		void loadTexture();
		void reloadText(int);
	public:
		Sprite StatsButtonSprite;
		Text text;
		//RectangleShape myRectangle;

		StatsButton(int, int, wstring, int);
		~StatsButton();
		void update(int);

};

	StatsButton::StatsButton(int posX, int posY, wstring myText, int value)
	{
	//ustawienie przycisku
		position_x = posX;
		position_y = posY;
	
		maybeUsedText = myText;
		reloadText(value);

		loadTexture();
		StatsButtonTexture.setSmooth(true);
		StatsButtonSprite.setTexture(StatsButtonTexture);
		StatsButtonSprite.setPosition(position_x, position_y);
		//StatsButtonSprite.setColor(Color(200, 200, 200));



	//rysowanie tekstu
		//usedText = "Play";
		loadFont();
		text.setFont(usedFont);
		text.setCharacterSize(50);
		text.setFillColor(Color(255, 216, 2, 255));

		text.setOutlineColor(Color::Black);
		text.setOutlineThickness(1.5);

		text.setPosition(position_x + 20, position_y);
		//text.scale(scale, scale);
	}
	void StatsButton::update(int newValue)
	{
		valueToShow = newValue;
		reloadText(valueToShow);
	}

	void StatsButton::loadFont()
	{
		if (!usedFont.loadFromFile("Fonts/EndorAltPl.ttf"))
		{
			cout << "Coudn't load a font." << endl;
		}
	}

	void StatsButton::loadTexture()
	{
		if (!StatsButtonTexture.loadFromFile("Textures/plank-bar.jpg"))
		{
			cout << "Coudn't load a texture." << endl;
		}
	}

	StatsButton::~StatsButton()
	{
		StatsButtonSprite.setColor(Color(255, 255, 255));
	}

	void StatsButton::reloadText(int newValue)
	{
		valueToShow = newValue;
		if (valueToShow >= 0)
			usedText = maybeUsedText + " " + to_wstring(valueToShow);
		else if (valueToShow == -1)
			usedText = maybeUsedText + L" Mê¿czyzna";
		else
			usedText = maybeUsedText + L" Kobieta";

		text.setString(usedText);

	}