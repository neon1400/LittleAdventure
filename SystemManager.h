#pragma once

#include <SFML/Audio.hpp>

// lokalne
#include "StateMachine.h"
#include "Hero.h"

using namespace sf;

class SystemManager
{
	private:
		StateMachine * myMachine;
	
		// przyciski
		SysButton* ChangeState;
		RenderWindow * myWindow;

		// obiekt bohatera
		Hero *myHero;

		// muzyka
		Music stateMusic;
		bool fuse;

	public:
		SystemManager(RenderWindow *);
		void update(Vector2i, bool);
		void draw();
		
};
	
	SystemManager::SystemManager(RenderWindow * borrowedWindow)
	{
		// tworzy maszynê stanów odpowiedzialn¹ za aktualnie wyœwietlane obiekty na ekranie
		ChangeState = new SysButton(100, 350, 200, 100, "Graj", 2);
		myMachine = new StateMachine(borrowedWindow, ChangeState);
		myWindow = borrowedWindow;

		// w³¹czanie muzyki
		stateMusic.setLoop(true);
		stateMusic.openFromFile("Sounds/menu-music.wav");
		stateMusic.play();
		fuse = true;
	}

	void SystemManager::update(Vector2i position, bool isClicked)
	{
		myMachine->update(position, isClicked);
		
		// w zale¿noœci od wartoœci zwróconej przez metodê update obiektu sysButton
		// wp³ywa na stan maszyny 
		/*
			jesli update ==
			1 - uruchamia menu
			2 - tworzy obiekt bohatera i uruchamia wybór statystyk
			3 - uruchamia wybór klasy 
			4 - uruchamia stan odpowiedzialny za ³adowanie tekstu
			5 - dorzuca na szczyt maszyny stanów walkê, by nie straciæ postêpu w poprzednim stanie
			6 - zrzuca stan walki i powraca do stanu ³adowania tekstu
			10 - ³aduje stan koñca gry 
		*/
		if(ChangeState->update() == 1)
		{
			if (fuse)
			{
				stateMusic.openFromFile("Sounds/menu-music.wav");
				stateMusic.play();
				fuse = false;
			}
			if(myMachine->darkenState())
			{
				delete ChangeState;
				ChangeState = new SysButton(100, 350, 200, 100, "Graj", 2);
				State* tempState = new MenuState(myWindow, ChangeState);
				myMachine->swap(tempState);
				fuse = true;
			}
		}
		else if (ChangeState->update() == 2)
		{
			if(myMachine->darkenState())
			{
				myHero = new Hero();
				delete ChangeState;
				ChangeState = new SysButton(600, 490, 200, 100, "Tak", 3, 0.75);
				State* tempState = new StatsState(myWindow, myHero, ChangeState);
				myMachine->swap(tempState);
			}
		}
		else if (ChangeState->update() == 3)
		{
			if (myMachine->darkenState())
			{
				delete ChangeState;
				ChangeState = new SysButton(0, 0, 1, 1, "", 4);
				State* tempState = new ClassState(myWindow, myHero, ChangeState);
				myMachine->swap(tempState);
			}
		}
		else if (ChangeState->update() == 4)
		{
			if (myMachine->darkenState())
			{
				delete ChangeState;
				ChangeState = new SysButton(0, 0, 1, 1, "", 5);
				State* tempState = new TextState(myWindow, myHero, ChangeState);
				myMachine->swap(tempState);
			}
		}
		else if (ChangeState->update() == 5)
		{
			if(fuse)
			{
				stateMusic.openFromFile("Sounds/battle-music.wav");
				stateMusic.play();
				fuse = false;
			}

			if (myMachine->darkenState())
			{
				cout << "Walka!" << endl;
				int enemyType = ChangeState->enemyType;
				delete ChangeState;
				ChangeState = new SysButton(0, 0, 1, 1, "", 6);
				State* tempState = new FightState(myWindow, myHero, ChangeState, enemyType);
				myMachine->insert(tempState);
				fuse = true;
			}	
		}
		else if(ChangeState->update() == 6)
		{
			if(fuse)
			{
				if(myHero->getHP() <= 0 )
				{
					stateMusic.openFromFile("Sounds/death-sound.wav");
				}
				else
				{
					stateMusic.openFromFile("Sounds/menu-music.wav");
				}
				stateMusic.play();
				fuse = false;
			}

			if (myMachine->darkenState())
			{
				delete ChangeState;
				fuse = true;

				if(myHero->getHP() <= 0 )
				{
					ChangeState = new SysButton(100, 400, 200, 100, "Menu", 1);
					State* tempState = new EndState(myWindow, myHero, ChangeState);
					myMachine->release();
					myMachine->swap(tempState);
				}
				else
				{
					ChangeState = new SysButton(0, 0, 1, 1, "", 5);
					myMachine->release();
				}
			}
		}
		else if(ChangeState->update() == 10)
		{
			if(myMachine->darkenState())
			{
				cout << "koniec gry" << endl;
				ChangeState = new SysButton(100, 400, 200, 100, "Menu", 1);
				State* tempState = new EndState(myWindow, myHero, ChangeState);
				myMachine->swap(tempState);
			}
		}
	}

	void SystemManager::draw()
	{
		myMachine->draw();
	}