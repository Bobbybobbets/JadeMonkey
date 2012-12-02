#include "TrapDoorGraphicsComponent.h"


TrapDoorGraphicsComponent::TrapDoorGraphicsComponent(int numRows, int numCols, TrapDoorComponent *trapDoor , Game* game, GameEntity* entity) : GameMap1GraphicsComponent(numRows, numCols,game, entity)
{
	_trapDoor = trapDoor;
}

void TrapDoorGraphicsComponent::Update(GameEntity *entity, long time)
{
	if( _trapDoor->getTriggered())
	{
		D3DXVECTOR3 rotation = _entity->getRotation();                                                              
		// Check to see if angle > 90
		if( rotation.x < 90)
			_entity->setRotation(D3DXVECTOR3(rotation.x + 1, rotation.y, rotation.z));
	}
	GameMap1GraphicsComponent::Update(this->_entity, time);
}

void TrapDoorGraphicsComponent::Initialize()
{
	// Load the content
	GameMap1GraphicsComponent::Initialize();
}

string TrapDoorGraphicsComponent::GetName()
{
	return "TrapDoorGraphicsComponent";
}

