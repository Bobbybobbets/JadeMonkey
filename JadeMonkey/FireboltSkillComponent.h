#pragma once
#include "SkillComponent.h"
#include "Enums.h"
#include "PlayerComponent.h"

class JadeMonkeyGame;

class FireboltSkillComponent : public SkillComponent
{
public:
	FireboltSkillComponent(Game* game, GameEntity* entity, int cooldown, CollisionGroup group, PlayerComponent *player);

protected:
	void fireSkill(void) override;
	CollisionGroup _group;
	int _indexBuffer;
	PlayerComponent *_player;
};
