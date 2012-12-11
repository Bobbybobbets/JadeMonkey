#include "PlayerComponent.h"


PlayerComponent::PlayerComponent(Game* game, GameEntity *entity): BEntityComponent(game, entity)
{
	score = 500;
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
	this->_game->setNumKeys(numKeyParts);
	this->_game->setNumLives(lives);
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

void PlayerComponent::LoseLife()
{
	if( lives > 0)
		lives --;
	if(lives <= 0)
	{
		_game->LossScreen();
	}
	else
	{
		_game->DeadScreen();
	}
}

void PlayerComponent::loseScore(int score)
{
	this->score -= score;
}

int PlayerComponent::getScore()
{
	return this->score;
}