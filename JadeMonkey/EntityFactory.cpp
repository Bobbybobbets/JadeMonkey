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
