#include "TargetedSkillComponent.h"
#include "VectorUtil.h"
#include "GameEntity.h"

TargetedSkillComponent::TargetedSkillComponent(Game* game, GameEntity* entity, int cooldown, float range)
	: SkillComponent(game, entity, cooldown)
{
	this->_target = nullptr;
	this->_range = range;
}

void TargetedSkillComponent::SetTarget(GameEntity* target)
{
	this->_target = target;
}

bool TargetedSkillComponent::InRange(GameEntity* entity)
{
	if(VectorUtil::Distance3f(this->_entity->getPosition(), entity->getPosition()))
	{
		return true;
	}

	return false;
}

float TargetedSkillComponent::GetRange(void)
{
	return this->_range;
}