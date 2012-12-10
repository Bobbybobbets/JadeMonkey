#include "SkillComponent.h"
#include "GameEntity.h"
#include <algorithm>

SkillComponent::SkillComponent(Game* game, GameEntity* entity, int cooldown)
	: BDrawableEntityComponent(game, entity)
{
	this->_activated = false;
	this->_cooldown = cooldown;
	this->_timeCounter = 0;
}

void SkillComponent::Update(GameEntity* entity, long time)
{
	this->_timeCounter++;
	GameEntity* todelete = nullptr;

	if(this->_activated)
	{
		this->fireSkill();
		this->_activated = false;
	}

	vector<GameEntity*>::iterator it;
	for(it = this->_children.begin(); it < this->_children.end(); it++)
	{
		if((*it)->IsActive() )
		{
			(*it)->Update(time);
		}
	}
}

void SkillComponent::Draw(long time)
{
	vector<GameEntity*>::iterator it;
	for(it = this->_children.begin(); it < this->_children.end(); it++)
	{
		(*it)->Draw(time);
	}
}

void SkillComponent::Activate()
{
	if(this->_timeCounter >= this->_cooldown)
	{
		this->_activated = true;
		this->_timeCounter = 0;
	}
}