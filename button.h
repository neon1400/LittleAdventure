#pragma once 

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateMachine.h"
#include <string>

using namespace std;
using namespace sf;

class Button
{
	private:
		// sk³adniki zawieraj¹ce pozycjê obiektu oraz jego wysokoœæ i szerokoœæ
		int width;
		int height;
		int position_x;
		int position_y;
		
		float scale; // wspó³czynnik skaluj¹cy 
		
		//sk³adniki odpowiedzialne za grafikê obiektu
		Font usedFont;
		wstring usedText;

		Texture buttonTexture;

		void loadFont(); // ³aduje font tekstu do obiektu usedFont
		void loadTexture(); // ³aduje teksturê do obiektu buttonTexture
	public:
		Sprite buttonSprite;
		Text text;
		RectangleShape myRectangle;

		Button(int, int, int, int, wstring, float);
		~Button();
		bool update(Vector2i, bool);
		
};

	Button::Button(int posX, int posY, int deltaX, int deltaY, wstring myText, float scale = 1)
	{
	//ustawienie przycisku
		position_x = posX;
		position_y = posY;
		height = deltaY;// * scale;
		width = deltaX * scale;
		usedText = myText;


		loadTexture();
		buttonTexture.setSmooth(true);
		buttonSprite.setTexture(buttonTexture);
		buttonSprite.setPosition(position_x, position_y);
		buttonSprite.setColor(Color(200, 200, 200));

		buttonSprite.scale(scale, scale);

	//rysowanie tekstu
		//usedText = "Play";
		loadFont();
		text.setFont(usedFont);
		text.setString(usedText);
		text.setCharacterSize(deltaY - deltaY/5);
		text.setFillColor(Color::Black);

		text.setPosition(position_x + (deltaX/10*scale), position_y - (deltaY/6*scale));
		text.scale(scale, scale);
	}

bool Button::update(Vector2i position, bool isClicked)
{
	// jesli mysz znajduje siê nad przyciskiem do podswietla go
	// jesli dodatkowo mysz zosta³a klikniêta to zwraca true
	buttonSprite.setColor(Color(200, 200, 200));

	if (position.x > (position_x) and position.x < (position_x + width))
	{
		if(position.y > (position_y) and position.y < (position_y + height))
		{
			buttonSprite.setColor(Color(255, 255, 255));
			if(isClicked)
			{
				return true;
			}
		}	
	}
	return false;
}

void Button::loadFont()
{
	if (!usedFont.loadFromFile("Fonts/EndorAltPl.ttf"))
	{
		cout << "Coudn't load a font." << endl;
	}
}

void Button::loadTexture()
{
	if(!buttonTexture.loadFromFile("Textures/button-texture.jpg"))
	{
		cout << "Coudn't load a texture." << endl;
	}
}

Button::~Button()
{
	buttonSprite.setColor(Color(255, 255, 255));
}
