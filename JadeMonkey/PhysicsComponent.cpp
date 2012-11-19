#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(Game* game, GameEntity* entity)
	: BEntityComponent(game, entity)
{
	this->_velocity = D3DXVECTOR3(0.0, 0.0, 0.0);
	this->_acceleration = D3DXVECTOR3(0.0, 0.0, 0.0);
	onGround = false;
}

void PhysicsComponent::Initialize(void)
{
	this->_acceleration += D3DXVECTOR3(0.0f, -1.0f, 0.0f);
}

void PhysicsComponent::Update(GameEntity* entity, long time)
{
	if( !_game->checkFloorCollisions(this->_entity->getPosition(), this->_entity->getPosition() + this->_acceleration))
	{
		if( onGround == true && this->_acceleration.y < 0)
		{
			this->_acceleration = D3DXVECTOR3(0.0,-1.0,0.0); // And set a new acceleration vector to be just starting to fall
		}
		this->_entity->setPosition(this->_entity->getPosition() + this->_acceleration);
		onGround = false; 	//Set it to be not on the ground

	}
	else
	{
		onGround = true;
		// If the object WAS on the ground and the acceleration of y is negative (didn't jump)

	}

	if(this->_acceleration.y > 0)
	{
		this->_acceleration.y--;
		if( this->_acceleration.y <= 0)
			this->_acceleration = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	}
	else if( this->_acceleration.y < 0)
	{
		this->_acceleration.y--;
	}
}


bool PhysicsComponent::getOnGround()
{
	return this->onGround;
}

void PhysicsComponent::setAccelerationVector(D3DXVECTOR3 newAcc)
{
	this->_acceleration = newAcc;
}

void PhysicsComponent::setVelocityVector(D3DXVECTOR3 newVel)
{
	this->_velocity = newVel;
}

D3DXVECTOR3 PhysicsComponent::getAccelerationVector()
{
	return this->_acceleration;
}

D3DXVECTOR3 PhysicsComponent::getVelocityVector()
{
	return this->_velocity;
}