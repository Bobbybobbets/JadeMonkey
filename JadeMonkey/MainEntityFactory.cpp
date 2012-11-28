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

	container = CreateLevel1(container, player);

	container.Cameras.push_back(camera);
	container.Entities.push_back(cameraEntity);
	
	container = AddTrapDoor(8, 7, container, D3DXVECTOR3( 14, 12, 29), player); 

	container = AddKey(D3DXVECTOR3(2,0,48), 1, container, player);
	container = AddKey(D3DXVECTOR3(16,12,38), 2, container, player);

	return container;
}

