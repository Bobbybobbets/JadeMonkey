#pragma once

#include "PointCollisionComponent.h"
#include "TrapDoorComponent.h"

class TrapDoorCollisionComponent : public PointCollisionComponent
{
private:
	TrapDoorComponent *_trapDoor;
public:
	TrapDoorCollisionComponent(Game* game, GameEntity* entity, PlayerComponent *pc, TrapDoorComponent *trapDoor);
	~TrapDoorCollisionComponent();

	virtual D3DXVECTOR3 checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end);
	virtual void LoadContent(void){};
	virtual void Update(void){};
	virtual void Initialize(void) override;
	virtual string GetName();
};