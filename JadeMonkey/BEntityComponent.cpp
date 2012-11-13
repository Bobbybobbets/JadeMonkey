#include "BEntityComponent.h"

BEntityComponent::BEntityComponent(Game* game, GameEntity* entity)
{
	this->_game = game;
	this->_entity = entity;
}

void BEntityComponent::Initialize(void)
{
}

void BEntityComponent::Update(GameEntity* entity, long time)
{
}

string BEntityComponent::GetName(void)
{
	return "Entity component";
}