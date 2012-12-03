#pragma once

#include "BEntityComponent.h"
#include "PlayerComponent.h"

class DoorComponent: public BEntityComponent 
{
private:
	int numberOfKeys;
	PlayerComponent *player;

public:
	DoorComponent(Game* game, GameEntity *entity, int numKeys);
	~DoorComponent();


	int getNumKeys();
	void setNumKeys(int numKeys);









};