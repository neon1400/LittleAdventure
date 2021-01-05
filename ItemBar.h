#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateMachine.h"
#include <string>

using namespace std;
using namespace sf;

class ItemBar
{
	private:
	int position_x;
	int position_y;

	int valueToShow;
	//graficzny staf
	Font usedFont;
	string usedText;
	string maybeUsedText;
	Texture ItemBarTexture;
	Texture PotionTexture;

	void loadFont();
	void loadTexture();

	public:
	Sprite ItemBarSprite;
	Text text;
	RectangleShape myRectangle;
	Sprite PotionSprite;

	ItemBar(int, int, int);
	~ItemBar();
	void update(int);

};

ItemBar::ItemBar(int posX, int posY, int value)
{
//ustawienie przycisku
	position_x = posX;
	position_y = posY;

	//PotionTexture = new Texture;
	loadTexture();

	ItemBarTexture.setSmooth(true);
	ItemBarSprite.setTexture(ItemBarTexture);
	ItemBarSprite.setPosition(position_x, position_y);
	//ItemBarSprite.setColor(Color(200, 200, 200));


//prostokat
	PotionTexture.setRepeated(true);
	//PotionTexture->setSmooth(true);
	

	PotionSprite.setTexture(PotionTexture);
	PotionSprite.setPosition(position_x, position_y);
	PotionSprite.setTextureRect({0 ,0, 74 * value, 68 });
}
void ItemBar::update(int newValue)
{
	PotionSprite.setTextureRect({ 0 ,0, 74 *  newValue, 68 });
}

void ItemBar::loadFont()
{
	if (!usedFont.loadFromFile("Fonts/EndorAltPl.ttf"))
	{
		cout << "Coudn't load a font." << endl;
	}
}

void ItemBar::loadTexture()
{
	if (!ItemBarTexture.loadFromFile("Textures/item-bar.jpg"))
	{
		cout << "Coudn't load a texture." << endl;
	}
	if(!PotionTexture.loadFromFile("Textures/potion.png"))
	{
		cout << "Coudn't load a texture." << endl;
	}
}

ItemBar::~ItemBar()
{
	ItemBarSprite.setColor(Color(255, 255, 255));
}
