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
#include "BarHP.h"
#include "StatsButton.h"
#include "ItemBar.h"

class TextState : public State
{
	private:
		RenderWindow* myWindow;
		Button* nextText;
		Button* accept;
		Button* deny;

		SysButton* fight;

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
		Font anotherFont;
		string myString;
		wstring usedText;
		wstring instructionsText;
		Text text;
		Text secText;
		Text instructions;

		wifstream myFile;
		ifstream alsoMyFile;
		int oldMode;

		string fileToRead;
		int idToFind;
		bool decisionToMake;
		bool decision;
		bool haveSomethingToFind;
		bool fuse;
		bool secFuse;
		bool canClick;

		void getText();
		void doSomeStuff();
		void doSomeOtherStuff();
		void setEnemyType(string);
		bool stringToBool(string);
		void giveReward(string);
		void getInstructions();

		//wiecej okrywy graficznej
		SecStatsButton* Inteligance;
		SecStatsButton* Strength;
		SecStatsButton* Agility;
		BarHP* heroBar;
		ItemBar* myItemBar;
		Texture StatsBackground;
		Sprite StatsBackSprite;
		
	public:
		TextState(RenderWindow*, Hero*, SysButton*);
		void update(Vector2i, bool);
		void draw();
		~TextState();
};

TextState::TextState(RenderWindow* borrowedWindow, Hero* borrowedHero, SysButton* borrowedButton)
	:alsoMyFile("Plot/Plot.txt")//, usedText(L"Załóć gęślą jaźń")
{
	myWindow = borrowedWindow;
	myHero = borrowedHero;

	//przyciski
	nextText = new Button(600, 490, 200, 100, L"Dalej", 0.75);

	accept = new Button(400, 290, 200, 100, L"Akceptuj", 0.75);
	deny = new Button(600, 290, 200, 100, L"Odrzuć", 0.75);

	fight = borrowedButton;
	canClick = true;
	fuse = false;
	secFuse = false;
	//statystyki

	int offset = 10;

	heroBar = new BarHP(0, 0, "Bohater", myHero->getHP(), myHero->getMaxHP(), Color::Green);
	Inteligance = new SecStatsButton(0, 138 + 1 * offset, L"Inteligencja:", myHero->getInteligance());
	Strength = new SecStatsButton(0, 207 + 2 * offset, L"Siła:", myHero->getStrength());
	Agility = new SecStatsButton(0, 276 + 3 * offset, L"Zręczność:", myHero->getAgility());

	myItemBar = new ItemBar(0, 69, myHero->checkPot());
	
	//ustawianie zapisu 
	idToFind = 0;
	decisionToMake = false;
	decision = false;
	haveSomethingToFind = false;
	
	doSomeStuff();

	//wczytywanie
	if (!backTexture.loadFromFile("Textures/title-background.jpg"))
	{
		cout << "Coudn't load a texture" << endl;
	}

	//wczytywanie
	if (!StatsBackground.loadFromFile("Textures/class-bar.png"))
	{
		cout << "Coudn't load a texture" << endl;
	}

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

	//wczytywanie fontu
	if (!anotherFont.loadFromFile("Fonts/EndorAltPl.ttf"))
	{
		cout << "Coudn't load a font." << endl;
	}

	//backSprite
	backSprite.setTexture(backTexture);
	barTexture.setSmooth(true);
	barSprite.setTexture(barTexture);
	
	//StatsBackSprite
	StatsBackSprite.setTexture(StatsBackground);
	StatsBackSprite.setPosition(Vector2f(0.0f, 0.0f));
	StatsBackSprite.setScale(Vector2f(1.2f, 1));
	StatsBackSprite.setColor(Color(200, 200, 200, 255));
	
	//tekst
	text.setFont(usedFont);
	text.setString(usedText);
	text.setCharacterSize(30);
	text.setFillColor(Color(255, 216, 2, 255));

	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(1.5);

	text.setPosition(Vector2f(320.0f, 70.0f));

	secText.setFont(usedFont);
	secText.setString(usedText);
	secText.setCharacterSize(30);
	secText.setFillColor(Color(255, 216, 2, 255));

	secText.setOutlineColor(Color::Black);
	secText.setOutlineThickness(1.5);

	secText.setPosition(Vector2f(320.0f, 100.0f));
	getText();
	getInstructions();
}

void TextState::update(Vector2i mousePosition, bool isClicked)
{
	if(brighten())
	{
		getInstructions();
		if(decisionToMake and myFile.eof())
		{
			if (accept->update(mousePosition, isClicked))
			{
				decision = true;
				decisionToMake = false;
				haveSomethingToFind = true;
				doSomeOtherStuff();
				getText();
			}
			if (deny->update(mousePosition, isClicked))
			{
				decision = false;
				decisionToMake = false;
				haveSomethingToFind = true;
				doSomeOtherStuff();
				getText();
			}
		}
		else
		{
			if (canClick and nextText->update(mousePosition, isClicked))
			{
				getText();
				secFuse = true;

				if (fuse and myFile.eof() and !decisionToMake)
				{
					doSomeStuff();
					myItemBar->update(myHero->checkPot());
					Inteligance->update(myHero->getInteligance());
					Strength->update(myHero->getStrength());
					Agility->update(myHero->getAgility());
					doSomeStuff();
					getText();
				}
			}
		}
	}
	else
	{
		heroBar->update(myHero->getHP());
		myItemBar->update(myHero->checkPot());
		canClick = true;
		if (secFuse)
		{
			doSomeStuff();
			doSomeStuff();
			getText();
			secFuse = false;
		}
	}
}

void TextState::draw()
{
	myWindow->clear(Color::White);
	myWindow->draw(backSprite);

	//tlo statystyk
	myWindow->draw(StatsBackSprite);

	//statystyki postaci
	myWindow->draw(Inteligance->SecStatsButtonSprite);
	myWindow->draw(Inteligance->text);

	myWindow->draw(Strength->SecStatsButtonSprite);
	myWindow->draw(Strength->text);

	myWindow->draw(Agility->SecStatsButtonSprite);
	myWindow->draw(Agility->text);
	
	//pasek zdrowia bohatera
	myWindow->draw(heroBar->BarHPSprite);
	myWindow->draw(heroBar->shadowBar);
	myWindow->draw(heroBar->bar);
	myWindow->draw(heroBar->nameText);
	myWindow->draw(heroBar->hpText);
	
	//pasek itemow
	myWindow->draw(myItemBar->ItemBarSprite);
	myWindow->draw(myItemBar->PotionSprite);

	//głowny pasek
	myWindow->draw(barSprite);

	//instrukcje
	myWindow->draw(instructions);

	if(decisionToMake and myFile.eof())
	{
		//przycisk ACCEPT
		myWindow->draw(accept->buttonSprite);
		myWindow->draw(accept->text);

		//przycisk DENY
		myWindow->draw(deny->buttonSprite);
		myWindow->draw(deny->text);
	}
	else
	{
		//przycisk NextText
		myWindow->draw(nextText->buttonSprite);
		myWindow->draw(nextText->text);
	}
	

	//tekst
	myWindow->draw(text);
	myWindow->draw(secText);

	myWindow->draw(curtain);

	myWindow->display();
}

TextState::~TextState()
{
	delete Inteligance;
	delete Strength;
	delete Agility;
	delete heroBar;
	delete myItemBar;
	delete nextText;
	delete accept;
	delete deny;
}


void TextState::getText()
{
	wstring toHelp;
	wstring another;
	oldMode = _setmode(_fileno(stdout), _O_U16TEXT);
	locale uft8_locale(locale(), new codecvt_utf8<wchar_t>);
	myFile.imbue(uft8_locale);

	wchar_t bom = L'\0';
	myFile.get(bom);
	if(myFile.eof())
	{
		usedText = L"";
		fuse = true;
	}
	else
	{
		fuse = false;
		getline(myFile, usedText);
		usedText = " " + usedText;
	}
	text.setString(usedText);

	
	if (!myFile.eof())
	{
		getline(myFile, another);

		for (int i = 3; i > 0; i--)
		{
			if (myFile.eof())
			{
				break;
			}
			else
			{
				getline(myFile, toHelp);
				another = another + "\n" + toHelp;
			}
		}

	}
	else another = L"";

	secText.setString(another);

	//_setmode(_fileno(stdout), oldMode);

}

void TextState::doSomeStuff()
{
	if(alsoMyFile.eof())
	{
		fight->endGame();
		fight->fuse = true;
	}
	bool toRead = false;
	getline(alsoMyFile, myString);

	if(myString.find("$$") != string::npos)
	{
		//cout << "zaczyna czytac" << endl;
		toRead = true;
	}

	while(toRead)
	{
		size_t tempSize;
		getline(alsoMyFile, myString);

		if (myString.find("$$") != string::npos)
		{
			//cout << "konczy czytac" << endl << endl;
			toRead = false;
		}
		else if( myString.find("action_ = ") == 0)
		{
			myString.erase(0, 10);

			//cout << myString << endl;

			if(myString == "fight")
			{
				//cout << "rozpoczeto walke " << myString << endl;
				getline(alsoMyFile, myString);				
				myString.erase(0, 14);
				
				cout << "typ przeciwnika " << myString << endl;

				setEnemyType(myString);
				cout << "Loading battle" << endl;
				canClick = false;
			}
			else if(myString == "choice")
			{
				cout << "wykryto wybor" << endl;

				getline(alsoMyFile, myString);

				if(myString.find("id_ = ") == 0)
				{
					myString.erase(0, 6);
					//cout << "przypisano id do szukania" << endl;
					idToFind = stoi(myString);
					//cout << "id do szukania = " << idToFind << endl;
					getline(alsoMyFile, myString);
					
					fileToRead = myString;
					myFile.close();
					cout << "Loading " << myString << endl;
					myFile.open("Plot/" + myString, ios::out);
				}
				decisionToMake = true;

			}
		}
		else if(myString.find("id_ = ") == 0)
		{
			//cout << "czyta id" << endl;
			myString.erase(0, 6);
			////
			//cout << "id = " << stoi(myString) << endl;
			//cout << "id do szukania = " << idToFind << endl;
			////
			if(stoi(myString) == idToFind)
			{
				//cout << "znaleziono szukane id" << endl;

				getline(alsoMyFile, myString);
				fileToRead = myString;
				myFile.close();
				cout << "Loading " << myString << endl;
				myFile.open("Plot/" + myString, ios::out);

				getline(alsoMyFile, myString);	

				if(myString.find("$$") != string::npos)
				{
					toRead = false;
					//testowe vvvvv
					haveSomethingToFind = false;
					//cout << "konczy czytac" << endl << endl;
					continue;
				}

				myString.erase(0, 12);

				if(stringToBool(myString) == decision)
				{
					cout << "znaleziono wybor gracza" << endl;
					
					getline(alsoMyFile, myString);
					myString.erase(0, 10);

					haveSomethingToFind = false;
					idToFind = stoi(myString);

					getline(alsoMyFile, myString);
					myString.erase(0, 10);
					giveReward(myString);

				}
			}
		}
	}
}

void TextState::setEnemyType(string myType)
{
	if(myType == "goblin")
	{
		fight->enemyType = 1;
	}
	else if(myType == "ork")
	{
		fight->enemyType = 2;
	}
	else if (myType == "ogr")
	{
		fight->enemyType = 3;
	}
	else if (myType == "cyklop")
	{
		fight->enemyType = 4;
	}
	else 
	{
		cout << "Cos poszlo nie tak w czytaniu z pliku potwora " << endl;
	}
	fight->fuse = true;
}

bool TextState::stringToBool(string toConvert)
{
	if(toConvert == "false") return false;
	return true;

}

void TextState::doSomeOtherStuff()
{
	while(haveSomethingToFind)
	{
		doSomeStuff();
	}

}

void TextState::giveReward(string reward)
{
	if(reward == "agility")
	{
		myHero->addAgility(2);
		cout << "dodano agility" << endl;
	}
	else if(reward == "strength")
	{
		myHero->addStrength(2);
		cout << "dodano strength" << endl;
	}
	else if(reward == "intelligence")
	{
		myHero->addInteligence(2);
		cout << "dodano intelligance" << endl;
	}
	else if(reward == "potion")
	{
		myHero->addPot(1);
		cout << "dodano potka" << endl;
	}
	else if(reward == "all")
	{
		myHero->addInteligence(2);
		myHero->addStrength(2);
		myHero->addAgility(2);

		cout << "dodano wszystko" << endl;
	}

}

void TextState::getInstructions()
{
	if(decisionToMake and myFile.eof())
	{
		instructionsText = L"Podejmij decyzję";
	}
	else
	{
		instructionsText = L"Kliknij, aby przewinąć tekst";
	}
	if(!canClick)
	{
		instructionsText = L"O Bogowie! Walka!";
	}
	instructions.setFont(anotherFont);
	instructions.setString(instructionsText);
	instructions.setCharacterSize(70);
	instructions.setFillColor(Color(255, 216, 2, 255));

	instructions.setOutlineColor(Color::Black);
	instructions.setOutlineThickness(1.5);
	FloatRect size = instructions.getLocalBounds();
	instructions.setPosition((800 - size.width) / 2, 420);
}