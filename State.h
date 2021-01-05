#pragma once

using namespace sf;

class State
{
	public:
		int counter;
		float opacity;
		RectangleShape curtain;
		bool fuse;

		State() 
		{
			// sk³adniki potrzebne do wykonywania metod darken i brighten 
			counter = 30;
			opacity = 255;
			curtain.setPosition(0, 0);
			curtain.setSize(Vector2f(800.0f, 600.0f));
			curtain.setFillColor(Color(0, 0, 0, opacity));
			fuse == false;
		}


		virtual ~State() {std::cout << "usuwa state" << std::endl;};
		virtual void update(Vector2i, bool) {}
		virtual void draw() {}

		virtual bool darken(); // metoda odpowiedzialna za œciemnianie ekranu w przeci¹gu 2 sekund
		virtual bool brighten(); // metoda odpowiedzialna za rozjaœnianie ekranu w przeci¹gu 2 sekund 
};


bool State::darken()
{
	if (counter == 0)
	{
		counter = 30;
		fuse = false;
		return true;
	}
	else
	{
		opacity += 8.5;
		curtain.setFillColor(Color(0, 0, 0, opacity));
		counter--;
	}
	return false;
}

bool State::brighten()
{
	if (fuse) return true;

	if (counter == 0)
	{
		fuse = true;
		counter = 30;
		return true;
	}
	else
	{
		opacity -= 8.5;
		curtain.setFillColor(Color(0, 0, 0, opacity));
		counter--;
	}
	return false;
}
