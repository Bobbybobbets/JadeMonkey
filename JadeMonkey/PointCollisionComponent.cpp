#include "PointCollisionComponent.h"
#include "CollisionComponent.h"

PointCollisionComponent::PointCollisionComponent(Game *game, GameEntity* gameEntity, PlayerComponent *pc): CollisionComponent(game,gameEntity)
{
	this->height = height;
	this->width = width;
	this->length = length;
	this->pc = pc;
}

PointCollisionComponent::~PointCollisionComponent()
{
}


string PointCollisionComponent::GetName()
{
	return "PointCollisionComponent";
}