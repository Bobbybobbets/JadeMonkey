#include "StdAfx.h"
#include "GameEntity.h"
#include "CollisionComponent.h"
#include "GraphicsComponent.h"
#include "Constants.h"

GameEntity::GameEntity(Game* game) : 
	DrawableGameComponent(game),
	_rotation(0.0, 0.0, 0.0), 
	_position(0.0,0.0,0.0),
	_positionBuffer(0.0, 0.0, 0.0),
	_direction(0.0,0.0,0.0),
	_scale(1.0, 1.0, 1.0),
	_speed(3.0),
	_height(40),
	_stepHeight(20),
	_velocity(0)
{
	this->_visible = false;
}

GameEntity::GameEntity(Game* game, D3DXVECTOR3 size) : 
	DrawableGameComponent(game),
	_rotation(0.0, 0.0, 0.0), 
	_position(0.0,0.0,0.0),
	_positionBuffer(0.0, 0.0, 0.0),
	_direction(0.0,0.0,0.0),
	_scale(1.0, 1.0, 1.0),
	_speed(3.0),
	_height(40),
	_stepHeight(20),
	_velocity(0)
{
	this->setSize(size);
	this->_visible = false;
}

GameEntity::~GameEntity()
{
}

void GameEntity::AddComponent(BEntityComponent* component)
{
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

void GameEntity::AddGraphicsComponent(GraphicsComponent* component)
{
	this->_visible = true;
	this->_graphicsComponents.push_back(component);
}

void GameEntity::AddCollisionComponent(CollisionComponent* component)
{
	this->_collisionComponents.push_back(component);
}
int GameEntity::Initialize()
{
	for(vector<BEntityComponent*>::iterator it = this->_components.begin();
		it < this->_components.end();
		it++)
	{
		(*it)->Initialize();
	}

	for(vector<GraphicsComponent*>::iterator it = this->_graphicsComponents.begin();
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
	
	this->setPosition(this->getPosition() += this->getDirection()*this->_velocity);
	return 0;
}

int GameEntity::Draw(long time)
{
	if(this->_visible)
	{
		for(vector<GraphicsComponent*>::iterator it = this->_graphicsComponents.begin();
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
	D3DXVec3Normalize(&this->_direction, &this->_direction);

	float yAngle = 180 - D3DXVec3Dot(&D3DXVECTOR3(1.0, 0.0, 0.0), &(this->_direction)) * 180 / PI;
	this->setRotation(D3DXVECTOR3(0.0, yAngle, 0.0));
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

D3DXVECTOR3 GameEntity::getSize()
{
	return this->_size;
}

void GameEntity::setSize(D3DXVECTOR3 size)
{
	this->_size = size;
}
float GameEntity::getSpeed(void)
{
	return this->_speed;
}

void GameEntity::setSpeed(float speed)
{
	this->_speed = speed;
}

int GameEntity::getHeight()
{
	return this->_height;
}

void GameEntity::setHeight(int height)
{
	this->_height = height;
}

int GameEntity::getStepHeight(void)
{
	return this->_stepHeight;
}

void GameEntity::setStepHeight(int stepHeight)
{
	this->_stepHeight = stepHeight;
}

float GameEntity::getVelocity(void)
{
	return this->_velocity;
}

void GameEntity::setVelocity(float velocity)
{
	this->_velocity = velocity;
}


GraphicsComponent* GameEntity::getGraphicsComponent()
{
	return _graphicsComponents.at(0);
}
vector<CollisionComponent*> GameEntity::getCollisionComponents()
{
	return _collisionComponents;
}