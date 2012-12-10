#pragma once
#include "TargetedSkillComponent.h"
#include "Enums.h"

class HealSkillComponent : public TargetedSkillComponent
{
public:
	HealSkillComponent(Game* game, GameEntity* entity, int cooldown, float range, CollisionGroup group);
	

protected:
	CollisionGroup _group;

	virtual void fireSkill(void) override;
};