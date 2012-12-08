#pragma once

#include "TexturedGraphicsComponent.h"

class GameMap2GraphicsComponent : public TexturedGraphicsComponent
{
	int height;
	int color;
public:
	GameMap2GraphicsComponent(int numRows, int numCols, Game* game, GameEntity* entity, int color);
	int getHeight();

protected:
	virtual void loadMesh(void) override;
	virtual void loadTexture(void) override;
	virtual void setupRender(void) override;
};