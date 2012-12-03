#pragma once
#include "SkillComponent.h"

class JadeMonkeyGame;

class FireboltSkillComponent : public SkillComponent
{
public:
	FireboltSkillComponent(Game* game, GameEntity* entity, int cooldown);

protected:
	void fireSkill(void) override;
};
