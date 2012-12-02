#pragma once
#include "Game.h"
#include "GameEntity.h"
#include "GameEntitiesContainer.h"
#include "PlayerComponent.h"

class EntityFactory
{
public:
	EntityFactory();
	virtual GameEntitiesContainer GetContainer(Game* game);

protected:
	Game* _game;

	GameEntitiesContainer AddFloor(int numCols, int num, D3DXVECTOR3 position, GameEntitiesContainer gc);
	GameEntitiesContainer AddWall(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, bool xWall);
	GameEntitiesContainer AddStair(D3DXVECTOR3 position, GameEntitiesContainer gc, int width, bool xStair);
	GameEntitiesContainer AddStairs(int number, int direction, D3DXVECTOR3 position, GameEntitiesContainer gc, int width, bool xStair);
	GameEntitiesContainer AddKey(D3DXVECTOR3 position, int keyNumber, GameEntitiesContainer gc, PlayerComponent *player);
	GameEntitiesContainer CreateLevel1(GameEntitiesContainer container, PlayerComponent *player);
	GameEntity* CreateAIEntity(GameEntitiesContainer* container, D3DXVECTOR3 position, D3DXVECTOR3 size, D3DCOLOR color, long framesToWait);
	GameEntity* CreateAIEntity(GameEntitiesContainer* container, D3DXVECTOR3 position, D3DXVECTOR3 size, D3DCOLOR color, long framesToWait, GameEntity* entityToFollow);
};