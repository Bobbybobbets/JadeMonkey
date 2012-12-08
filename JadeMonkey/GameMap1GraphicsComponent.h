#pragma once

#include "TexturedGraphicsComponent.h"

class GameMap1GraphicsComponent : public TexturedGraphicsComponent
{
public:
	GameMap1GraphicsComponent(int numRows, int numCols, Game* game, GameEntity* entity);
	
protected:
	virtual void loadMesh(void) override;
	virtual void loadTexture(void) override;
	virtual void setupRender(void) override;
};