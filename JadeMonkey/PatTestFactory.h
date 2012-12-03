#pragma once
#include "EntityFactory.h"
#include "GameEntitiesContainer.h"
#include "Game.h"


class PatTestFactory : public EntityFactory
{
private:
	DoorUseComponent* AddDoor(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *player, bool xWall, CameraComponent *camera);
public:
	PatTestFactory();
	GameEntitiesContainer GetContainer(Game* game);
};