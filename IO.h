#pragma once
#ifndef _IO_
#define _IO_


#include <SFML\Graphics.hpp>

#endif

class IO
{
public:
	IO(void);
	~IO(void);

	sf::RenderWindow window;
	sf::RectangleShape rectangle;

	static const int WIDTH = 640;
	static const int HEIGHT = 480;

	void DrawRectangle      (int pX1, int pY1, int pX2, int pY2, sf::Color color, bool isGhost = false);
    void ClearScreen        ();
    int GetScreenHeight     ();
    int InitGraph           ();
    int Pollkey             ();
    void UpdateScreen       ();
	void DrawScore			(int pScore);
};

