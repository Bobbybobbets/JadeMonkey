#include "WallPointXCollisionComponent.h"
#include "MainEntityFactory.h"
#include "PlayerFPInputComponent.h"
#include "CameraComponent.h"
#include "GameMap1GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "GameMap2GraphicsComponent.h"
#include "CuboidCollisionComponent.h"
#include "WallPointCollisionComponent.h"
#include "FloorPointCollisionComponent.h"
#include "PlayerComponent.h"

using namespace std;

MainEntityFactory::MainEntityFactory(Game* game)
	: EntityFactory(game)
{
}

GameEntitiesContainer MainEntityFactory::GetContainer(void)
{
	GameEntitiesContainer container;


	//create main character
	GameEntity* cameraEntity = new GameEntity(this->_game);
	CameraComponent* camera = new CameraComponent(this->_game, cameraEntity);
	PlayerComponent* player = new PlayerComponent(this->_game, cameraEntity);
	PhysicsComponent* physics = new PhysicsComponent(this->_game, cameraEntity);
	PlayerFPInputComponent* input = new PlayerFPInputComponent(this->_game, cameraEntity, camera, physics);
	
	camera->SetCamera(D3DXVECTOR3(30,70,30), D3DXVECTOR3(100,70,100), D3DXVECTOR3(0,1,0));

	cameraEntity->AddComponent(physics);
	cameraEntity->AddComponent(camera);
	cameraEntity->AddComponent(input);
	cameraEntity->AddComponent(player);

	// Using to get access to the dx/dy for the squares
	GameEntity* throwaway = new GameEntity(this->_game);
	GameMap1GraphicsComponent* graphics = new GameMap1GraphicsComponent(20, 20, this->_game, throwaway);


	// AddFloor( z numbers, z numbers, blah blah)
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
	container = AddWall( height,width, D3DXVECTOR3(graphics->getDx() * 49, 0,0), container, player, true);
	// W4
	container = AddWall(height,length, D3DXVECTOR3(0,0, 49 * graphics->getDx()), container, player, false);
	// F2
	container = AddFloor( width,length , D3DXVECTOR3(0,24 * graphics->getDx(), 0), container, player);
	
	// Containing walls
	// W5
	container = AddWall( height, 26, D3DXVECTOR3(3 * graphics->getDx(), 0, 0) , container, player, true);
	// W6
	container = AddWall( (int)(height/2), 18 , D3DXVECTOR3( 3 * graphics->getDx(), 0 , 25 * graphics->getDx()), container, player, false);
	// W7
	container = AddWall( height, 7, D3DXVECTOR3( 24 * graphics->getDx() , 0 , 25 * graphics->getDx()), container, player, false);
	// W8
	container = AddWall( (int)(height / 2), 8 , D3DXVECTOR3( 30 * graphics->getDx(), 0, 25 * graphics->getDx()), container, player, false);
	// W9
	container = AddWall( height, 10 , D3DXVECTOR3( 37 * graphics->getDx(), 0, 25 * graphics->getDx()) , container, player, false);
	// W10
	container = AddWall( height, 22, D3DXVECTOR3( 46 * graphics->getDx(), 0, 4 * graphics->getDx()), container, player, true);
	// W11
	container = AddWall( height, 26, D3DXVECTOR3( 21 * graphics->getDx(), 0, 4 * graphics->getDx()),  container, player, false);
	// W12
	container = AddWall( height, 5, D3DXVECTOR3( 21 * graphics->getDx(), 0, 0), container, player, true);
	// S1
	container = AddStairs( 6, 4, D3DXVECTOR3( 20 * graphics->getDx(), 0 , 25 * graphics->getDx()), container, player, 4, false);
	// Plateau for staircase
	container = AddFloor( 5 , 5 , D3DXVECTOR3( 20 * graphics->getDx() , 6 * graphics->getDx(),  16 * graphics->getDx()), container, player );
	// Second half of staircase
	container = AddStairs( 6, 1, D3DXVECTOR3( 24 * graphics->getDx(), 6 * graphics->getDx(), 16 * graphics->getDx()), container, player , 4, true);
	// Right  for 2nd floor
	container = AddWall( height, 10 , D3DXVECTOR3( 20 * graphics->getDx(), 0 , 16 * graphics->getDx()), container, player, true);
	// Left stair wall
	container = AddWall( height, 6, D3DXVECTOR3( 24 * graphics->getDx(), 0, 20 * graphics->getDx()), container, player, true);
	// W27
	container = AddWall( height, 6, D3DXVECTOR3( 30 * graphics->getDx(), 0, 20 * graphics->getDx()), container, player, true);
	//
	container = AddWall( height, 7, D3DXVECTOR3( 24 * graphics->getDx(), 0, 20 * graphics->getDx()), container, player, false);
	// 2nd floor at top of stairs
	container = AddFloor( 22 , 8, D3DXVECTOR3( 30 * graphics->getDx() , (int)(height / 2) * graphics->getDx(), 4 * graphics->getDx()), container, player);
	//
	container = AddWall( height, 11, D3DXVECTOR3(20 * graphics->getDx(), 0, 16 * graphics->getDx()), container, player, false);
	// W21
	container = AddWall( (int)(height / 2) , 21 , D3DXVECTOR3( 37 * graphics->getDx() , (int)(height / 2) * graphics->getDx() , 5 * graphics->getDx()), container, player, true);
	// W22
	container = AddWall( (int)(height / 2) , 8, D3DXVECTOR3(30 * graphics->getDx() , (int)(height / 2) * graphics->getDx(), 4 * graphics->getDx()), container, player, true);
	// W23
	container = AddWall( (int)(height / 2) , 18, D3DXVECTOR3(13 * graphics->getDx() , (int)(height / 2) * graphics->getDx(), 11 * graphics->getDx()), container, player, false);
	// W24
	container = AddWall( (int)(height / 2) , 30, D3DXVECTOR3( 13 * graphics->getDx() , (int)(height / 2) * graphics->getDx(), 11 * graphics->getDx()), container, player, true);
	// W25
	container = AddWall(( int)(height / 2), 16, D3DXVECTOR3( 20 * graphics->getDx(), (int)(height / 2) * graphics->getDx(), 25 * graphics->getDx()), container, player, true);
	// Floor for previous walls
	container = AddFloor( 6, 18 , D3DXVECTOR3( 13 * graphics->getDx(), (int)(height/2) * graphics->getDx() , 11 * graphics->getDx()), container, player);
	container = AddFloor( 14, 8, D3DXVECTOR3( 13 * graphics->getDx() , (int)(height/2) * graphics->getDx() , 16 * graphics->getDx()), container, player);

	// Add floor extending into main room
	container = AddFloor(8 , 2, D3DXVECTOR3( 19 * graphics->getDx(), (int)(height/2) * graphics->getDx(), 29 * graphics->getDx()), container, player);
	container = AddFloor(8 , 2, D3DXVECTOR3( 13 * graphics->getDx(), (int)(height / 2) * graphics->getDx(), 29 * graphics->getDx()), container, player);
	container = AddFloor(5 , 8, D3DXVECTOR3(13 * graphics->getDx() , (int)(height / 2) * graphics->getDx(), 36 * graphics->getDx()), container, player);

	// W26
	container = AddWall(height, 47 , D3DXVECTOR3( 0, 0, 40 * graphics->getDx()), container, player, false);
	// W27
	container = AddWall(height, 2, D3DXVECTOR3( 46 * graphics->getDx(), 0 , 40 * graphics->getDx()), container, player, true);
	// W28
	container = AddWall( height, 47, D3DXVECTOR3( 0, 0, 41 * graphics->getDx()), container, player, false);

	container.Cameras.push_back(camera);
	container.Entities.push_back(cameraEntity);
	

	return container;
}

GameEntitiesContainer MainEntityFactory::AddFloor(int numRows, int numCols, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *player)
{
	GameEntity* floor = new GameEntity(this->_game);
	GameMap1GraphicsComponent* graphics6 = new GameMap1GraphicsComponent(numRows, numCols, this->_game, floor);
	floor->AddGraphicsComponent(graphics6);
	floor->setPosition( position);
	FloorPointCollisionComponent* floorCollision = new FloorPointCollisionComponent(this->_game, floor, player);
	floor->AddCollisionComponent(floorCollision);
	gc.Entities.push_back(floor);
	gc.Floors.push_back(floor);

	return gc;
}

GameEntitiesContainer MainEntityFactory::AddWall(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *player, bool xWall)
{
	GameEntity* wall = new GameEntity(this->_game);
	GameMap2GraphicsComponent* graphics = new GameMap2GraphicsComponent(numCols, numRows, this->_game, wall);
	wall->AddGraphicsComponent(graphics);
	wall->setPosition( position);

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

GameEntitiesContainer MainEntityFactory::AddStair(D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *pc, int width, bool xStair)
{
	gc = AddWall( 2, width + 1, position, gc, pc, xStair);
	
	if( !xStair )
		gc = AddFloor(2, width + 1, D3DXVECTOR3(position.x, position.y + 20, position.z - 20), gc, pc);
	else
		gc = AddFloor(width + 1, 2, D3DXVECTOR3(position.x, position.y + 20, position.z), gc, pc);
		
	return gc;
}

/* Add in a number of specified stairs in a given direction
* 1 - positive x
* 2 - negative x
* 3 - positive z
* 4 - negative z
*/
GameEntitiesContainer MainEntityFactory::AddStairs(int number, int direction, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *pc, int width, bool xStair)
{
	int x;
	for( x = 0 ; x < number ; x++)
	{
		switch( direction )
		{
		case 1:
			gc = AddWall(2, width + 1, D3DXVECTOR3(position.x + x * 20 , position.y + x * 20, position.z), gc, pc, xStair);
			gc = AddFloor(width + 1, 2 , D3DXVECTOR3(position.x + x  * 20, position.y + (x + 1) * 20, position.z), gc, pc);
			break;
		case 2:
			gc = AddWall( 2, width + 1, D3DXVECTOR3(position.x - x * 20 , position.y + x * 20 , position.z), gc, pc, xStair);
			gc = AddFloor(width + 1, 2, D3DXVECTOR3(position.x - x * 20, position.y + (x + 1) * 20, position.z), gc, pc);
			break;
		case 3:
			gc = AddWall( 2, width + 1, D3DXVECTOR3(position.x , position.y + x * 20 , position.z + x * 20), gc, pc, xStair);
			gc = AddFloor(2, width + 1, D3DXVECTOR3(position.x, position.y + (x + 1) * 20, position.z + x * 20), gc, pc);
			break;
		default:
			gc = AddWall( 2, width + 1, D3DXVECTOR3(position.x , position.y  + x * 20, position.z - x * 20), gc, pc, xStair);
			gc = AddFloor(2, width + 1, D3DXVECTOR3(position.x , position.y + (x + 1) * 20, position.z - (x + 1) * 20), gc, pc);
			break;


		}
	
	}
	return gc;
}

/* 	GameEntity* map = new GameEntity(this->_game);
	map->setPosition(D3DXVECTOR3(0,0,0));
	GameMap1GraphicsComponent* graphics = new GameMap1GraphicsComponent(100, 100, this->_game, map);
	GameEntity* map2 = new GameEntity(this->_game);
	GameMap2GraphicsComponent* graphics2 = new GameMap2GraphicsComponent(100, 100, this->_game, map2);
		float boundingBoxLength = 20;
	vector<D3DXVECTOR3> mainCharVertices = vector<D3DXVECTOR3>();
	mainCharVertices.push_back(D3DXVECTOR3(boundingBoxLength/2, boundingBoxLength/2, -boundingBoxLength/2));
	mainCharVertices.push_back(D3DXVECTOR3(boundingBoxLength/2, -boundingBoxLength/2, -boundingBoxLength/2));
	mainCharVertices.push_back(D3DXVECTOR3(-boundingBoxLength/2, -boundingBoxLength/2, -boundingBoxLength/2));
	mainCharVertices.push_back(D3DXVECTOR3(-boundingBoxLength/2, boundingBoxLength/2, -boundingBoxLength/2));
	mainCharVertices.push_back(D3DXVECTOR3(boundingBoxLength/2, boundingBoxLength/2, boundingBoxLength/2));
	mainCharVertices.push_back(D3DXVECTOR3(boundingBoxLength/2, -boundingBoxLength/2, boundingBoxLength/2));
	mainCharVertices.push_back(D3DXVECTOR3(-boundingBoxLength/2, -boundingBoxLength/2, boundingBoxLength/2));
	mainCharVertices.push_back(D3DXVECTOR3(-boundingBoxLength/2, boundingBoxLength/2, boundingBoxLength/2));

	CuboidPrism* mainBoundingBox = new CuboidPrism(mainCharVertices);

//	CuboidCollisionComponent* mainCollision = new CuboidCollisionComponent(this->_game, main, mainBoundingBox, true);

	//create collision bounding box for map
	vector<D3DXVECTOR3> vertices = vector<D3DXVECTOR3>();
	vertices.push_back(D3DXVECTOR3(0.0, 0.0, 0.0));
	vertices.push_back(D3DXVECTOR3(400.0, 0.0, 0.0));
	vertices.push_back(D3DXVECTOR3(400.0, 0.0, 400.0));
	vertices.push_back(D3DXVECTOR3(0.0, 0.0, 400.0));
	vertices.push_back(D3DXVECTOR3(0.0, -1.0, 0.0));
	vertices.push_back(D3DXVECTOR3(400.0, -1.0, 0.0));
	vertices.push_back(D3DXVECTOR3(400.0, -1.0, 400.0));
	vertices.push_back(D3DXVECTOR3(0.0, -1.0, 400.0));
*/
	/*	GameEntity* map = new GameEntity(this->_game);
	map->setPosition(D3DXVECTOR3(0,0,0));
	map->AddGraphicsComponent(graphics);
	FloorPointCollisionComponent* pointCollision = new FloorPointCollisionComponent(this->_game, map, player);
	map->AddCollisionComponent(pointCollision);
	container.Entities.push_back(map);
	container.Floors.push_back(map);
	*/

/*	GameEntity* map2 = new GameEntity(this->_game);
	GameMap2GraphicsComponent* graphics2 = new GameMap2GraphicsComponent(100, 100, this->_game, map2);
	map2->AddGraphicsComponent(graphics2);
	WallPointCollisionComponent* wallCollision = new WallPointCollisionComponent(this->_game, map2, player);
	map2->AddCollisionComponent(wallCollision);
	container.Entities.push_back(map2);
	container.Walls.push_back(map2);
	
	*/

/*
	GameEntity* map3 = new GameEntity(this->_game);
	GameMap2GraphicsComponent* graphics3 = new GameMap2GraphicsComponent(100, 100, this->_game, map3);
	map3->setRotation(D3DXVECTOR3(0.0,90,0.0));
	map3->AddGraphicsComponent(graphics3);
	WallPointXCollisionComponent* wallCollision2 = new WallPointXCollisionComponent(this->_game, map3, player);
	map3->AddCollisionComponent(wallCollision2);
	container.Entities.push_back(map3);
	container.Walls.push_back(map3);
*/

/*	GameEntity* map4 = new GameEntity(this->_game);
	GameMap2GraphicsComponent* graphics4 = new GameMap2GraphicsComponent(50, 50, this->_game, map4);
	map4->setRotation(D3DXVECTOR3(0.0,90,0.0));
	map4->AddGraphicsComponent(graphics4);
	map4->setPosition(D3DXVECTOR3(150,0,150));
	WallPointXCollisionComponent* wallCollision3 = new WallPointXCollisionComponent(this->_game, map4, player);
	map4->AddCollisionComponent(wallCollision3);
	container.Entities.push_back(map4);
	container.Walls.push_back(map4);
*/


/*	GameEntity* map5 = new GameEntity(this->_game);
	map5->setRotation(D3DXVECTOR3(0.0,90,0.0));
	GameMap2GraphicsComponent* graphics5 = new GameMap2GraphicsComponent(50, 50, this->_game, map5);

	map5->AddGraphicsComponent(graphics5);
	map5->setPosition(D3DXVECTOR3(20 * graphics5->getDx(),-50 * graphics5->getDy(),0));
	WallPointXCollisionComponent* wallCollision4 = new WallPointXCollisionComponent(this->_game, map5, player);
	map5->AddCollisionComponent(wallCollision4);
	container.Entities.push_back(map5);
	container.Walls.push_back(map5);
	*/
/*	GameEntity* map6 = new GameEntity(this->_game);
	GameMap1GraphicsComponent* graphics6 = new GameMap1GraphicsComponent(20, 20, this->_game, map6);
	map6->AddGraphicsComponent(graphics6);
	map6->setPosition(D3DXVECTOR3( -20 * graphics6->getDx() ,100 * graphics5->getDy(),0));
	FloorPointCollisionComponent* floorCollision = new FloorPointCollisionComponent(this->_game, map6, player);
	map6->AddCollisionComponent(floorCollision);
	container.Entities.push_back(map6);
	container.Floors.push_back(map6);
*/
