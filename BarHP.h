#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateMachine.h"
#include <string>

using namespace std;
using namespace sf;

class BarHP
{
	private:
		// pozycja na ekranie
		int position_x;
		int position_y;

		int valueToShow;
		int maxHp;
		int lastHp;

		//graficzny staf
		Font usedFont;
		string usedText;
		string name;
		Texture BarHPTexture;
		float width; // szerokosc paska zdrowia 
		int counter;
		void loadFont();
		void loadTexture();
		void reloadText(int); // prze³adowuje wyswietlany tekst now¹ wartoœci¹
		bool reloadBar(int); // prze³adowuje bar now¹ wartoœci¹. Odejmuje co ka¿d¹ iteracjê 1/15 róznicy miedzy LastHp a dan¹ wartoœci¹,

	public:
		Sprite BarHPSprite;
		Text nameText;
		Text hpText;
		RectangleShape bar;
		RectangleShape shadowBar;

		BarHP(int, int, string, int, int, Color);
		~BarHP();
		bool update(int); // odœwie¿a wartoœæ zdrowia na pasku 

};

BarHP::BarHP(int posX, int posY, string myText, int hp, int MaxHp, Color usedColor)
{
//ustawienie przycisku
	position_x = posX;
	position_y = posY;

	name = myText;
	loadFont();
	loadTexture();

// ustawienie tekstury 
	BarHPTexture.setSmooth(true);
	BarHPSprite.setTexture(BarHPTexture);
	BarHPSprite.setPosition(position_x, position_y);

//bar HP
	maxHp = MaxHp;
	lastHp = hp;
	width = 400;
	counter = 15;
	bar.setSize(Vector2f(400.0f, 20.0f));
	bar.setFillColor(usedColor);
	bar.setPosition(position_x + 10, position_y + 35);
//cien za HP barem
	shadowBar.setSize(Vector2f(404.0f, 24.0f));
	shadowBar.setFillColor(Color::Black);
	shadowBar.setPosition(position_x + 8, position_y + 33);

//tekst - nazwa stwora
	nameText.setString(myText);
	nameText.setFont(usedFont);
	nameText.setCharacterSize(20);
	nameText.setFillColor(Color(255, 216, 2, 255));

	nameText.setOutlineColor(Color::Black);
	nameText.setOutlineThickness(1.5);

	nameText.setPosition(position_x + 20, position_y + 5);
//tekst - hp
	reloadText(maxHp);
	hpText.setFont(usedFont);
	hpText.setCharacterSize(20);
	hpText.setFillColor(Color(255, 216, 2, 255));

	hpText.setOutlineColor(Color::Black);
	hpText.setOutlineThickness(1.5);

	hpText.setPosition(position_x + 420, position_y + 30);
}
bool BarHP::update(int newValue)
{
	//jesli wartosci s¹ ró¿ne to zaczyna zmieniaæ je dopóki ich wartoœci siê nie zrównaj¹
	if(newValue != lastHp)
	{
		reloadText(newValue);
		return reloadBar(newValue);
	}
	else 
	{
		return true;
	}
}

void BarHP::loadFont()
{
	if (!usedFont.loadFromFile("Fonts/Arial.ttf"))
	{
		cout << "Coudn't load a font." << endl;
	}
}

void BarHP::loadTexture()
{
	if (!BarHPTexture.loadFromFile("Textures/plank-bar-long.jpg"))
	{
		cout << "Coudn't load a texture." << endl;
	}
}

BarHP::~BarHP()
{}

void BarHP::reloadText(int newValue)
{
	if (newValue >= 0)
		usedText =  to_string(newValue) + "/" + to_string(maxHp);
	else 
		usedText = "0/" + to_string(maxHp);
	hpText.setString(usedText);

}

bool BarHP::reloadBar(int newHp)
{
	float tempValue = 400/maxHp;
	float deltaHp = static_cast<float>(lastHp - newHp)/15;

	width -= tempValue * deltaHp;

	if(width <= 0)
	{
		bar.setSize(Vector2f(0.0f, 20.0f));
		counter = 0;
	}
	else
	{
		bar.setSize(Vector2f(width, 20.0f));
		counter --;
	}
	if(counter == 0)
	{
		lastHp = newHp;
		counter = 15;
		return true;
	}
	else 
		return false;
}