#include "KeyGraphicsComponent.h"
#include "KeyPartComponent.h"
#include "EntityFactory.h"
#include "WallPointXCollisionComponent.h"
#include "PlayerFPInputComponent.h"
#include "CameraComponent.h"
#include "GameMap1GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "GameMap2GraphicsComponent.h"
#include "CuboidCollisionComponent.h"
#include "WallPointCollisionComponent.h"
#include "FloorPointCollisionComponent.h"
#include "PhysicsComponent.h"
#include "AIControllerComponent.h"
#include "AStarPathfindingComponent.h"
#include "ScaledBoxGraphicsComponent.h"
#include "TrapDoorGraphicsComponent.h"
#include "TrapDoorCollisionComponent.h"


EntityFactory::EntityFactory(void)
{
}

GameEntitiesContainer EntityFactory::GetContainer(Game* game)
{
	GameEntitiesContainer cont;
	return cont;
}

GameEntitiesContainer EntityFactory::AddFloor(int numRows, int numCols, D3DXVECTOR3 position, GameEntitiesContainer gc)
{
	GameEntity* floor = new GameEntity(this->_game);
	GameMap1GraphicsComponent* graphics6 = new GameMap1GraphicsComponent(numRows, numCols, this->_game, floor);
	floor->AddGraphicsComponent(graphics6);
	floor->setPosition( D3DXVECTOR3(position.x*20, position.y*20, position.z*20));
	FloorPointCollisionComponent* floorCollision = new FloorPointCollisionComponent(this->_game, floor);
	floor->AddCollisionComponent(floorCollision);
	gc.Entities.push_back(floor);
	gc.Floors.push_back(floor);

	return gc;
}

GameEntitiesContainer EntityFactory::AddWall(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, bool xWall)
{
	GameEntity* wall = new GameEntity(this->_game);
	GameMap2GraphicsComponent* graphics = new GameMap2GraphicsComponent(numCols, numRows, this->_game, wall);
	wall->AddGraphicsComponent(graphics);
	wall->setPosition( D3DXVECTOR3(position.x*20, position.y*20, position.z*20));

	if( xWall )
	{
		WallPointXCollisionComponent* wallCollision = new WallPointXCollisionComponent(this->_game, wall);
		wall->AddCollisionComponent(wallCollision);
		wall->setRotation(D3DXVECTOR3(0, 90, 0));
	}
	else
	{
		WallPointCollisionComponent* wallCollision = new WallPointCollisionComponent(this->_game, wall);
		wall->AddCollisionComponent(wallCollision);
	}
	gc.Entities.push_back(wall);
	gc.Walls.push_back(wall);

	return gc;
}

/* Add in a number of specified stairs in a given direction
* 1 - positive x
* 2 - negative x
* 3 - positive z
* 4 - negative z
*/
GameEntitiesContainer EntityFactory::AddStairs(int number, int direction, D3DXVECTOR3 position, GameEntitiesContainer gc, int width, bool xStair)
{
	int x;
	for( x = 0 ; x < number ; x++)
	{
		switch( direction )
		{
		case 1:
			gc = AddWall(2, width + 1, D3DXVECTOR3(position.x + x  , position.y + x , position.z), gc, xStair);
			gc = AddFloor(width + 1, 2 , D3DXVECTOR3(position.x + x  , position.y + (x + 1) , position.z), gc);
			break;
		case 2:
			gc = AddWall( 2, width + 1, D3DXVECTOR3(position.x - x  , position.y + x  , position.z), gc, xStair);
			gc = AddFloor(width + 1, 2, D3DXVECTOR3(position.x - x , position.y + (x + 1) , position.z), gc);
			break;
		case 3:
			gc = AddWall( 2, width + 1, D3DXVECTOR3(position.x , position.y + x  , position.z + x ), gc, xStair);
			gc = AddFloor(2, width + 1, D3DXVECTOR3(position.x, position.y + (x + 1) , position.z + x ), gc);
			break;
		default:
			gc = AddWall( 2, width + 1, D3DXVECTOR3(position.x , position.y  + x , position.z - x ), gc, xStair);
			gc = AddFloor(2, width + 1, D3DXVECTOR3(position.x , position.y + (x + 1) , position.z - (x + 1) ), gc);
			break;

		}
	
	}
	return gc;
}

GameEntitiesContainer EntityFactory::AddKey(D3DXVECTOR3 position, int keyNumber, GameEntitiesContainer gc, PlayerComponent *player)
{
	D3DXVECTOR3 newPos = D3DXVECTOR3(position.x * 20, position.y * 20, position.z * 20);
	GameEntity *keyEntity = new GameEntity(this->_game);
	KeyPartComponent *keyPartComponent = new KeyPartComponent(this->_game, keyEntity, player, keyNumber, newPos);
	KeyGraphicsComponent *kg = new KeyGraphicsComponent(20,20,player, keyPartComponent, this->_game , keyEntity);
	
	keyEntity->setPosition(newPos);	
	keyEntity->AddComponent(keyPartComponent);
	keyEntity->AddGraphicsComponent(kg);

	gc.Entities.push_back(keyEntity);
	return gc;
}

GameEntitiesContainer EntityFactory::AddTrapDoor( int numRows, int numCols,GameEntitiesContainer container, D3DXVECTOR3 position, PlayerComponent* player)
{
	D3DXVECTOR3 newPos = D3DXVECTOR3(position.x * 20, position.y * 20, position.z * 20);
	GameEntity *trapEntity = new GameEntity(this->_game);
	trapEntity->setPosition(newPos);
	TrapDoorComponent* trapDoor = new TrapDoorComponent(this->_game, trapEntity);
	GameMap1GraphicsComponent* graphics6 = new GameMap1GraphicsComponent(numRows, numCols, this->_game, trapEntity);
	trapEntity->AddGraphicsComponent(graphics6);

	TrapDoorGraphicsComponent *trapDoorGraphics = new TrapDoorGraphicsComponent(numRows, numCols, trapDoor, this->_game, trapEntity);

	TrapDoorCollisionComponent *trapDoorCollisions = new TrapDoorCollisionComponent(this->_game, trapEntity, player, trapDoor);

	trapEntity->AddComponent(trapDoor);
	trapEntity->AddGraphicsComponent(trapDoorGraphics);
	trapEntity->AddCollisionComponent(trapDoorCollisions);

	container.Floors.push_back(trapEntity);
	container.Entities.push_back(trapEntity);
	
	return container;
}

GameEntitiesContainer EntityFactory::CreateLevel1(GameEntitiesContainer container, PlayerComponent *player)
{
	int height = 25;
	int width = 50;
	int length = 50;
	// Create the bounding walls and floor
	// F1
	container = AddFloor( width , length, D3DXVECTOR3(0,0,0) , container);
	// W1
	container = AddWall( height, width, D3DXVECTOR3(0,0,0), container, true);
	// W2
	container = AddWall( height,length, D3DXVECTOR3(0,0,0) , container, false);
	// W3
	container = AddWall( height,width, D3DXVECTOR3( 49, 0,0), container, true);
	// W4
	container = AddWall(height,length, D3DXVECTOR3(0,0, 49 ), container, false);
	// F2
	container = AddFloor( width,length , D3DXVECTOR3(0,24 , 0), container);
	
	// Containing walls
	// W5
	container = AddWall( height, 26, D3DXVECTOR3(3 , 0, 0) , container, true);
	// W6
	container = AddWall( (int)(height/2), 18 , D3DXVECTOR3( 3 , 0 , 25 ), container, false);
	// W7
	container = AddWall( height, 7, D3DXVECTOR3( 24  , 0 , 25 ), container, false);
	// W8
	container = AddWall( (int)(height / 2), 8 , D3DXVECTOR3( 30 , 0, 25 ), container, false);
	// W9
	container = AddWall( height, 10 , D3DXVECTOR3( 37 , 0, 25 ) , container, false);
	// W10
	container = AddWall( height, 22, D3DXVECTOR3( 46 , 0, 4 ), container, true);
	// W11
	container = AddWall( height, 26, D3DXVECTOR3( 21 , 0, 4 ),  container, false);
	// W12
	container = AddWall( height, 5, D3DXVECTOR3( 21 , 0, 0), container, true);
	// S1
	container = AddStairs( 6, 4, D3DXVECTOR3( 20 , 0 , 25 ), container, 4, false);
	// Plateau for staircase
	container = AddFloor( 5 , 5 , D3DXVECTOR3( 20  , 6 ,  16 ), container );
	// Second half of staircase
	container = AddStairs( 6, 1, D3DXVECTOR3( 24 , 6 , 16 ), container , 4, true);
	// Right  for 2nd floor
	container = AddWall( height, 10 , D3DXVECTOR3( 20 , 0 , 16 ), container, true);
	// Left stair wall
	container = AddWall( height, 6, D3DXVECTOR3( 24 , 0, 20 ), container, true);
	// W27
	container = AddWall( height, 6, D3DXVECTOR3( 30 , 0, 20 ), container, true);
	//
	container = AddWall( height, 7, D3DXVECTOR3( 24 , 0, 20 ), container, false);
	// 2nd floor at top of stairs
	container = AddFloor( 22 , 8, D3DXVECTOR3( 30  , (int)(height / 2) , 4 ), container);
	//
	container = AddWall( height, 11, D3DXVECTOR3(20 , 0, 16 ), container, false);
	// W21
	container = AddWall( (int)(height / 2) , 21 , D3DXVECTOR3( 37  , (int)(height / 2)  , 5 ), container, true);
	// W22
	container = AddWall( (int)(height / 2) , 8, D3DXVECTOR3(30  , (int)(height / 2) , 4 ), container, true);
	// W23
	container = AddWall( (int)(height / 2) , 18, D3DXVECTOR3(13  , (int)(height / 2) , 11 ), container, false);
	// W24
	container = AddWall( (int)(height / 2) , 30, D3DXVECTOR3( 13  , (int)(height / 2) , 11 ), container, true);
	// W25
	container = AddWall(( int)(height / 2), 16, D3DXVECTOR3( 20 , (int)(height / 2) , 25 ), container, true);

	// Floor for previous walls
	container = AddFloor( 6, 18 , D3DXVECTOR3( 13 , (int)(height/2)  , 11 ), container);
	container = AddFloor( 14, 8, D3DXVECTOR3( 13  , (int)(height/2)  , 16 ), container);

	// Add floor extending into main room
	container = AddFloor(8 , 2, D3DXVECTOR3( 19 , (int)(height/2) , 29 ), container);
	container = AddFloor(8 , 2, D3DXVECTOR3( 13 , (int)(height / 2) , 29 ), container);
	container = AddFloor(5 , 8, D3DXVECTOR3(13  , (int)(height / 2) , 36 ), container);

	// W26
	container = AddWall(height, 47 , D3DXVECTOR3( 0, 0, 40 ), container, false);
	// W27
	container = AddWall(height, 2, D3DXVECTOR3( 46 , 0 , 40 ), container, true);
	// W28
	container = AddWall( height, 47, D3DXVECTOR3( 0, 0, 41 ), container, false);

	return container;
}

GameEntity* EntityFactory::CreateAIEntity(
	GameEntitiesContainer* container, 
	D3DXVECTOR3 position, 
	D3DXVECTOR3 size, 
	D3DCOLOR color, 
	long framesToWait,
	Behaviour behaviour,
	AIEntitiesInteractionContainer entitiesContainer,
	AStarPathfindingGraph* graph)
{
	return this->CreateAIEntity(container, position, size, color, framesToWait, behaviour, entitiesContainer, graph, nullptr);
}

GameEntity* EntityFactory::CreateAIEntity(
	GameEntitiesContainer* container, 
	D3DXVECTOR3 position, 
	D3DXVECTOR3 size, 
	D3DCOLOR color, 
	long framesToWait, 
	Behaviour behaviour,
	AIEntitiesInteractionContainer entitiesContainer,
	AStarPathfindingGraph* graph,
	GameEntity* entityToFollow)
{
	GameEntity* entity = new GameEntity(this->_game);
	entity->setPosition(position);
	entity->setSize(size);
	PhysicsComponent* physics = new PhysicsComponent(this->_game, entity);
	AIControllerComponent* aiController = new AIControllerComponent(this->_game, entity);
	AStarPathfindingComponent* pathfinding = new AStarPathfindingComponent(this->_game, entity, aiController, framesToWait, graph);
	ScaledBoxGraphicsComponent* graphics = new ScaledBoxGraphicsComponent(this->_game, entity, color);

	BehaviourComponent* behaviourComponent = new BehaviourComponent(this->_game, entity, behaviour, entitiesContainer, pathfinding);

	entity->AddComponent(physics);
	entity->AddComponent(aiController);
	entity->AddComponent(pathfinding);
	entity->AddComponent(behaviourComponent);
	entity->AddGraphicsComponent(graphics);

	if(entityToFollow != nullptr)
	{
		pathfinding->FollowEntity(entityToFollow);
	}
	
	container->Entities.push_back(entity);

	return entity;
}