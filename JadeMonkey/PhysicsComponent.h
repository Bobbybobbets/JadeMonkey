#pragma once

#include "BEntityComponent.h"
#include "GameEntity.h"

class PhysicsComponent : public BEntityComponent
{
public:
	PhysicsComponent(Game* game, GameEntity* entity);
	void Initialize(void) override;
	void Update(GameEntity* entity, long time) override;

	void setAccelerationVector( D3DXVECTOR3 newAcc);
	void setVelocityVector(D3DXVECTOR3 newVel);
	D3DXVECTOR3 getAccelerationVector();
	D3DXVECTOR3 getVelocityVector();

	bool getOnGround();

private:
	D3DXVECTOR3 _velocity;
	D3DXVECTOR3 _acceleration;
	bool onGround;
};