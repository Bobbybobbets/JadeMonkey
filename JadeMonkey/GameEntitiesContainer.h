#pragma once
#include <vector>
#include "CameraComponent.h"
#include "PlayerComponent.h"

struct GameEntitiesContainer
{
	vector<CameraComponent*> Cameras;
	PlayerComponent* MainCharacter;
	vector<GameEntity*> Entities;
	vector<GameEntity*> Walls;
	vector<GameEntity*> Floors;
	vector<GameEntity*> EntitiesToAdd;
	vector<GameEntity*> EntitiesToRemove;
};