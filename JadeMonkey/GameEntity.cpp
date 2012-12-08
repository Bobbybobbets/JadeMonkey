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
	_velocity(0),
	_active(true),
	_type(Enemy)
{
	this->_visible = true;
	this->_life = 100;
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
	_velocity(0),
	_active(true),
	_type(Enemy)
{
	this->setSize(size);
	this->_visible = true;
	this->_life = 100;
}

GameEntity::~GameEntity()
{
	for(int i = 0; i < this->_components.size(); i++)
	{
		delete(this->_components[i]);
	}
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
	this->_components.push_back(component);
}

void GameEntity::AddCollisionComponent(CollisionComponent* component)
{
	this->_collisionComponents.push_back(component);
	this->_components.push_back(component);
}

void GameEntity::AddSkillComponent(SkillComponent* component)
{
	this->_skillComponents.push_back(component);
	this->_components.push_back(component);
}

void GameEntity::AddDrawableComponent(BDrawableEntityComponent* drawableComponent)
{
	this->_components.push_back(drawableComponent);
	this->_graphicsComponents.push_back(drawableComponent);
}

int GameEntity::Initialize()
{
	for(vector<BEntityComponent*>::iterator it = this->_components.begin();
		it < this->_components.end();
		it++)
	{
		(*it)->Initialize();
	}

	return 0;
}

int GameEntity::Update(long time)
{

	//Update all components in this entity
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
		for(vector<BDrawableEntityComponent*>::iterator it = this->_graphicsComponents.begin();
			it < this->_graphicsComponents.end();
			it++)
		{
			(*it)->Draw(time);
		}
	}

	for(vector<SkillComponent*>::iterator it = this->_skillComponents.begin();
		it < this->_skillComponents.end();
		it++)
	{
		(*it)->Draw(time);
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

int GameEntity::getLife(void)
{
	return this->_life;
}

void GameEntity::setLife(int life)
{
	this->_life = life;
}

void GameEntity::reduceLife(int amount)
{
	this->_life -= amount;
}

bool GameEntity::IsActive(void)
{
	return this->_active;
}

void GameEntity::SetStatus(bool active)
{
	this->_active = active;
}

EntityType GameEntity::GetType(void)
{
	return this->_type;
}

void GameEntity::SetType(EntityType type)
{
	this->_type = type;
}

BDrawableEntityComponent* GameEntity::getGraphicsComponent()
{
	return _graphicsComponents.at(0);
}
vector<CollisionComponent*> GameEntity::getCollisionComponents()
{
	return _collisionComponents;
}