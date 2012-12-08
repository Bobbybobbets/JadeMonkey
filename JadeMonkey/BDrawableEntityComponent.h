#pragma once
#include "BEntityComponent.h"

class BDrawableEntityComponent : public BEntityComponent
{
public:
	BDrawableEntityComponent(Game* game, GameEntity* entity):BEntityComponent(game, entity){}
	virtual void Draw(long time) = 0;
};