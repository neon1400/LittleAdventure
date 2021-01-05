#pragma once 

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateMachine.h"
#include <string>

using namespace std;
using namespace sf;

class SysButton
{
	private:
		int width;
		int height;
		int position_x;
		int position_y;

		int level;

		float scale;
		//graficzny staf
		Font usedFont;
		string usedText;

		Texture SysButtonTexture;

		void loadFont();
		void loadTexture();
	public:
		Sprite SysButtonSprite;
		Text text;
		RectangleShape myRectangle;

		bool fuse;
		int enemyType; // typ przeciwnika 
		bool wasClicked;

		SysButton(int, int, int, int, string, int, float);
		~SysButton();
		int update(Vector2i, bool);
		int update(); // zwraca level nadany przy tworzeniu obiektu tylko wtedy, gdy fuse jest true;
		
		void endGame() // zmienia level na 10, który jest odpowiedzialny za zmianê stanu na EndState
		{
			level = 10;
		}

};

SysButton::SysButton(int posX, int posY, int deltaX, int deltaY, string myText, int toReturn, float scale = 1)
{
//ustawienie przycisku
	position_x = posX;
	position_y = posY;
	height = deltaY;// * scale;
	width = deltaX * scale;
	usedText = myText;
	
	level = toReturn;
	fuse = false;
	wasClicked = false;
	enemyType = 0;
//rysowanie 
	loadTexture();
	SysButtonTexture.setSmooth(true);
	SysButtonSprite.setTexture(SysButtonTexture);
	SysButtonSprite.setPosition(position_x, position_y);
	SysButtonSprite.setColor(Color(200, 200, 200));

	SysButtonSprite.scale(scale, scale);

//rysowanie tekstu
	loadFont();
	text.setFont(usedFont);
	text.setString(usedText);
	text.setCharacterSize(deltaY - deltaY / 5);
	text.setFillColor(Color::Black);

	text.setPosition(position_x + (deltaX / 10 * scale), position_y - (deltaY / 6 * scale));
	text.scale(scale, scale);
}

int SysButton::update(Vector2i position, bool isClicked)
{
	SysButtonSprite.setColor(Color(200, 200, 200));

	if (position.x > (position_x) and position.x < (position_x + width))
	{
		if (position.y > (position_y) and position.y < (position_y + height))
		{
			SysButtonSprite.setColor(Color(255, 255, 255));
			if (isClicked)
			{
				return level;
			}
		}
	}
	return 0;
}

int SysButton::update()
{
	if(fuse)
	{
		return level;
	}
	return 0;
}

void SysButton::loadFont()
{
	if (!usedFont.loadFromFile("Fonts/EndorAltPl.ttf"))
	{
		cout << "Coudn't load a font." << endl;
	}
}

void SysButton::loadTexture()
{
	if (!SysButtonTexture.loadFromFile("Textures/Button-texture.jpg"))
	{
		cout << "Coudn't load a texture." << endl;
	}
}

SysButton::~SysButton()
{
	cout << "usunieto sysButton" << endl;
}
