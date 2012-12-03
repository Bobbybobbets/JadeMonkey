#pragma once
#include "GameEntity.h"
#include <vector>

using namespace std;

struct AIEntitiesInteractionContainer
{
	GameEntity* Player;
	GameEntity* Boss;
	vector<GameEntity*> Friendly;

public:
	AIEntitiesInteractionContainer(GameEntity* player, GameEntity* boss, vector<GameEntity*> friendly)
	{
		this->Player = player;
		this->Boss = boss;
		this->Friendly = friendly;
	}
};