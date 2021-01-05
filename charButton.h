#pragma once 

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateMachine.h"
#include <string>

using namespace std;
using namespace sf;

class CharButton
{
	private:
		int width;
		int height;
		int position_x;
		int position_y;

		float scale;
		//graficzny staf
		Font usedFont;
		wstring usedText;
		wstring secondUsedText;

		Texture CharButtonTexture;
		Texture heroTexture;

		void loadFont();
		void loadTexture(string);
	public:
		Sprite CharButtonSprite;
		Sprite heroSprite;
		Text text;
		Text secondText;
		RectangleShape myRectangle;

		CharButton(int, int, int, int, wstring, wstring, string, float);
		~CharButton();
		bool update(Vector2i, bool);

};

	CharButton::CharButton(int posX, int posY, int deltaX, int deltaY, wstring myText, wstring ability, string heroPath, float scale = 1)
	{
	//ustawienie przycisku
		position_x = posX;
		position_y = posY;
		height = deltaY;
		width = deltaX;
		usedText = myText;
		secondUsedText = ability;	


		loadTexture(heroPath);
		CharButtonTexture.setSmooth(true);
		CharButtonSprite.setTexture(CharButtonTexture);
		CharButtonSprite.setPosition(position_x, position_y);
		CharButtonSprite.setColor(Color(200, 200, 200));

		CharButtonSprite.scale(scale, scale);
		
		heroTexture.setSmooth(true);
		heroSprite.setTexture(heroTexture);
		heroSprite.setPosition(position_x + deltaX*0.125, position_y);
		heroSprite.setColor(Color(200,200,200));
		heroSprite.setScale(0.75, 0.75);


	//rysowanie tekstu
		loadFont();
		text.setFont(usedFont);
		text.setString(usedText);
		text.setCharacterSize(50);
		text.setFillColor(Color(255, 216, 2, 255));

		text.setOutlineColor(Color::Black);
		text.setOutlineThickness(1.5);
		FloatRect size = text.getLocalBounds();
		text.setPosition(position_x + (width - size.width)/2 , 280);
		text.scale(scale, scale);

		secondText.setFont(usedFont);
		secondText.setString(secondUsedText);
		secondText.setCharacterSize(50);
		secondText.setFillColor(Color(255, 216, 2, 255));

		secondText.setOutlineColor(Color::Black);
		secondText.setOutlineThickness(1.5);
		size = secondText.getLocalBounds();
		secondText.setPosition(position_x + (width - size.width) / 2, 320);
		secondText.scale(scale, scale);
	}

	bool CharButton::update(Vector2i position, bool isClicked)
	{
		CharButtonSprite.setColor(Color(200, 200, 200));
		heroSprite.setColor(Color(200, 200, 200));
		if (position.x > (position_x) and position.x < (position_x + width))
		{
			if (position.y > (position_y) and position.y < (position_y + height))
			{
				//cout << "przycisk zostal najechany " << endl;
				CharButtonSprite.setColor(Color(255, 255, 255));
				heroSprite.setColor(Color(255, 255, 255));

				if (isClicked)
				{
					//cout << "Przycisk zostal klikniety" << endl;
					return true;
				}
			}
		}
		return false;
	}

	void CharButton::loadFont()
	{
		if (!usedFont.loadFromFile("Fonts/EndorAltPl.ttf"))
		{
			cout << "Coudn't load a font." << endl;
		}
	}

	void CharButton::loadTexture(string heroPath)
	{
		if (!CharButtonTexture.loadFromFile("Textures/class-bar.png"))
		{
			cout << "Coudn't load a texture." << endl;
		}
		if (!heroTexture.loadFromFile("Textures/" + heroPath))
		{
			cout << "Coudn't load a hero texture." << endl;
		}
	}

	CharButton::~CharButton()
	{
		CharButtonSprite.setColor(Color(255, 255, 255));

	}
