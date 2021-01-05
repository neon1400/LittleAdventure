#pragma once

#include <stack>

// stany gry:
#include "MenuState.h"
#include "StatsState.h"
#include "ClassState.h"
#include "TextState.h"
#include "FightState.h"
#include "EndState.h"

using namespace std;

class StateMachine
{
	private:
		stack <State*> myStack;

	public:
		StateMachine(RenderWindow *, SysButton*); // konstruktor przyjmuj¹cy wskaznik na okno gry i przycisk systemowy 
		void insert(State *); // dodaje stan na szczyt stacka
		void release(); // zdejmuje stan ze szczytu 
		void swap(State *); // zamienia stan ze szczytu na nowy
		///////////////////
		void update(Vector2i, bool); // wykonuje metode update stanu na szczycie stacka
		void draw(); // wykonuje metode draw stanu na szczycie stacka
		bool darkenState(); // wykonuje metode darken stanu na szczycie stacka
		///////////////////
		~StateMachine();
};

	StateMachine::StateMachine(RenderWindow * borrowedWindow, SysButton * ChangeState)
	{
		State* statePtr = new MenuState(borrowedWindow, ChangeState);
	
		myStack.push(statePtr);

	}

	void StateMachine::insert(State * toAdd)
	{
		myStack.push(toAdd);
	}

	void StateMachine::release()
	{
		if(!myStack.empty())
		{
			delete myStack.top();
			myStack.pop();
		}
	}

	void StateMachine::swap(State* toSwap)
	{
		if (!myStack.empty())
		{
			delete myStack.top();
			
			myStack.pop();
			myStack.push(toSwap);
		}
	}

	void StateMachine::update(Vector2i position, bool isClicked)
	{
		if(!myStack.empty())
			myStack.top()->update(position, isClicked);
	}

	void StateMachine::draw()
	{
		if(!myStack.empty())
			myStack.top()->draw();
	}

	StateMachine::~StateMachine()
	{
		while(!myStack.empty())
		{
			delete myStack.top();
			myStack.pop();
		}
	}
	
	bool StateMachine::darkenState()
	{
		return myStack.top()->darken();
	}