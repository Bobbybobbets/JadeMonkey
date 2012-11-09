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

void GameEntity::setPosition(D3DXVECTOR3 position)
{
	this->_position = position;
}

D3DXVECTOR3 GameEntity::getDirection()
{
	return this->_direction;
}

void GameEntity::setDirection(D3DXVECTOR3 direction)
{
	this->_direction = direction;
}

D3DXVECTOR3 GameEntity::getRotation()
{
	return this->_rotation;
}

void GameEntity::setRotation(D3DXVECTOR3 rotation)
{
	this->_rotation = rotation;
}

D3DXVECTOR3 GameEntity::getScale()
{
	return this->_scale;
}

void GameEntity::setScale(D3DXVECTOR3 scale)
{
	this->_scale = scale;
}