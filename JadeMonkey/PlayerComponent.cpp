#include "PlayerComponent.h"


PlayerComponent::PlayerComponent(Game* game, GameEntity *entity): BEntityComponent(game, entity)
{

}

PlayerComponent::~PlayerComponent()
{

}

void PlayerComponent::Initialize()
{
	lives = 3;
	stepHeight = 20;
	currentLevel = 1;
	height = 40;
	numKeyParts = 0;
}

void PlayerComponent::Update(GameEntity* entity, long time)
{

}
int PlayerComponent::getLives()
{
	return lives;
}

int PlayerComponent::getStepHeight()
{
	return stepHeight;
}

int PlayerComponent::getCurrentLevel()
{
	return currentLevel;
}

void PlayerComponent::setLives(int lives)
{
	this->lives = lives;
}
void PlayerComponent::setCurrentLevel(int newCurLevel)
{
	this->currentLevel = newCurLevel;
}

int PlayerComponent::getHeight()
{
	return height;
}


int PlayerComponent::getNumKeyParts()
{
	return numKeyParts;
}

void PlayerComponent::setNumKeyParts(int numKeyParts)
{
	this->numKeyParts = numKeyParts;
}

void PlayerComponent::FoundKey()
{
	this->numKeyParts++;
}