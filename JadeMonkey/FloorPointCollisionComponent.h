#pragma once

#include "PointCollisionComponent.h"

class FloorPointCollisionComponent : public PointCollisionComponent
{
public:
	FloorPointCollisionComponent(Game* game, GameEntity* entityc);
	~FloorPointCollisionComponent();

	virtual D3DXVECTOR3 checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end, GameEntity* entity);
	virtual void LoadContent(void){};
	virtual void Update(void){};
	virtual void Initialize(void) override;
	virtual string GetName();
};