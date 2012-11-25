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

MainEntityFactory::MainEntityFactory()
	: EntityFactory()
{
}

GameEntitiesContainer MainEntityFactory::GetContainer(Game* game)
{
	this->_game = game;
	GameEntitiesContainer container;


	//create main character
	GameEntity* cameraEntity = new GameEntity(game);
	CameraComponent* camera = new CameraComponent(game, cameraEntity);
	PlayerComponent* player = new PlayerComponent(game, cameraEntity);
	PhysicsComponent* physics = new PhysicsComponent(game, cameraEntity);
	PlayerFPInputComponent* input = new PlayerFPInputComponent(game, cameraEntity, camera, physics);
	
	camera->SetCamera(D3DXVECTOR3(30,70,30), D3DXVECTOR3(100,70,100), D3DXVECTOR3(0,1,0));

	cameraEntity->AddComponent(physics);
	cameraEntity->AddComponent(camera);
	cameraEntity->AddComponent(input);
	cameraEntity->AddComponent(player);

	// Using to get access to the dx/dy for the squares
	GameEntity* throwaway = new GameEntity(game);
	GameMap1GraphicsComponent* graphics = new GameMap1GraphicsComponent(20, 20, game, throwaway);


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

	container.Cameras.push_back(camera);
	container.Entities.push_back(cameraEntity);
	

	return container;
}

