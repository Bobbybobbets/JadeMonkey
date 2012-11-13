#include "MainEntityFactory.h"
#include "PlayerFPInputComponent.h"
#include "CameraComponent.h"
#include "GameMap1GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "CuboidCollisionComponent.h"

using namespace std;

MainEntityFactory::MainEntityFactory(Game* game)
	: EntityFactory(game)
{
}

GameEntitiesContainer MainEntityFactory::GetContainer(void)
{
	GameEntitiesContainer container;


	//create main character
	GameEntity* main = new GameEntity(this->_game);
	CameraComponent* camera = new CameraComponent(this->_game, main);
	camera->SetCamera(D3DXVECTOR3(30,70,30), D3DXVECTOR3(100,70,100), D3DXVECTOR3(0,1,0));

	PlayerFPInputComponent* input = new PlayerFPInputComponent(this->_game, main, camera);

	PhysicsComponent* physics = new PhysicsComponent(this->_game, main);

	//create collision bounding box for main character
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

	CuboidCollisionComponent* mainCollision = new CuboidCollisionComponent(this->_game, main, mainBoundingBox, true);

	main->AddComponent(physics);
	main->AddComponent(camera);
	main->AddComponent(input);
	main->AddComponent(mainCollision);
	

	container.Cameras.push_back(camera);
	container.Entities.push_back(main);

	//create map
	GameEntity* map = new GameEntity(this->_game);
	GameMap1GraphicsComponent* graphics = new GameMap1GraphicsComponent(this->_game, map);


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

	CuboidPrism* boundingBox = new CuboidPrism(vertices);
			
	CuboidCollisionComponent* collision = new CuboidCollisionComponent(this->_game, map, boundingBox, false);

	map->AddComponent(collision);
	map->AddGraphicsComponent(graphics);

	container.Entities.push_back(map);




	return container;
}