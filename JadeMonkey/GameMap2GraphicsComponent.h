#pragma once

#include "GraphicsComponent.h"

class GameMap2GraphicsComponent : public GraphicsComponent
{
	int height;
	int color;
public:
	GameMap2GraphicsComponent(int numRows, int numCols, Game* game, GameEntity* entity, int color);
	virtual void Initialize(void) override;
	virtual void Update(GameEntity* entity, long time) override;
	virtual string GetName(void) override;

	int getHeight();
};