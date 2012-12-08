#pragma once
#include "BDrawableEntityComponent.h"
#include <vector>
#include <list>

using namespace std;

class SkillComponent : public BDrawableEntityComponent
{
public:
	SkillComponent(Game* game, GameEntity* entity, int cooldown);
	void Update(GameEntity* entity, long time);
	void Draw(long time) override;
	void Activate(void);
protected:
	bool _activated;
	virtual void fireSkill(void) = 0;
	vector<GameEntity*> _children;
	int _cooldown;
	int _timeCounter;
	vector<GameEntity*> _targets;

};