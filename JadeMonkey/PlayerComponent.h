#pragma once

#include "BEntityComponent.h"
#include "Game.h"
#include "GameEntity.h"


class PlayerComponent: public BEntityComponent
{
private:
	int lives;
	int stepHeight;
	int currentLevel;
	int height; 
	int numKeyParts;

public:
	PlayerComponent(Game* game, GameEntity* entity);
	~PlayerComponent();

	virtual void Initialize(void) override;
	virtual void Update(GameEntity* entity, long time) override;

	int getLives();
	int getStepHeight();
	int getCurrentLevel();
	void setLives(int);
	void setCurrentLevel(int);
	int getHeight();
	int getNumKeyParts();
	void setNumKeyParts(int numKeys);
	void FoundKey();
	void LoseLife();

};