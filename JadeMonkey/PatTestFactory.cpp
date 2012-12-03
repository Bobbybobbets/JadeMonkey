#include "PatTestFactory.h"
#include "PhysicsComponent.h"
#include "PlayerFPInputComponent.h"
#include "ScaledBoxGraphicsComponent.h"
#include "PathfindingUtil.h"
#include "PathfindingGraphNode.h"
#include "GameMap1GraphicsComponent.h"
#include "AStarPathfindingComponent.h"
#include "AIControllerComponent.h"
#include "BehaviourBuilder.h"
#include "Enums.h"
#include "FireboltSkillComponent.h"

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
	FireboltSkillComponent* firebolt = new FireboltSkillComponent(game, cameraEntity, 10);
	PlayerFPInputComponent* input = new PlayerFPInputComponent(game, cameraEntity, camera, physics, firebolt);
	
	
	camera->SetCamera(D3DXVECTOR3(-500, 100, -500), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0,1,0));

	cameraEntity->AddComponent(firebolt);
	cameraEntity->AddComponent(physics);
	cameraEntity->AddComponent(camera);
	cameraEntity->AddComponent(input);

	AIEntitiesInteractionContainer aiEntitiesContainer(cameraEntity, nullptr, vector<GameEntity*>());

	AStarPathfindingGraph* graph = PathfindingUtil::CreateAStarGraphFromFloors(50, 50, 20, 20, D3DXVECTOR3(-35, 0, -35));
	//create AI controller character
	GameEntity* aiEntity1 = this->CreateAIEntity(&container, D3DXVECTOR3(10, 100, 0), D3DXVECTOR3(10, 40, 10), D3DCOLOR_RGBA(255, 0, 0, 255), 0, BasicEnemy, aiEntitiesContainer, graph);
	GameEntity* aiEntity2 = this->CreateAIEntity(&container, D3DXVECTOR3(50, 100, 0), D3DXVECTOR3(10, 40, 10), D3DCOLOR_RGBA(0, 255, 0, 255), 1, BasicEnemy, aiEntitiesContainer, graph);
	GameEntity* aiEntity3 = this->CreateAIEntity(&container, D3DXVECTOR3(90, 100, 0), D3DXVECTOR3(10, 40, 10), D3DCOLOR_RGBA(255, 0, 0, 255), 2, BasicEnemy, aiEntitiesContainer, graph);
	GameEntity* aiEntity4 = this->CreateAIEntity(&container, D3DXVECTOR3(130, 100, 0), D3DXVECTOR3(10, 40, 10), D3DCOLOR_RGBA(0, 255, 0, 255), 3, BasicEnemy, aiEntitiesContainer, graph);
	GameEntity* aiEntity5 = this->CreateAIEntity(&container, D3DXVECTOR3(170, 100, 0), D3DXVECTOR3(10, 40, 10), D3DCOLOR_RGBA(255, 0, 0, 255), 4, BasicEnemy, aiEntitiesContainer, graph);

	//create floor
	container = this->AddFloor(50, 50, D3DXVECTOR3(-35, 0, -35), container);


	
	
	container.Cameras.push_back(camera);
	container.Entities.push_back(cameraEntity);
	return container;
}