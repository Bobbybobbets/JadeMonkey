#include "KeyPartComponent.h"
#include <math.h>

float KeyPartComponent::keyWidth = 20.0;

KeyPartComponent::KeyPartComponent( Game *game, GameEntity *entity, PlayerComponent *player, int keyNumber, D3DXVECTOR3 position) : BEntityComponent(game, entity)
{
	this->keyNumber = keyNumber;
	this->_position = position;
	this->_player = player;
}

void KeyPartComponent::Initialize(void)
{
	retrieved = false;
}

void KeyPartComponent::Update(GameEntity* entity, long time)
{
	if( !retrieved)
		if(checkPickup(_player->getEntity()->getPosition()))
		{
			retrieved = true;
			_player->FoundKey();
			return;
		}
}
bool KeyPartComponent::checkPickup( D3DXVECTOR3 toCheck)
{
	// in the x bounds
	if( toCheck.x > _position.x && toCheck.x < _position.x + keyWidth)
		// In the z bounds
		if( toCheck.z > _position.z && toCheck.z < _position.z + keyWidth)
			// In the y bounds
			if( toCheck.y > _position.y && toCheck.y <= _position.y + _player->getHeight())
				return true;

	return false;
}

bool KeyPartComponent::getRetrieved()
{
	return retrieved;
}