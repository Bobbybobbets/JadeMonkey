#pragma once
#include "BehaviourTreeNode.h"

class BehaviourComponent;

class CondHealthMonitorBehaviourNode : public BehaviourTreeNode
{
public:
	CondHealthMonitorBehaviourNode(BehaviourComponent* behaviourComponent, int healthThreshold);
	bool Update(void);

protected:
	int _healthThreshold;
};