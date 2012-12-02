#pragma once
#include "PointCollisionComponent.h"

class WallPointXCollisionComponent : public PointCollisionComponent
{
public:
	WallPointXCollisionComponent(Game* game, GameEntity* entity);
	~WallPointXCollisionComponent();

	virtual D3DXVECTOR3 checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end, GameEntity* entity);
	virtual void LoadContent(void){};
	virtual void Update(void){};
	virtual void Initialize(void) override;
	virtual string GetName();
};