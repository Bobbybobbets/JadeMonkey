#pragma once
#include "BehaviourTreeNode.h"
#include <vector>

class GameEntity;
class HealSkillComponent;
class BehaviourComponent;

class ActionHealAllyBehaviourNode : public BehaviourTreeNode
{
public:
	ActionHealAllyBehaviourNode(BehaviourComponent* behaviourComponent, HealSkillComponent* healSkill, string name);
	bool Update(void);

protected:
	HealSkillComponent* _healSkillComponent;
};