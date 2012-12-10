#pragma once
#include "TexturedGraphicsComponent.h"

class BillboardDisplayComponent : public TexturedGraphicsComponent
{
public:
	BillboardDisplayComponent(Game* game, GameEntity* entity, GameEntity* player);

protected:
	GameEntity* _player;

	virtual void setupRender(void) override;
	virtual void loadMesh(void) = 0;
	virtual void loadTexture(void) = 0;
};