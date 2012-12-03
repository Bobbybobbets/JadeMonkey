#pragma once
#include "GameEntity.h"
#include <vector>
#include "Enums.h"

using namespace std;

struct AIEntitiesInteractionContainer
{
	GameEntity* Player;
	GameEntity* Boss;
	vector<GameEntity*> Friendly;
	CollisionGroup Group;

public:
	AIEntitiesInteractionContainer(GameEntity* player, GameEntity* boss, vector<GameEntity*> friendly, CollisionGroup group)
	{
		this->Player = player;
		this->Boss = boss;
		this->Friendly = friendly;
		this->Group = group;
	}
};