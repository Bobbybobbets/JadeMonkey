#pragma once

#include "TexturedGraphicsComponent.h"

class GameMap2GraphicsComponent : public TexturedGraphicsComponent
{
	int height;
	int color;
public:
	GameMap2GraphicsComponent(int numRows, int numCols, Game* game, GameEntity* entity, int color, D3DXVECTOR3 normal);
	GameMap2GraphicsComponent(int numRows, int numCols, Game* game, GameEntity* entity, int color, D3DXVECTOR3 normal, string texturePath);
	int getHeight();

protected:
	virtual void loadMesh(void) override;
	virtual void loadTexture(void) override;
	virtual void setupRender(void) override;
	D3DXVECTOR3 _normal;
	string _texturePath;
	string hopefully;
};