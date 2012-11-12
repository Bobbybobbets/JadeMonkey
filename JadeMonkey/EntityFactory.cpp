#include "EntityFactory.h"

EntityFactory::EntityFactory(Game* game)
{
	this->_game = game;
}

GameEntitiesContainer EntityFactory::GetContainer(void)
{
	GameEntitiesContainer cont;
	return cont;
}