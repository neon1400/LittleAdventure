#pragma once

#include "State.h"
#include "Camera.h"
#include "Walls.h"

using namespace std;

class GameState : public State
{
	private:
		RenderWindow *myWindow;
		Camera *myCamera;
		Wall *leftWall;
		Wall *rightWall;
		Wall *nextWall;
	public:
		GameState(RenderWindow*);
		void update(Vector2i);
		void draw();
};

	GameState::GameState(RenderWindow* borrowedWindow)
	{
		myWindow = borrowedWindow;
		myCamera = new Camera();
		
		leftWall = new Wall(5, 1, 10, 0, 40, 30);
		rightWall = new Wall(5, 1, 40, 15, 40, 0);
		nextWall = new Wall(20, 1 , 10, 0, 40, 30);
	}

	void GameState::update(Vector2i position)
	{
		leftWall->update(myCamera);
		rightWall->update(myCamera);
		nextWall->update(myCamera);
	}

	void GameState::draw()
	{
		myWindow->clear(Color::White);
		myWindow->draw(leftWall->wall);
		myWindow->draw(rightWall->wall);
		myWindow->draw(nextWall->wall);
		cout <<"narysowane"<<endl;
		myWindow->display();
	}
