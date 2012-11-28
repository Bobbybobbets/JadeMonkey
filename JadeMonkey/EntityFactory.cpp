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


EntityFactory::EntityFactory(void)
{
}

GameEntitiesContainer EntityFactory::GetContainer(Game* game)
{
	GameEntitiesContainer cont;
	return cont;
}

GameEntitiesContainer EntityFactory::AddFloor(int numRows, int numCols, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *player)
{
	GameEntity* floor = new GameEntity(this->_game);
	GameMap1GraphicsComponent* graphics6 = new GameMap1GraphicsComponent(numRows, numCols, this->_game, floor);
	floor->AddGraphicsComponent(graphics6);
	floor->setPosition( D3DXVECTOR3(position.x * 20, position.y * 20, position.z * 20));
	FloorPointCollisionComponent* floorCollision = new FloorPointCollisionComponent(this->_game, floor, player);
	floor->AddCollisionComponent(floorCollision);
	gc.Entities.push_back(floor);
	gc.Floors.push_back(floor);

	return gc;
}

GameEntitiesContainer EntityFactory::AddWall(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *player, bool xWall)
{
	GameEntity* wall = new GameEntity(this->_game);
	GameMap2GraphicsComponent* graphics = new GameMap2GraphicsComponent(numCols, numRows, this->_game, wall);
	wall->AddGraphicsComponent(graphics);
	wall->setPosition( D3DXVECTOR3(position.x * 20, position.y * 20, position.z * 20));

	if( xWall )
	{
		WallPointXCollisionComponent* wallCollision = new WallPointXCollisionComponent(this->_game, wall, player);
		wall->AddCollisionComponent(wallCollision);
		wall->setRotation(D3DXVECTOR3(0, 90, 0));
	}
	else
	{
		WallPointCollisionComponent* wallCollision = new WallPointCollisionComponent(this->_game, wall, player);
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
GameEntitiesContainer EntityFactory::AddStairs(int number, int direction, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *pc, int width, bool xStair)
{
	int x;
	for( x = 0 ; x < number ; x++)
	{
		switch( direction )
		{
		case 1:
			gc = AddWall(2, width + 1, D3DXVECTOR3(position.x + x  , position.y + x , position.z), gc, pc, xStair);
			gc = AddFloor(width + 1, 2 , D3DXVECTOR3(position.x + x  , position.y + (x + 1) , position.z), gc, pc);
			break;
		case 2:
			gc = AddWall( 2, width + 1, D3DXVECTOR3(position.x - x  , position.y + x  , position.z), gc, pc, xStair);
			gc = AddFloor(width + 1, 2, D3DXVECTOR3(position.x - x , position.y + (x + 1) , position.z), gc, pc);
			break;
		case 3:
			gc = AddWall( 2, width + 1, D3DXVECTOR3(position.x , position.y + x  , position.z + x ), gc, pc, xStair);
			gc = AddFloor(2, width + 1, D3DXVECTOR3(position.x, position.y + (x + 1) , position.z + x ), gc, pc);
			break;
		default:
			gc = AddWall( 2, width + 1, D3DXVECTOR3(position.x , position.y  + x , position.z - x ), gc, pc, xStair);
			gc = AddFloor(2, width + 1, D3DXVECTOR3(position.x , position.y + (x + 1) , position.z - (x + 1) ), gc, pc);
			break;

		}
	
	}
	return gc;
}

GameEntitiesContainer EntityFactory::AddKey(D3DXVECTOR3 position, int keyNumber, GameEntitiesContainer gc, PlayerComponent *player)
{
	position = D3DXVECTOR3(1,0,4);
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

GameEntitiesContainer EntityFactory::CreateLevel1(GameEntitiesContainer container, PlayerComponent *player)
{
		int height = 25;
	int width = 50;
	int length = 50;
	// Create the bounding walls and floor
	// F1
	container = AddFloor( width , length, D3DXVECTOR3(0,0,0) , container, player);
	// W1
	container = AddWall( height, width, D3DXVECTOR3(0,0,0), container, player, true);
	// W2
	container = AddWall( height,length, D3DXVECTOR3(0,0,0) , container, player, false);
	// W3
	container = AddWall( height,width, D3DXVECTOR3( 49, 0,0), container, player, true);
	// W4
	container = AddWall(height,length, D3DXVECTOR3(0,0, 49 ), container, player, false);
	// F2
	container = AddFloor( width,length , D3DXVECTOR3(0,24 , 0), container, player);
	
	// Containing walls
	// W5
	container = AddWall( height, 26, D3DXVECTOR3(3 , 0, 0) , container, player, true);
	// W6
	container = AddWall( (int)(height/2), 18 , D3DXVECTOR3( 3 , 0 , 25 ), container, player, false);
	// W7
	container = AddWall( height, 7, D3DXVECTOR3( 24  , 0 , 25 ), container, player, false);
	// W8
	container = AddWall( (int)(height / 2), 8 , D3DXVECTOR3( 30 , 0, 25 ), container, player, false);
	// W9
	container = AddWall( height, 10 , D3DXVECTOR3( 37 , 0, 25 ) , container, player, false);
	// W10
	container = AddWall( height, 22, D3DXVECTOR3( 46 , 0, 4 ), container, player, true);
	// W11
	container = AddWall( height, 26, D3DXVECTOR3( 21 , 0, 4 ),  container, player, false);
	// W12
	container = AddWall( height, 5, D3DXVECTOR3( 21 , 0, 0), container, player, true);
	// S1
	container = AddStairs( 6, 4, D3DXVECTOR3( 20 , 0 , 25 ), container, player, 4, false);
	// Plateau for staircase
	container = AddFloor( 5 , 5 , D3DXVECTOR3( 20  , 6 ,  16 ), container, player );
	// Second half of staircase
	container = AddStairs( 6, 1, D3DXVECTOR3( 24 , 6 , 16 ), container, player , 4, true);
	// Right  for 2nd floor
	container = AddWall( height, 10 , D3DXVECTOR3( 20 , 0 , 16 ), container, player, true);
	// Left stair wall
	container = AddWall( height, 6, D3DXVECTOR3( 24 , 0, 20 ), container, player, true);
	// W27
	container = AddWall( height, 6, D3DXVECTOR3( 30 , 0, 20 ), container, player, true);
	//
	container = AddWall( height, 7, D3DXVECTOR3( 24 , 0, 20 ), container, player, false);
	// 2nd floor at top of stairs
	container = AddFloor( 22 , 8, D3DXVECTOR3( 30  , (int)(height / 2) , 4 ), container, player);
	//
	container = AddWall( height, 11, D3DXVECTOR3(20 , 0, 16 ), container, player, false);
	// W21
	container = AddWall( (int)(height / 2) , 21 , D3DXVECTOR3( 37  , (int)(height / 2)  , 5 ), container, player, true);
	// W22
	container = AddWall( (int)(height / 2) , 8, D3DXVECTOR3(30  , (int)(height / 2) , 4 ), container, player, true);
	// W23
	container = AddWall( (int)(height / 2) , 18, D3DXVECTOR3(13  , (int)(height / 2) , 11 ), container, player, false);
	// W24
	container = AddWall( (int)(height / 2) , 30, D3DXVECTOR3( 13  , (int)(height / 2) , 11 ), container, player, true);
	// W25
	container = AddWall(( int)(height / 2), 16, D3DXVECTOR3( 20 , (int)(height / 2) , 25 ), container, player, true);
	// Floor for previous walls
	container = AddFloor( 6, 18 , D3DXVECTOR3( 13 , (int)(height/2)  , 11 ), container, player);
	container = AddFloor( 14, 8, D3DXVECTOR3( 13  , (int)(height/2)  , 16 ), container, player);

	// Add floor extending into main room
	container = AddFloor(8 , 2, D3DXVECTOR3( 19 , (int)(height/2) , 29 ), container, player);
	container = AddFloor(8 , 2, D3DXVECTOR3( 13 , (int)(height / 2) , 29 ), container, player);
	container = AddFloor(5 , 8, D3DXVECTOR3(13  , (int)(height / 2) , 36 ), container, player);

	// W26
	container = AddWall(height, 47 , D3DXVECTOR3( 0, 0, 40 ), container, player, false);
	// W27
	container = AddWall(height, 2, D3DXVECTOR3( 46 , 0 , 40 ), container, player, true);
	// W28
	container = AddWall( height, 47, D3DXVECTOR3( 0, 0, 41 ), container, player, false);

	return container;
}