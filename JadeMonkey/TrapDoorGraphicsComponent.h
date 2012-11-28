#pragma once

#include "GameMap1GraphicsComponent.h"
#include "TrapDoorComponent.h"

class TrapDoorGraphicsComponent : public GameMap1GraphicsComponent
{

private:
	bool triggered;
	TrapDoorComponent *_trapDoor;

public:
	TrapDoorGraphicsComponent(int numRows, int numCols, TrapDoorComponent *trapDoor, Game* game, GameEntity* entity);
	virtual void Initialize(void) override;
	virtual void Update(GameEntity* entity, long time) override;
	virtual string GetName(void) override;
};