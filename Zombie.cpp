#include "zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>
#include "Player.h"


using namespace std;


void Zombie::spawn(float startX, float startY, int type, int seed)
{

	switch (type)
	{
	case 0:
		// Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/bloater.png"));

		m_Speed = 40;
		m_Health = 5.5;
		break;

	case 1:
		// Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/chaser.png"));

		m_Speed = 80;
		m_Health = 3;
		break;

	case 2:
		// Crawler
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/crawler.png"));

		m_Speed = 20;
		m_Health = 3;
		break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	srand((int)time(0) * seed);
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	m_Speed *= modifier;

	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

bool Zombie::hit(float damage)
{
	m_Health -= damage;

	if (m_Health < 0)
	{
		// dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics/blood.png"));

		return true;
	}

	// Injured but not dead yet
	if (getType() == 1)  // Check if it's a Chaser zombie
	{
		// Set a flag to make the Chaser zombie turn around
		m_TurnAroundTime = sf::seconds(0.5f);
	}

	// injured but not dead yet
	return false;
}

bool Zombie::isAlive()
{
	return m_Alive;
}

FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}


Sprite Zombie::getSprite()
{
	return m_Sprite;
}

void Zombie::increaseSpeed(float speedIncrease) {
	// Increase the crawler zombie's speed
	m_Speed += speedIncrease;
}



void Zombie::update(float elapsedTime,
	Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// Update the zombie position variables
	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x +
			m_Speed * elapsedTime;
	}

	if (playerY > m_Position.y)
	{
		m_Position.y = m_Position.y +
			m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x -
			m_Speed * elapsedTime;
	}

	if (playerY < m_Position.y)
	{
		m_Position.y = m_Position.y -
			m_Speed * elapsedTime;
	}



	// Move the sprite
	m_Sprite.setPosition(m_Position);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180) / 3.141;

	m_Sprite.setRotation(angle);

	if (m_TurnAroundTime > sf::Time::Zero)
	{
		// Reduce the turn-around time
		m_TurnAroundTime -= sf::seconds(elapsedTime);

		// Move away from the player
		m_Position.x -= m_Speed * elapsedTime;
		m_Position.y -= m_Speed * elapsedTime;

		// Move the sprite
		m_Sprite.setPosition(m_Position);

		return;  // Exit early, don't update the regular behavior
	}



}