#pragma once
#include "BehaviourTreeNode.h"
#include <vector>

class GameEntity;
class BehaviourComponent;

class CondAllyHealthLowBehaviourNode : public BehaviourTreeNode
{
public:
	CondAllyHealthLowBehaviourNode(BehaviourComponent* behaviourComponent, int healthThreshold);
	virtual bool Update(void) override;

protected:
	int _healthThreshold;
};