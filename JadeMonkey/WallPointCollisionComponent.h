#pragma once

#include "PointCollisionComponent.h"

class WallPointCollisionComponent : public PointCollisionComponent
{
public:
	WallPointCollisionComponent(Game* game, GameEntity* entity);
	~WallPointCollisionComponent();

	virtual bool checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end);
	virtual void LoadContent(void){};
	virtual void Update(void){};
	virtual void Initialize(void) override;
	virtual string GetName();
};