#pragma once
#include "SkillComponent.h"
#include "Enums.h"

class JadeMonkeyGame;

class FireboltSkillComponent : public SkillComponent
{
public:
	FireboltSkillComponent(Game* game, GameEntity* entity, int cooldown, CollisionGroup group);

protected:
	void fireSkill(void) override;
	CollisionGroup _group;
	int _indexBuffer;
};
