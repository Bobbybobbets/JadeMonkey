#pragma once
#include "EntityFactory.h"

class PatTestFactory : public EntityFactory
{
public :
	PatTestFactory();
	GameEntitiesContainer GetContainer(Game* game) override;
};