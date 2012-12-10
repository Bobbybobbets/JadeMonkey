#pragma once
#include "SkillComponent.h"

class GameEntity;

class TargetedSkillComponent : public SkillComponent
{
public:
	TargetedSkillComponent(Game* game, GameEntity* entity, int cooldown, float range);
	void SetTarget(GameEntity* target);
	bool InRange(GameEntity* entity);
	float GetRange(void);

protected:
	float _range;

	GameEntity* _target;
	virtual void fireSkill(void) = 0;
};