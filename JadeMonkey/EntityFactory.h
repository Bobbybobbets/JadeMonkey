#pragma once
#include "Game.h"
#include "GameEntity.h"
#include "GameEntitiesContainer.h"
#include "PlayerComponent.h"
#include "TrapDoorComponent.h"
#include "BehaviourBuilder.h"
#include <vector>
#include "AIEntitiesInteractionContainer.h"
#include "AStarPathfindingGraph.h"
#include "DoorUseComponent.h"


using namespace std;

class EntityFactory
{
public:
	EntityFactory();
	virtual GameEntitiesContainer GetContainer(Game* game);

protected:
	Game* _game;
	GameEntitiesContainer container;

	GameEntitiesContainer AddFloor(int numCols, int num, D3DXVECTOR3 position, GameEntitiesContainer gc);
	GameEntitiesContainer AddWall(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, bool xWall);
	GameEntitiesContainer AddStair(D3DXVECTOR3 position, GameEntitiesContainer gc, int width, bool xStair);
	GameEntitiesContainer AddStairs(int number, int direction, D3DXVECTOR3 position, GameEntitiesContainer gc, int width, bool xStair);
	GameEntitiesContainer AddKey(D3DXVECTOR3 position, int keyNumber, GameEntitiesContainer gc, PlayerComponent *player);
	GameEntitiesContainer CreateLevel1(GameEntitiesContainer container, PlayerComponent *player, AIEntitiesInteractionContainer aiEntitiesContainer);
	GameEntity* CreateAIEntity(GameEntitiesContainer* container, D3DXVECTOR3 position, D3DXVECTOR3 size, float speed, D3DCOLOR color, long framesToWait, Behaviour behaviour, AIEntitiesInteractionContainer entitiesContainer, AStarPathfindingGraph* graph, PlayerComponent *player);
	GameEntity* CreateAIEntity(GameEntitiesContainer* container, D3DXVECTOR3 position, D3DXVECTOR3 size, float speed, D3DCOLOR color, long framesToWait, Behaviour behaviour, AIEntitiesInteractionContainer entitiesContainer, AStarPathfindingGraph* graph, GameEntity* entityToFollow, PlayerComponent *player);
	GameEntitiesContainer AddTrapDoor( int numRows, int numCols,GameEntitiesContainer container, D3DXVECTOR3 position, PlayerComponent* player);
	GameEntitiesContainer AddWall(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, bool xWall, string texturepath);
};