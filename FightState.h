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
#include "Hero.h"
#include "Fight.h"
#include "BarHP.h"
#include "ItemBar.h"

class FightState : public State
{
	private:
		RenderWindow* myWindow;

		Button* attack1;
		Button* attack2;
		Button* attack3;
		Button* attack4;

		SysButton* fromFight;

		BarHP* monsterBar;
		BarHP* heroBar;
		ItemBar* myItemBar;
		//bohater
		Hero* myHero;

		//tlo
		Texture backTexture;
		Sprite backSprite;

		//bar
		Texture barTexture;
		Sprite barSprite;

		//inne
		int rerolls = 3;

		//tekst
		Font usedFont;
		wstring usedText;
		sf::String myText;
		Text text;
		string enemyName;

		wifstream myFile;
		int oldMode;
		void getText();

		//przeciwnik
		MonsterClasses* myMonster;
		int monsterMaxHp;
		bool turn;
		Texture monsterTexture;
		Sprite monsterSprite;
		void setMonsterType(int);
		void setMonsterSprite(int);


	public:
		FightState(RenderWindow*, Hero*, SysButton*, int);
		void update(Vector2i, bool);
		void draw();
		//bool darken();
		//bool brighten();
		~FightState();
};

FightState::FightState(RenderWindow* borrowedWindow, Hero* borrowedHero, SysButton* borrowedButton, int monsterType)
	:myFile("Plot/Plot.txt"), State()
{
	myWindow = borrowedWindow;
	myHero = borrowedHero;
	myMonster = new MonsterClasses;
	setMonsterType(monsterType);
	setMonsterSprite(monsterType);
	monsterMaxHp = myMonster->getHAPE();
	turn = false;
	
//przyciski
	attack1 = new Button(50, 500, 200, 100, L"Atak1", 0.75);
	attack2 = new Button(230, 500, 200, 100, L"Atak2", 0.75);
	attack3 = new Button(410, 500, 200, 100, L"Atak3", 0.75);
	attack4 = new Button(590, 500, 200, 100, L"Mikstura", 0.75);

	fromFight = borrowedButton;

	monsterBar = new BarHP(221, 0, enemyName, myMonster->getHAPE(), monsterMaxHp, Color::Red);
	heroBar = new BarHP(221, 420, "Bohater", myHero->getHP(), myHero->getMaxHP(), Color::Green);

	//ustawienie kurtyny 
	myItemBar = new ItemBar(100, 352, myHero->checkPot());
	//504
	
	//wczytywanie
	if (!barTexture.loadFromFile("Textures/main-bar.png"))
	{
		cout << "Coudn't load a texture" << endl;
	}

	//wczytywanie fontu
	if (!usedFont.loadFromFile("Fonts/Arial.ttf"))
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
	text.setCharacterSize(20);
	text.setFillColor(Color(255, 216, 2, 255));

	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(1.5);

	text.setPosition(100, 0);

}

void FightState::update(Vector2i mousePosition, bool isClicked)
{
	if(brighten())
	{
		if (heroBar->update(myHero->getHP()) and monsterBar->update(myMonster->getHAPE()))
		{
			myItemBar->update(myHero->checkPot());
			if (myMonster->getHAPE() <= 0 or myHero->getHP() <= 0)
			{
				fromFight->fuse = true;
			}
			else
			{
				switch (turn)
				{
					case true:
					{
						int monsterAttack = d20Throw();

						if (monsterAttack > 0 and monsterAttack < 8)
						{
							myHero->subtractHP(myMonster->doAttack1());
							turn = !turn;
						}
						else if (monsterAttack > 7 and monsterAttack < 20)
						{
							myHero->subtractHP(myMonster->doAttack2());
							turn = !turn;
						}
						else if (monsterAttack == 20)
						{
							myHero->subtractHP(myMonster->doAttack3());
							turn = !turn;
						}

						break;
					}
					case false:
					{
						if (attack1->update(mousePosition, isClicked))
						{
							myMonster->subtractHP(myHero->doAttack1()/10);

							turn = !turn;
						}
						else if (attack2->update(mousePosition, isClicked))
						{
							myMonster->subtractHP(myHero->doAttack2()/10);

							turn = !turn;
						}
						else if (attack3->update(mousePosition, isClicked))
						{
							myMonster->subtractHP(myHero->doAttack3()/10);

							turn = !turn;
						}
						else if (attack4->update(mousePosition, isClicked))
						{
							myHero->consumePot();
						}
						break;
					}
				}
			}
		}
	}
}

void FightState::draw()
{
	myWindow->clear(Color::White);
	myWindow->draw(backSprite);

//sprite potwora
	myWindow->draw(monsterSprite);

//poty
	myWindow->draw(myItemBar->ItemBarSprite);
	myWindow->draw(myItemBar->PotionSprite);

//g³owny pasek
	myWindow->draw(barSprite);

//przyciski walki
	myWindow->draw(attack1->buttonSprite);
	myWindow->draw(attack1->text);

	myWindow->draw(attack2->buttonSprite);
	myWindow->draw(attack2->text);

	myWindow->draw(attack3->buttonSprite);
	myWindow->draw(attack3->text);

	myWindow->draw(attack4->buttonSprite);
	myWindow->draw(attack4->text);


//Bar HP potwora
	myWindow->draw(monsterBar->BarHPSprite);
	myWindow->draw(monsterBar->shadowBar);
	myWindow->draw(monsterBar->bar);
	myWindow->draw(monsterBar->nameText);
	myWindow->draw(monsterBar->hpText);
	
//Bar HP bohatera
	myWindow->draw(heroBar->BarHPSprite);
	myWindow->draw(heroBar->shadowBar);
	myWindow->draw(heroBar->bar);
	myWindow->draw(heroBar->nameText);
	myWindow->draw(heroBar->hpText);

//curtain
	myWindow->draw(curtain);


	myWindow->display();
}

FightState::~FightState()
{
	delete myMonster;
	delete attack1;
	delete attack2;
	delete attack3;
	delete attack4;
	delete heroBar;
	delete monsterBar;
	delete myItemBar;
}


void FightState::getText()
{
	oldMode = _setmode(_fileno(stdout), _O_U16TEXT);
	locale uft8_locale(locale(), new codecvt_utf8<wchar_t>);
	myFile.imbue(uft8_locale);

	wchar_t bom = L'\0';
	myFile.get(bom);

	getline(myFile, usedText);

	text.setString(usedText);

	_setmode(_fileno(stdout), oldMode);

}

void FightState::setMonsterType(int monsterType)
{
	if (monsterType == 1)
	{
		myMonster = new Goblin;
		enemyName = "Goblin";
		//wczytywanie
		if (!backTexture.loadFromFile("Textures/cave-background.jpg"))
		{
			cout << "Coudn't load a texture" << endl;
		}

	}
	else if (monsterType == 2)
	{
		myMonster = new Ork;
		enemyName = "Ork";
		//wczytywanie
		if (!backTexture.loadFromFile("Textures/forest-background.png"))
		{
			cout << "Coudn't load a texture" << endl;
		}

	}
	else if (monsterType == 3)
	{
		myMonster = new Ogr;
		enemyName = "Ogr";
		//wczytywanie
		if (!backTexture.loadFromFile("Textures/forest-background.png"))
		{
			cout << "Coudn't load a texture" << endl;
		}

	}
	else
	{
		myMonster = new Cyklop;
		enemyName = "Cyklop";
		//wczytywanie
		if (!backTexture.loadFromFile("Textures/forest-background.png"))
		{
			cout << "Coudn't load a texture" << endl;
		}

	}
}

void FightState::setMonsterSprite(int monsterType)
{
	if (monsterType == 1)
	{
		monsterTexture.loadFromFile("Textures/goblin.png");
		monsterSprite.setPosition(50, 50);

	}
	else if (monsterType == 2)
	{
		 monsterTexture.loadFromFile("Textures/ork.png");
		 monsterSprite.setPosition(50, 50);

	}
	else if (monsterType == 3)
	{
		monsterTexture.loadFromFile("Textures/ogr.png");
		monsterSprite.setPosition(50, 50);

	}
	else
	{
		monsterTexture.loadFromFile("Textures/cyklop.png");
		monsterSprite.setPosition(50, 50);

	}
	monsterTexture.setSmooth(true);
	monsterSprite.setTexture(monsterTexture);
}
