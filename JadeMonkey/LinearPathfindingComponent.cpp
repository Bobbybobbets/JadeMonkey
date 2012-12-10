#include "LinearPathfindingComponent.h"
#include <d3dx9.h>
#include "AIControllerComponent.h"
#include "GameEntity.h"
#include "Game.h"

LinearPathfindingComponent::LinearPathfindingComponent(Game* game, GameEntity* entity, AIControllerComponent* aiController)
	: BEntityComponent(game, entity)
{
	this->_aiController = aiController;
	this->_followEntity = false;
	this->_entityToFollow = nullptr;
}

LinearPathfindingComponent::~LinearPathfindingComponent(void)
{
}

void LinearPathfindingComponent::Update(GameEntity* entity, long time)
{
	if(this->_followEntity && this->_entityToFollow != nullptr)
	{
		this->_aiController->MoveTo(this->_entityToFollow->getPosition());
	}
}

void LinearPathfindingComponent::FollowEntity(GameEntity* entity)
{
	this->_followEntity = true;
	this->_entityToFollow = entity;
}