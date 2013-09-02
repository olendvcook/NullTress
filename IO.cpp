#include "IO.h"

IO::IO(void)
{
	InitGraph ();
}


IO::~IO(void)
{
}

void IO::ClearScreen() 
{
	window.clear();
	//boxColor (mScreen, 0, 0, mScreen->w - 1, mScreen->h - 1, mColors[BLACK]);
}

void IO::DrawRectangle (int pX1, int pY1, int pX2, int pY2, sf::Color color, bool isGhost)
{
	rectangle.setPosition(pX1,pY1);
	rectangle.setSize(sf::Vector2f(pX2,pY2));
	rectangle.setFillColor(color);
	if(isGhost)
	{
		rectangle.setOutlineColor(sf::Color::White);
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setOutlineThickness(1);
		window.draw(rectangle);
		return;
	}
	else 
	{
		rectangle.setOutlineThickness(0);
		window.draw(rectangle);
	}

}

int IO::GetScreenHeight()
{
	return HEIGHT;
}

void IO::UpdateScreen()
{
	window.display();
	//SDL_Flip(mScreen);
}

int IO::Pollkey()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch(event.type) {
		case sf::Event::KeyPressed:
			return event.key.code;
		case sf::Event::Closed:
			exit(3);
		}
	}
	return -1;
	/*
	SDL_Event event;
	while ( SDL_PollEvent(&event) ) 
	{
		switch (event.type) {
			case SDL_KEYDOWN:
				return event.key.keysym.sym;
			case SDL_QUIT:
				exit(3);
		}
	}
	return -1;
	*/

}

int IO::Getkey()
{
	/*
	SDL_Event event;
	while (true)
	{
	  SDL_WaitEvent(&event);
	  if (event.type == SDL_KEYDOWN)
		  break;
      if (event.type == SDL_QUIT)
		  exit(3);
	};
	return event.key.keysym.sym;
	*/
	return 0;
}

/* 
======================================									
Keyboard Input
====================================== 
*/
int IO::IsKeyDown (int pKey)
{
	/*
	Uint8* mKeytable;
	int mNumkeys;
	SDL_PumpEvents();
	mKeytable = SDL_GetKeyState(&mNumkeys);
	return mKeytable[pKey];
	*/
	return 0;
}

int IO::InitGraph()
{	
	window.create(sf::VideoMode(WIDTH, HEIGHT), "NULLtress");
	return 0;
}

void IO::DrawScore(int pScore)
{
	
	sf::Font font;
	font.loadFromFile("font.ttf");

	sf::Text text("Number of Lines Cleared:", font);
	sf::Text tScore;
	//text.setString("Number of Lines Cleared:");
	text.setPosition(20,50);
	text.setColor(sf::Color::White);
	text.setCharacterSize(10);



	std::string s = std::to_string(pScore);
	tScore.setString(s);
	tScore.setPosition(50,70);
	tScore.setFont(font);
	tScore.setColor(sf::Color::Cyan);
	tScore.setCharacterSize(12);
		

	window.draw(text);
	window.draw(tScore);
		
}