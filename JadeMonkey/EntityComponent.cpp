#include "EntityComponent.h"

EntityComponent::EntityComponent(Game* game, GameEntity* entity)
{
	this->_game = game;
	this->_entity = entity;
}

void EntityComponent::Initialize(void)
{
}

void EntityComponent::Update(GameEntity* entity, long time)
{
}

string EntityComponent::GetName(void)
{
	return "Entity component";
}