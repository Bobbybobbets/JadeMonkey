#include "DoorComponent.h"


DoorComponent::DoorComponent(Game* game, GameEntity* entity, int numKeys): BEntityComponent(game, entity)
{
	this->numberOfKeys = numKeys;
}

int DoorComponent::getNumKeys()
{
	return this->numberOfKeys;
}

void DoorComponent::setNumKeys(int numKeys)
{
	this->numberOfKeys = numKeys;
}