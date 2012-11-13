#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(Game* game, GameEntity* entity)
	: BEntityComponent(game, entity)
{
	this->_velocity = D3DXVECTOR3(0.0, 0.0, 0.0);
	this->_acceleration = D3DXVECTOR3(0.0, 0.0, 0.0);
}

void PhysicsComponent::Initialize(void)
{
	this->_acceleration += D3DXVECTOR3(0.0f, -1.0f, 0.0f);
}

void PhysicsComponent::Update(GameEntity* entity, long time)
{
	this->_entity->setPosition(this->_entity->getPosition() + this->_acceleration);
}