#include "PatTestFactory.h"
#include "PhysicsComponent.h"
#include "PlayerFPInputComponent.h"
#include "ScaledBoxGraphicsComponent.h"

PatTestFactory::PatTestFactory()
	: EntityFactory()
{
}

GameEntitiesContainer PatTestFactory::GetContainer(Game* game)
{
	this->_game = game;
	GameEntitiesContainer container;

	//create main character
	GameEntity* cameraEntity = new GameEntity(game);
	CameraComponent* camera = new CameraComponent(game, cameraEntity);
	
	PhysicsComponent* physics = new PhysicsComponent(game, cameraEntity);
	physics->setAccelerationVector(D3DXVECTOR3(0, 0, 0));
	PlayerFPInputComponent* input = new PlayerFPInputComponent(game, cameraEntity, camera, physics);
	
	camera->SetCamera(D3DXVECTOR3(-50, 200, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1,0,0));

	//cameraEntity->AddComponent(physics);
	cameraEntity->AddComponent(camera);
	cameraEntity->AddComponent(input);

	//create AI controller character
	GameEntity* testAI = new GameEntity(game, D3DXVECTOR3(30, 40, 10));
	PhysicsComponent* aiphysics = new PhysicsComponent(game, testAI);
	PlayerComponent* player = new PlayerComponent(game, testAI);
	testAI->setPosition(D3DXVECTOR3(10, 100, 0));
	ScaledBoxGraphicsComponent* aiGraphics = new ScaledBoxGraphicsComponent(game, testAI, D3DCOLOR_RGBA(255, 0, 0, 255));
	
	testAI->AddComponent(aiphysics);
	testAI->AddGraphicsComponent(aiGraphics);
	testAI->AddComponent(player);
	//testAI->AddComponent(camera);

	

	//create floor
	container = this->AddFloor(70, 70, D3DXVECTOR3(-35, 0, -35), container, player);

	container.Cameras.push_back(camera);
	container.Entities.push_back(cameraEntity);
	container.Entities.push_back(testAI);
	return container;
}