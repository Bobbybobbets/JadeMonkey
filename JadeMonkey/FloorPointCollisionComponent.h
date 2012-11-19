#pragma once

#include "PointCollisionComponent.h"

class FloorPointCollisionComponent : public PointCollisionComponent
{
public:
	FloorPointCollisionComponent(Game* game, GameEntity* entity);
	~FloorPointCollisionComponent();

	virtual bool checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end);
	virtual void LoadContent(void){};
	virtual void Update(void){};
	virtual void Initialize(void) override;
	virtual string GetName();
};