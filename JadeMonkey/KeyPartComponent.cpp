#include "KeyPartComponent.h"
#include <math.h>

float KeyPartComponent::pickupDistance = 20.0;

KeyPartComponent::KeyPartComponent( Game *game, GameEntity *entity, int keyNumber, D3DXVECTOR3 position) : BEntityComponent(game, entity)
{
	this->keyNumber = keyNumber;
	this->_position = position;
}

void KeyPartComponent::Initialize(void)
{
	retrieved = false;
}
bool KeyPartComponent::checkPickup( D3DXVECTOR3 toCheck)
{
	float distance;
	distance = pow((_position.x - toCheck.x), 2) + pow((_position.y - toCheck.y), 2) + pow((_position.z + toCheck.z), 2);
	distance = sqrt(distance);

	if( distance <  pickupDistance)
	{
		retrieved = true;
		return true;
	}
	return false;
}

bool KeyPartComponent::getRetrieved()
{
	return retrieved;
}