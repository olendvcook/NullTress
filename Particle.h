#pragma once

#include <SFML/Graphics.hpp>


class Particle
{
public:

	sf::Vector2f mPosition;
	sf::Vector2f mVelocity;
	sf::RectangleShape mRectangle;
	float mAngle;
	float mAngularVelocity;
	sf::Color mColor;
	float mSize;
	int mTTL;

	Particle();
	Particle(sf::Vector2f pPosition, sf::Vector2f pVelocity, float pAngle, float pAngularVelocity, int pTTL, float pSize, sf::Color pColor = sf::Color::White);
	virtual ~Particle(void);
	void Update();
	void Draw(sf::RenderWindow* pWindow);
};

