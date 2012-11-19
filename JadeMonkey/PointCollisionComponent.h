#pragma once

#include "CollisionComponent.h"
class PointCollisionComponent : public CollisionComponent
{

public:
	PointCollisionComponent(Game *game, GameEntity* gameEntity);
	~PointCollisionComponent();

	virtual bool checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end) = 0;
	virtual void Initialize(void){};
	virtual void Update(GameEntity* entity, long time){};
	virtual string GetName(void);

protected:
	D3DXVECTOR3 _position;
	int width;
	int height;
	int length;



};