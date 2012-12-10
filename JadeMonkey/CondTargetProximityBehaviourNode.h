#pragma once
#include "BehaviourTreeNode.h"

class BehaviourComponent;

class CondTargetProximityBehaviourNode : public BehaviourTreeNode
{
public:
	CondTargetProximityBehaviourNode(BehaviourComponent* behaviourComponent, float distance);
	bool Update(void);

protected:
	float _distance;
};