#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

//lokalne
#include "SystemManager.h"

using namespace std;
using namespace sf;

class Engine
{
	private:
		RenderWindow myWindow; // okno gry
		RenderWindow* windowPtr = &myWindow; // wskaznik na okno gry

		SystemManager myManager; 
	public:
		Engine(int, int); // konstruktor przyjmuj�cy szeroko�� i wysoko�� okna 
		void start(); // funkcja uruchamiaj�ca g��wny gameloop 
};

	Engine::Engine(int height, int weight)
		:myManager(windowPtr)
	{
		myWindow.create(VideoMode(height, weight), "myWindow"); // przypisanie wymiar�w i utworzenie gry 
		myWindow.setFramerateLimit(15); // ustawienie limitu wyswietlanych klatek na sekund�
		Image icon; // utowrzenie obiektu icon
		icon.loadFromFile("LittleAdventure.png"); // �aduje do utworzonego obiektu obraz ikony 
		myWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // przypisuje o
		myWindow.setTitle("Little Adventure");
	}

	void Engine::start()
	{
		Vector2i localPosition;

		// dop�ki okno jest otwarte zbiera zdarzenia 
		while (myWindow.isOpen())
		{
			bool isClicked = false;

			Event event;

			while (myWindow.pollEvent(event))
			{
				switch (event.type)
				{
					case Event::Closed:
					{
						myWindow.close();
						break;
					}
					case Event::MouseMoved:
					{
						localPosition = Mouse::getPosition(myWindow);
						break;
					}
					case Event::MouseButtonPressed:
					{
						if (event.mouseButton.button == Mouse::Left)
						{
							localPosition = Mouse::getPosition(myWindow);
							isClicked = true;
						}
					}
				}
			}
			myManager.update(localPosition, isClicked);
			myManager.draw();
		}
	}


