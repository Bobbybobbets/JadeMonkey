#include "TrapDoorComponent.h"

TrapDoorComponent::TrapDoorComponent(Game *game, GameEntity* entity) : BEntityComponent(game,entity)
{
	triggered = false;
}

bool TrapDoorComponent::getTriggered()
{
	return this->triggered;
}

void TrapDoorComponent::setTriggered(bool triggered)
{
	this->triggered = triggered;
}