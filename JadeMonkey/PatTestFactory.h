#pragma once
#include "EntityFactory.h"
#include "GameEntitiesContainer.h"
#include "Game.h"


class PatTestFactory : public EntityFactory
{
public:
	PatTestFactory();
	GameEntitiesContainer GetContainer(Game* game);
};