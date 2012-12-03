#pragma once
#include "BehaviourTreeNode.h"

class PrioritySelectorBehaviourNode : public BehaviourTreeNode
{
public :
	PrioritySelectorBehaviourNode(BehaviourComponent* behaviourComponent, string name);
	bool Update(void);
};