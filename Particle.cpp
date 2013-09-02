#include "Particle.h"

Particle::Particle()
{
}

Particle::Particle(sf::Vector2f pPosition, sf::Vector2f pVelocity, float pAngle, float pAngularVelocity, int pTTL, float pSize, sf::Color pColor) :
	mPosition(pPosition),
	mVelocity(pVelocity),
	mAngle(pAngle),
	mAngularVelocity(pAngularVelocity),
	mTTL(pTTL),
	mSize(pSize),
	mColor(pColor)
{
}


Particle::~Particle(void)
{
}

void Particle::Update()
{
	mTTL--;
	mPosition += mVelocity;
	mAngle += mAngularVelocity;
}

void Particle::Draw(sf::RenderWindow* pWindow)
{
	//TODO SFML DRAW SHIT
	mRectangle.setPosition(mPosition);
	mRectangle.setSize(sf::Vector2f(mSize,mSize));
	mRectangle.setFillColor(mColor);
	pWindow->draw(mRectangle);
}