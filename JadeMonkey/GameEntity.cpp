#include "StdAfx.h"
#include "GameEntity.h"

GameEntity::GameEntity(Game* game) : 
	DrawableGameComponent(game),
	_rotation(0.0, 0.0, 0.0), 
	_position(0.0,0.0,0.0),
	_positionBuffer(0.0, 0.0, 0.0),
	_direction(0.0,0.0,0.0)
{
}

GameEntity::~GameEntity()
{
}

void GameEntity::AddComponent(BEntityComponent* component)
{
	this->_visible = false;
	this->_components.push_back(component);
}

void GameEntity::AddComponent(BEntityComponent* component, vector<BEntityComponent*> dependencies)
{
	vector<BEntityComponent*>::iterator maxIt;
	vector<BEntityComponent*>::iterator it;

	for(it = this->_components.begin(); it < this->_components.end(); it++)
	{
		for(int i = 0; i < dependencies.size(); i++)
		{
			if(*it == dependencies[i])
			{
				maxIt = it;
			}
		}
	}

	if(maxIt != this->_components.end())
	{
		this->_components.insert(maxIt+1, component);
	}
	else{
		this->AddComponent(component);
	}
}

void GameEntity::AddGraphicsComponent(BEntityComponent* component)
{
	this->_visible = true;
	this->_graphicsComponents.push_back(component);
}

int GameEntity::Initialize()
{
	for(vector<BEntityComponent*>::iterator it = this->_components.begin();
		it < this->_components.end();
		it++)
	{
		(*it)->Initialize();
	}

	for(vector<BEntityComponent*>::iterator it = this->_graphicsComponents.begin();
		it < this->_graphicsComponents.end();
		it++)
	{
		(*it)->Initialize();
	}

	return 0;
}

int GameEntity::Update(long time)
{
	for(vector<BEntityComponent*>::iterator it = this->_components.begin();
		it < this->_components.end();
		it++)
	{
		(*it)->Update(this, time);
	}
	
	return 0;
}

int GameEntity::Draw(long time)
{
	if(this->_visible)
	{
		for(vector<BEntityComponent*>::iterator it = this->_graphicsComponents.begin();
			it < this->_graphicsComponents.end();
			it++)
		{
			(*it)->Update(this, time);
		}
	}

	return 0;
}


D3DXVECTOR3 GameEntity::getPosition()
{
	return this->_position;
}

D3DXVECTOR3 GameEntity::getPositionBuffer()
{
	return this->_positionBuffer;
}

void GameEntity::setPosition(D3DXVECTOR3 position)
{
	this->_positionBuffer = this->_position;
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