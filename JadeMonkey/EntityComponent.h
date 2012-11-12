#pragma once
#include "Game.h"
#include <string>

using namespace std;

class GameEntity;

class EntityComponent
{
public:
	EntityComponent(Game* game, GameEntity* entity);
	virtual void Initialize(void);
	virtual void Update(GameEntity* entity, long time);
	virtual string GetName(void);
protected:
	Game* _game;
	GameEntity* _entity;
};