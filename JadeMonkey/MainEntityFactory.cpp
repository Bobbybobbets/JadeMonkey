#include "MainEntityFactory.h"
#include "PlayerFPInputComponent.h"
#include "CameraComponent.h"

MainEntityFactory::MainEntityFactory(Game* game)
	: EntityFactory(game)
{
}

GameEntitiesContainer MainEntityFactory::GetContainer(void)
{
	GameEntitiesContainer container;
	GameEntity* main = new GameEntity(this->_game);
	CameraComponent* camera = new CameraComponent(this->_game, main);
	camera->SetCamera(D3DXVECTOR3(0,70,0), D3DXVECTOR3(50,70,50), D3DXVECTOR3(0,1,0));

	PlayerFPInputComponent* input = new PlayerFPInputComponent(this->_game, main, camera);

	main->AddComponent(camera);
	main->AddComponent(input);

	container.Cameras.push_back(camera);
	container.Entities.push_back(main);

	return container;
}