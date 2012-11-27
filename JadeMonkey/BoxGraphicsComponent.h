#pragma once
#include "GraphicsComponent.h"

class BoxGraphicsComponent : public GraphicsComponent
{
public:
	BoxGraphicsComponent(Game* game, GameEntity* entity, D3DCOLOR color);
	virtual void Initialize(void) override;
	virtual void Update(GameEntity* entity, long time) override;
	virtual string GetName() override;

private:
	D3DCOLOR _color;
};