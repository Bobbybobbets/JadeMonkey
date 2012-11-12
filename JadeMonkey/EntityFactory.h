#pragma once
#include "Game.h"
#include "GameEntity.h"
#include "GameEntitiesContainer.h"

class EntityFactory
{
public:
	EntityFactory(Game* game);
	virtual GameEntitiesContainer GetContainer();

protected:
	Game* _game;
};