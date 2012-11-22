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
	height = 15;
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