#include "ParticleEngine.h"

float RandomFloat(float pA, float pB);
int RandomInt (int pA, int pB);

ParticleEngine::ParticleEngine(void)
{
}

ParticleEngine::ParticleEngine(sf::Vector2f pLocation, int pCount) :
	mEmitterLocation(pLocation),
	mParticles(pCount)
{
	srand ((unsigned int) time(NULL));
	Refill(pCount);
}

ParticleEngine::~ParticleEngine(void)
{
}

void ParticleEngine::Refill(int pCount)
{
	mParticles.resize(pCount);
	for(int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i] = GenerateNewParticle();
	}
}

void ParticleEngine::Clear()
{
	mParticles.clear();
}

Particle ParticleEngine::GenerateNewParticle(float xMin, float xMax, 
											 float yMin, float yMax, 
											 float TTLmin, float TTLmax, 
											 int sizeMin, int sizeMax, float pAngle,
											 float pAngularvelocity, sf::Color pColor)
{
	sf::Vector2f position = mEmitterLocation;
	sf::Vector2f velocity(RandomFloat(xMin,xMax),RandomFloat(yMin,yMax));
	float angle = pAngle;
	float angularVelocity = pAngularvelocity; //0.1f * RandomFloat(-1,1);
	sf::Color color;
	if( pColor == sf::Color::Black)
	{
		color = sf::Color(RandomInt(0,255),
								RandomInt(0,255),
								RandomInt(0,255));
	}
	else
	{
		color = pColor;
	}
	int size = RandomInt(sizeMin,sizeMax);
	int ttl = RandomInt(TTLmin,TTLmax);

	return Particle(position, velocity, angle, angularVelocity, ttl, size, color);
}

void ParticleEngine::Update(float gravity, bool kill)
{
	std::vector<Particle>::iterator it = mParticles.begin();

	for (int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].Update();
		mParticles[i].mVelocity.y += gravity;
		if (mParticles[i].mTTL <= 0)
		{
			if (kill) 
			{
				mParticles.erase(mParticles.begin() + i);
			}
			else
			{
				mParticles[i] = GenerateNewParticle();
			}
		}
	}
}

void ParticleEngine::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].Draw(window);
	}
}

float RandomFloat(float pA, float pB) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = pB - pA;
    float r = random * diff;
    return pA + r;
}

int RandomInt (int pA, int pB)
{
    return pA + (rand() % (int)(pB - pA + 1));
}
