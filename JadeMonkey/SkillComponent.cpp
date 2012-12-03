#include "SkillComponent.h"
#include "GameEntity.h"

SkillComponent::SkillComponent(Game* game, GameEntity* entity, int cooldown)
	: BEntityComponent(game, entity)
{
	this->_activated = false;
	this->_cooldown = cooldown;
	this->_timeCounter = 0;
}

void SkillComponent::Update(GameEntity* entity, long time)
{
	list<GameEntity*>::iterator it;
	this->_timeCounter++;

	if(this->_activated)
	{
		this->fireSkill();
		this->_activated = false;
	}

	/*
	for(it = this->_children.begin(); it < this->_children.end(); it++)
	{
		(*it)->Update(time);
		(*it)->Draw(time);
	}*/
}

void SkillComponent::Activate()
{
	if(this->_timeCounter >= this->_cooldown)
	{
		this->_activated = true;
		this->_timeCounter = 0;
	}
}