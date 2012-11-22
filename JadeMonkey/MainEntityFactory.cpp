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

	container = AddFloor( 20,20, D3DXVECTOR3(0,0,0) , container, player);
	container = AddWall( 100,100, D3DXVECTOR3(0,0,0) , container, player, false);
	container = AddWall( 100,100, D3DXVECTOR3(0,0,0), container, player, true);
	container = AddWall( 50,50, D3DXVECTOR3(150,0,150), container, player, true);
	container = AddWall(50,50, D3DXVECTOR3(20 * graphics->getDx(),-50 * graphics->getDx(),0), container, player, true);
	container = AddFloor(20,20, D3DXVECTOR3( -20 * graphics->getDx() ,100 * graphics->getDx(),0) , container, player);
	//create collision bounding box for main character



	container.Cameras.push_back(camera);
	container.Entities.push_back(cameraEntity);
	

	return container;
}

GameEntitiesContainer MainEntityFactory::AddFloor(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *player)
{
	GameEntity* floor = new GameEntity(this->_game);
	GameMap1GraphicsComponent* graphics6 = new GameMap1GraphicsComponent(numCols, numRows, this->_game, floor);
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
