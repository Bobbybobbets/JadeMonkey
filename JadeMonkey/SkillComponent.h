#pragma once
#include "BEntityComponent.h"
#include <vector>

using namespace std;

class SkillComponent : public BEntityComponent
{
public:
	SkillComponent(Game* game, GameEntity* entity, int cooldown);
	void Update(GameEntity* entity, long time);
	void Activate(void);
protected:
	bool _activated;
	virtual void fireSkill(void) = 0;
	vector<GameEntity*> _children;
	int _cooldown;
	int _timeCounter;
	vector<GameEntity*> _targets;
};