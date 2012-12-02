#pragma once

#include "PointCollisionComponent.h"
#include "PlayerComponent.h"

class WallPointCollisionComponent : public PointCollisionComponent
{
public:
	WallPointCollisionComponent(Game* game, GameEntity* entity);
	~WallPointCollisionComponent();

	virtual D3DXVECTOR3 checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end, GameEntity* entity);
	virtual void LoadContent(void){};
	virtual void Update(void){};
	virtual void Initialize(void) override;
	virtual string GetName();
};