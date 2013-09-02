#pragma once

#include "Particle.h"
class ParticleEngine
{
public:


	ParticleEngine(void);
	ParticleEngine(sf::Vector2f pLocation, int pCount);
	~ParticleEngine(void);
	void Update(float gravity = 0.2, bool kill = true);
	void Draw(sf::RenderWindow* window);
	void Refill(int pCount);
	void Clear();

	sf::Vector2f mEmitterLocation;

private:

	std::vector<Particle> mParticles;
	Particle GenerateNewParticle(float xMin = -2, float xMax = 2, 
											 float yMin = -30, float yMax = -1, 
											 float TTLmin = 1000, float TTLmax = 20000, 
											 int sizeMin = 20, int sizeMax = 50, float pAngle = 0,
											 float pAngularvelocity = 0, sf::Color pColor = sf::Color::Black);
};

