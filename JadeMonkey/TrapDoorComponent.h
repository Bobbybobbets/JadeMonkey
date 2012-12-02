#pragma once

#include "BEntityComponent.h"

class TrapDoorComponent: public BEntityComponent
{
private:
	bool triggered;

public:
	TrapDoorComponent(Game *game, GameEntity* entity);
	~TrapDoorComponent();

	bool getTriggered();
	void setTriggered(bool triggered);
};