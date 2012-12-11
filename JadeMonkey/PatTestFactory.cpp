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
#include "PlayerComponent.h"
#include "DoorUseComponent.h"
#include "WallPointXCollisionComponent.h"
#include "WallPointCollisionComponent.h"
#include "GameMap2GraphicsComponent.h"
#include "RadiusBasedCollisionComponent.h"


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
	cameraEntity->SetInvincibility(true);
	CameraComponent* camera = new CameraComponent(game, cameraEntity);
	PlayerComponent* player = new PlayerComponent(game, cameraEntity);
	DoorUseComponent* doorUse = AddDoor(25, 5, D3DXVECTOR3( 21 , 0, 0), container, player, true, camera);
	PhysicsComponent* physics = new PhysicsComponent(game, cameraEntity);
	FireboltSkillComponent* firebolt = new FireboltSkillComponent(game, cameraEntity, 10, Player, player);
	PlayerFPInputComponent* input = new PlayerFPInputComponent(game, cameraEntity, camera, physics, firebolt, doorUse, player);
	RadiusBasedCollisionComponent* collisionGrid = new RadiusBasedCollisionComponent(game, cameraEntity, 15, Player, Nothing);
	
	camera->SetCamera(D3DXVECTOR3(-500, 100, -500), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0,1,0));

	cameraEntity->AddComponent(input);
	cameraEntity->AddComponent(collisionGrid);
	cameraEntity->AddSkillComponent(firebolt);
	cameraEntity->AddComponent(physics);
	cameraEntity->AddComponent(camera);
	cameraEntity->AddComponent(player);

	AIEntitiesInteractionContainer aiEntitiesContainer(cameraEntity, nullptr, vector<GameEntity*>(), Enemies);

	vector<D3DRECT> collisions;
	AStarPathfindingGraph* graph = PathfindingUtil::CreateAStarGraphFromFloors(50, 50, 20, 20, D3DXVECTOR3(-35, 0, -35), collisions);
	//create AI controller character
	GameEntity* aiEntity1 = this->CreateAIEntity(&container, D3DXVECTOR3(-10, 100, -100), D3DXVECTOR3(10, 40, 10), 5, D3DCOLOR_RGBA(255, 0, 0, 255), 0, BasicEnemy, aiEntitiesContainer, graph, player);
	GameEntity* aiEntity2 = this->CreateAIEntity(&container, D3DXVECTOR3(-50, 120, -100), D3DXVECTOR3(10, 40, 10), 7, D3DCOLOR_RGBA(0, 255, 0, 255), 1, RangedEnemy, aiEntitiesContainer, graph, player);
	GameEntity* aiEntity3 = this->CreateAIEntity(&container, D3DXVECTOR3(-90, 140, -100), D3DXVECTOR3(10, 40, 10), 5, D3DCOLOR_RGBA(255, 0, 0, 255), 2, BasicEnemy, aiEntitiesContainer, graph, player);
	GameEntity* aiEntity4 = this->CreateAIEntity(&container, D3DXVECTOR3(-130, 160, -100), D3DXVECTOR3(10, 40, 10), 7, D3DCOLOR_RGBA(0, 255, 0, 255), 3, RangedEnemy, aiEntitiesContainer, graph, player);
	GameEntity* aiEntity5 = this->CreateAIEntity(&container, D3DXVECTOR3(-170, 180, -100), D3DXVECTOR3(10, 40, 10), 5, D3DCOLOR_RGBA(255, 0, 0, 255), 4, BasicEnemy, aiEntitiesContainer, graph, player);
	GameEntity* aiEntity6 = this->CreateAIEntity(&container, D3DXVECTOR3(-210, 220, -100), D3DXVECTOR3(10, 40, 10), 10, D3DCOLOR_RGBA(0, 0, 255, 255), 5, HealerEnemy, aiEntitiesContainer, graph, player);
	//GameEntity* aiEntity7 = this->CreateAIEntity(&container, D3DXVECTOR3(-250, 220, -100), D3DXVECTOR3(10, 40, 10), 8, D3DCOLOR_RGBA(0, 0, 255, 255), 5, HealerEnemy, aiEntitiesContainer, graph, player);

	//create floor
	container = this->AddFloor(50, 50, D3DXVECTOR3(-35, 0, -35), container);


	container.Cameras.push_back(camera);
	container.Entities.push_back(cameraEntity);
	container.MainCharacter = player;
	return container;
}

DoorUseComponent* PatTestFactory::AddDoor(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *player, bool xDoor, CameraComponent *camera)
{
	int color;
	GameEntity* door = new GameEntity(this->_game);
	if( xDoor )
		color = 1;
	else
		color = 2;
	GameMap2GraphicsComponent* graphics;
	DoorComponent *doorComponent = new DoorComponent( this->_game, door, 2);
	door->AddGraphicsComponent(graphics);
	door->setPosition( D3DXVECTOR3(position.x * 20, position.y * 20, position.z * 20));

	DoorUseComponent *doorUse = new DoorUseComponent(this->_game, door, camera, player, doorComponent, xDoor);
	if( xDoor )
	{
		graphics = new GameMap2GraphicsComponent(numCols, numRows, this->_game, door, color, D3DXVECTOR3(1, 0, 0));
		WallPointXCollisionComponent* wallCollision = new WallPointXCollisionComponent(this->_game, door);
		door->AddCollisionComponent(wallCollision);
		door->setRotation(D3DXVECTOR3(0, 90, 0));
	}
	else
	{
		graphics = new GameMap2GraphicsComponent(numCols, numRows, this->_game, door, color, D3DXVECTOR3(0, 0, 1));
		WallPointCollisionComponent* wallCollision = new WallPointCollisionComponent(this->_game, door);
		door->AddCollisionComponent(wallCollision);
	}
	container.Entities.push_back(door);
	container.Walls.push_back(door);

	return doorUse;
}