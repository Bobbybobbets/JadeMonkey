#pragma once
#include <vector>
#include "CameraComponent.h"

struct GameEntitiesContainer
{
	vector<CameraComponent*> Cameras;
	vector<GameEntity*> Entities;
	vector<GameEntity*> Walls;
	vector<GameEntity*> Floors;
};