#pragma once
#include "BEntityComponent.h"
#include "GameEntity.h"

class CollisionComponent : public BEntityComponent
{
public:
	CollisionComponent(Game* game, GameEntity* entity) : BEntityComponent(game, entity){}
	virtual void Initialize(void) override = 0;
	virtual void Update(GameEntity* entity, long time) override = 0;
	virtual string GetName(void) override = 0;
	virtual D3DXVECTOR3 checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end, GameEntity* entity){return D3DXVECTOR3(0,0,0);};
};