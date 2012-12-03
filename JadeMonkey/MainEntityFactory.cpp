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

	DoorUseComponent* doorUse = AddDoor(25, 5, D3DXVECTOR3( 21 , 0, 0), container, player, true, camera);

	PlayerFPInputComponent* input = new PlayerFPInputComponent(game, cameraEntity, camera, physics, doorUse, player);
	
	camera->SetCamera(D3DXVECTOR3(30,70,30), D3DXVECTOR3(100,70,100), D3DXVECTOR3(0,1,0));

	cameraEntity->AddComponent(physics);
	cameraEntity->AddComponent(camera);
	cameraEntity->AddComponent(input);
	cameraEntity->AddComponent(player);

	container = CreateLevel1(container, player);

	container.Cameras.push_back(camera);
	container.Entities.push_back(cameraEntity);
	
	container = AddTrapDoor(8, 7, container, D3DXVECTOR3( 14, 12, 29), player); 

	container = AddKey(D3DXVECTOR3(2,0,48), 1, container, player);
	container = AddKey(D3DXVECTOR3(16,12,38), 2, container, player);

	return container;
}

DoorUseComponent* MainEntityFactory::AddDoor(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *player, bool xDoor, CameraComponent *camera)
{
	GameEntity* door = new GameEntity(this->_game);
	GameMap2GraphicsComponent* graphics = new GameMap2GraphicsComponent(numCols, numRows, this->_game, door);
	DoorComponent *doorComponent = new DoorComponent( this->_game, door, 2);
	door->AddGraphicsComponent(graphics);
	door->setPosition( D3DXVECTOR3(position.x * 20, position.y * 20, position.z * 20));

	DoorUseComponent *doorUse = new DoorUseComponent(this->_game, door, camera, player, doorComponent, xDoor);
	if( xDoor )
	{
		WallPointXCollisionComponent* wallCollision = new WallPointXCollisionComponent(this->_game, door, player);
		door->AddCollisionComponent(wallCollision);
		door->setRotation(D3DXVECTOR3(0, 90, 0));
	}
	else
	{
		WallPointCollisionComponent* wallCollision = new WallPointCollisionComponent(this->_game, door, player);
		door->AddCollisionComponent(wallCollision);
	}
	container.Entities.push_back(door);
	container.Walls.push_back(door);

	return doorUse;
}