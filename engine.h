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
		Engine(int, int); // konstruktor przyjmuj¹cy szerokoœæ i wysokoœæ okna 
		void start(); // funkcja uruchamiaj¹ca g³ówny gameloop 
};

	Engine::Engine(int height, int weight)
		:myManager(windowPtr)
	{
		myWindow.create(VideoMode(height, weight), "myWindow"); // przypisanie wymiarów i utworzenie gry 
		myWindow.setFramerateLimit(15); // ustawienie limitu wyswietlanych klatek na sekundê
		Image icon; // utowrzenie obiektu icon
		icon.loadFromFile("LittleAdventure.png"); // ³aduje do utworzonego obiektu obraz ikony 
		myWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // przypisuje o
		myWindow.setTitle("Little Adventure");
	}

	void Engine::start()
	{
		Vector2i localPosition;

		// dopóki okno jest otwarte zbiera zdarzenia 
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


