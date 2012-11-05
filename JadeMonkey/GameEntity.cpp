#include "StdAfx.h"
#include "GameEntity.h"

GameEntity::GameEntity(Game* game) : 
	GameComponent(game),
	_rotation(0.0, 0.0, 0.0), 
	_position(0.0,0.0,0.0),
	_direction(0.0,0.0,0.0)
{
}

GameEntity::~GameEntity()
{
}

int GameEntity::Initialize()
{
	return 0;
}

int GameEntity::Update(long time)
{
	return 0;
}

D3DXVECTOR3 GameEntity::getPosition()
{
	return this->_position;
}

D3DXVECTOR3 GameEntity::getDirection()
{
	return this->_direction;
}

D3DXVECTOR3 GameEntity::getRotation()
{
	return this->_rotation;
}

D3DXVECTOR3 GameEntity::getScale()
{
	return this->_scale;
}