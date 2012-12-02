#include "PointCollisionComponent.h"
#include "CollisionComponent.h"

PointCollisionComponent::PointCollisionComponent(Game *game, GameEntity* gameEntity)
	: CollisionComponent(game,gameEntity)
{
	this->height = height;
	this->width = width;
	this->length = length;
}

PointCollisionComponent::~PointCollisionComponent()
{
}


string PointCollisionComponent::GetName()
{
	return "PointCollisionComponent";
}